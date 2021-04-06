#include "map.h"

Map::Map(GameMode* game_mode) :
    map_index_(game_mode->map_index) {
  ParseMapBorders();
}

void Map::ParseMapBorders() {
  QTextStream out(stdout);
  QFile file(map_data::borders_filepaths[map_index_]);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Cannot open file for reading");
  }
  std::vector<std::pair<int, int>> left_borders_;
  std::vector<std::pair<int, int>> right_borders_;
  QTextStream in(&file);
  bool left_part = true;
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line.startsWith('-')) {
      left_part = false;
      continue;
    }
    if (left_part) {
      left_borders_.push_back(ParseLine(line));
    } else {
      right_borders_.push_back(ParseLine(line));
    }
  }
  file.close();
  borders_.push_back(left_borders_);
  borders_.push_back(right_borders_);
}

std::pair<int, int> Map::ParseLine(const QString& line) {
  std::pair<int, int> result;
  QString number1;
  QString number2;
  bool left = true;
  for (int i = 0; i < line.size(); i++) {
    if (line[i] == ' ') {
      left = false;
      i++;
    }
    if (left) {
      number1 += line[i];
    } else {
      number2 += line[i];
    }
  }
  result.first = number1.toInt();
  result.second = number2.toInt();
  return result;
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
        l2.x1 = border[j].first;
        l2.y1 = border[j].second;
        l2.x2 = border[border_i].first;
        l2.y2 = border[border_i].second;
        if (Physics::IsIntersects(lines[i], l2)) {
          Vec2f point = Physics::FindIntersectionPoint(lines[i], l2);
          CollideCar(car, point);
          return;
        }
      }
    }
  }
}

void Map::CollideCar(Car* car, const Vec2f& point) {
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
