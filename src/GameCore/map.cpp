#include "map.h"

Map::Map(int map_index) {
  switch (map_index) {
    case 0: {
      map_data_filename = ":resources/images/map_data/map_1.txt";
      break;
    }
    case 1: {
      map_data_filename = ":resources/images/map_data/map_2.txt";
      break;
    }
    case 2: {
      map_data_filename = ":resources/images/map_data/map_3.txt";
      break;
    }
    default: {
      qWarning("Something went wrong with map");
    }
  }
}

void Map::ParseMapBorders() {
  QTextStream out(stdout);
  QFile file(map_data_filename);
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
        if (Line::IsIntersects(lines[i], l2)) {
          car->SetIsCollidingWithBorders(true);
          return;
        }
      }
    }
  }
}
