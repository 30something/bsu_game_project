#include "game_map.h"

Map::Map(GameMode* game_mode) :
    game_mode_(game_mode) {
  JsonMapParser
      parser(map_data::json_file_paths.file_paths[game_mode->map_index]);
  borders_ = parser.GetBorders();
  waypoints_ = parser.GetWaypoints();
  no_go_lines_ = parser.GetNoGoLines();
  pos_and_angles_ = parser.GetCarStartPositionsAndAngles();
  CalculateBonusesPositions();
  bonus_timer_.setSingleShot(true);
  bonus_timer_.start(
      QRandomGenerator::global()->bounded(kMaxMilliSecondsForNewBonus)
          + kMinMilliSecondForNewBonus);
  finish_line_ = parser.GetFinishLine();
  if (game_mode->network_controller != nullptr
      && game_mode->network_controller->GetId() != 0) {
    connect(game_mode->network_controller,
            &NetworkController::GotNewBonusData,
            this,
            &Map::ProceedNewBonusFromNetwork);
  }
}

void Map::HandleCarTick(Car* car) {
  ProceedCollisions(car);
  ProceedActiveBonuses(car);
  ProceedNewBonuses();
}

void Map::HandleCarCrashIntoBorder(Car* car, const Vec2f& point) {
  Vec2f position = car->GetPosition();
  car->AddHitPoints(-car->GetVelocity().GetLength() * kHPDecrease);
  Vec2f deviation
      (position.GetX() - point.GetX(), position.GetY() - point.GetY());
  deviation.Normalize();
  Vec2f velocity = car->GetVelocity()
      + deviation * physics::kCollisionDeviationScalar;
  velocity *= kVelocityDecrease;
  car->SetVelocity(velocity);
  car->SetPosition(position + deviation);
}

void Map::CalculateBonusesPositions() {
  for (const auto& first : borders_[0]) {
    Vec2f second = borders_[1][FindIndexOfMinimalDistance(first, borders_[1])];
    Line line(first.GetX(), first.GetY(), second.GetX(), second.GetY());
    Vec2f point = physics::GetRandomPointOnLine(line,
                                                kBonusSpawnDeadZone,
                                                kBonusSpawnDeadZone);
    bonuses_positions_.push_back(point);
  }
}

size_t Map::FindIndexOfMinimalDistance(Vec2f first,
                                       const std::vector<Vec2f>& second) {
  double min_distance = physics::Distance(first, second[0]);
  int minimal_index = 0;
  for (size_t i = 0; i < second.size(); i++) {
    if (physics::Distance(first, second[i]) < min_distance) {
      min_distance = physics::Distance(first, second[i]);
      minimal_index = i;
    }
  }
  return minimal_index;
}

void Map::ProceedCollisions(Car* car) {
  // For every line of the car find the interceptions
  // with every line of the borders
  auto lines = car->GetCollisionLines();
  for (int i = 0; i < 4; i++) {
    for (const auto& border : borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l2;
        size_t border_i = (j == border.size() - 1 ? 0 : j + 1);
        l2.x1 = border[j].GetX();
        l2.y1 = border[j].GetY();
        l2.x2 = border[border_i].GetX();
        l2.y2 = border[border_i].GetY();
        if (physics::IsIntersects(lines[i], l2)) {
          Vec2f point = physics::FindIntersectionPoint(lines[i], l2);
          HandleCarCrashIntoBorder(car, point);
          return;
        }
      }
    }
  }
}

void Map::ProceedNewBonuses() {
  NetworkController* network = game_mode_->network_controller;
  if (network != nullptr && network->GetId() != 0) {
    return;
  }
  if (bonuses_.size() < kMaxBonusesAmount && !bonus_timer_.isActive()) {
    int position_index = QRandomGenerator::global()->
        bounded(static_cast<int>(bonuses_positions_.size()));
    auto type(BonusTypes(QRandomGenerator::global()->bounded(
        kAmountOfBonusTypes)));
    bonuses_.emplace_back(bonuses_positions_[position_index], type);
    bonus_timer_.start(
        QRandomGenerator::global()->bounded(kMaxMilliSecondsForNewBonus)
            + kMinMilliSecondForNewBonus);
    if (network != nullptr) {
      network->SendNewBonusData(bonuses_positions_[position_index],
                                static_cast<int>(type));
    }
  }
}

void Map::ProceedActiveBonuses(Car* car) {
  for (size_t i = 0; i < bonuses_.size(); i++) {
    if (physics::IsIntersects(car->GetCollisionLines(),
                              bonuses_[i].GetCollisionLines())) {
      bonuses_[i].ApplyTo(car);
      bonuses_.erase(std::find(bonuses_.begin(),
                               bonuses_.end(),
                               bonuses_[i]));
    }
  }
}

const std::vector<Bonus>& Map::GetActiveBonuses() const {
  return bonuses_;
}

const std::vector<std::vector<Vec2f>>& Map::GetBorders() const {
  return borders_;
}

const std::vector<Vec2f>& Map::GetWaypoints() const {
  return waypoints_;
}

const std::vector<Line>& Map::GetNoGoLines() const {
  return no_go_lines_;
}

const std::vector<std::pair<Vec2f, double>>& Map::GetPosAndAngles() const {
  return pos_and_angles_;
}

const Line& Map::GetFinishLine() const {
  return finish_line_;
}

void Map::ProceedNewBonusFromNetwork() {
  QString json = game_mode_->network_controller->GetData().toString();
  QJsonObject json_object = QJsonDocument::fromJson(json.toUtf8()).object();
  Vec2f position(json_object["x"].toDouble(),
                 json_object["y"].toDouble());
  BonusTypes type = static_cast<BonusTypes>(json_object["type"].toInt());
  bonuses_.emplace_back(position, type);
}
