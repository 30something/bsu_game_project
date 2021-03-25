#include "map.h"

void Map::ParseMapBorders() {
  QTextStream out(stdout);
  QFile file(":resources/images/map_data/map_1.txt");
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

bool Map::ProceedCollisions(std::vector<Vec2f>& corners) {
  // For every line of the car find the interceptions
  // with every line of the borders
  for (int i = 0; i < 4; i++) {
    Line l1;
    if (i == 0 || i == 1) {
      l1.x1 = corners[i].GetX();
      l1.y1 = corners[i].GetY();
      l1.x2 = corners[i + 2].GetX();
      l1.y2 = corners[i + 2].GetY();
    }
    if (i == 2 || i == 3) {
      l1.x1 = corners[i - 2].GetX();
      l1.y1 = corners[i - 2].GetY();
      l1.x2 = corners[i].GetX();
      l1.y2 = corners[i].GetY();
    }
    for (const auto& border : borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l2;
        if (j == border.size() - 1) {
          l2.x1 = border[j].first;
          l2.y1 = border[j].second;
          l2.x2 = border[0].first;
          l2.y2 = border[0].second;
        } else {
          l2.x1 = border[j].first;
          l2.y1 = border[j].second;
          l2.x2 = border[j + 1].first;
          l2.y2 = border[j + 1].second;
        }
        if (Line::IsIntersects(l1, l2)) {
          return true;
        }
      }
    }
  }
  return false;
}
