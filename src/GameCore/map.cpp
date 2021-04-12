#include "map.h"

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
      + deviation * Physics::kCollisionDeviationScalar;
  velocity *= kVelocityDecrease;
  car->SetVelocity(velocity);
  car->SetPosition(position + deviation);
}

void Map::CalculateBonusesPositions() {
  for (const auto& first : borders_[0]) {
    QPoint second = borders_[1][FindIndexOfMinimalDistance(first, borders_[1])];
    Line line(first.x(), first.y(), second.x(), second.y());
    Vec2f point = Physics::GetRandomPointOnLine(line);
    bonuses_positions_.push_back(point);
  }
}

size_t Map::FindIndexOfMinimalDistance(QPoint first,
                                       const std::vector<QPoint>& second) {
  double min_distance = Physics::Distance(first, second[0]);
  int minimal_index = 0;
  for (size_t i = 0; i < second.size(); i++) {
    if (Physics::Distance(first, second[i]) < min_distance) {
      min_distance = Physics::Distance(first, second[i]);
      minimal_index = i;
    }
  }
  return minimal_index;
}

void Map::ProceedCollisions(Car* car) {
  // For every line of the car find the interceptions
  // with every line of the borders
  auto lines = car->GetLines();
  for (int i = 0; i < 4; i++) {
    for (const auto& border : borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l2;
        size_t border_i = (j == (border.size()) - 1 ? 0 : j + 1);
        l2.x1 = border[j].x();
        l2.y1 = border[j].y();
        l2.x2 = border[border_i].x();
        l2.y2 = border[border_i].y();
        if (Physics::IsIntersects(lines[i], l2)) {
          Vec2f point = Physics::FindIntersectionPoint(lines[i], l2);
          HandleCarCrashIntoBorder(car, point);
          return;
        }
      }
    }
  }
}

void Map::ProceedNewBonuses() {
  if (bonuses_.size() < kMaxBonusesAmount && !bonus_timer_.isActive()) {
    int position_index = QRandomGenerator::global()->
        bounded(static_cast<int>(bonuses_positions_.size()));
    auto type(Bonus::BonusType(QRandomGenerator::global()->bounded(
        kAmountOfBonusTypes)));
    bonuses_.emplace_back(bonuses_positions_[position_index], type);
    bonus_timer_.start(
        QRandomGenerator::global()->bounded(kMaxMilliSecondsForNewBonus)
            + kMinMilliSecondForNewBonus);
  }
}

void Map::ProceedActiveBonuses(Car* car) {
  for (auto& bonus : bonuses_) {
    if (Physics::IsInside(car->GetLines(), QPoint(bonus.GetPosition().GetX(), bonus.GetPosition().GetY()))) {
      bonus.ApplyTo(car);
      bonuses_.erase(std::find(bonuses_.begin(),
                               bonuses_.end(),
                               bonus));
    }
  }
}

const std::vector<Bonus>& Map::GetActiveBonuses() const {
  return bonuses_;
}

void Map::SetBorders(const std::vector<std::vector<QPoint>>& borders) {
  borders_ = borders;
  CalculateBonusesPositions();
  bonus_timer_.setSingleShot(true);
  bonus_timer_.start(
      QRandomGenerator::global()->bounded(kMaxMilliSecondsForNewBonus)
          + kMinMilliSecondForNewBonus);
}
