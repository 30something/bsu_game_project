#include "model.h"

Model::Model() :
    left_borders_(new std::vector<std::pair<int, int>>()),
    right_borders_(new std::vector<std::pair<int, int>>()),
    car_(360, 548, -M_PI / 2, left_borders_, right_borders_) {
  ParseMapBorders();
}

void Model::Tick(int time_millisec) {
  car_.Tick(time_millisec);
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    car_.SetFlagUp(true);
  }
  if (key == Qt::Key_Down) {
    car_.SetFlagDown(true);
  }
  if (key == Qt::Key_Left) {
    car_.SetFlagLeft(true);
  }
  if (key == Qt::Key_Right) {
    car_.SetFlagRight(true);
  }
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    car_.SetFlagUp(false);
  }
  if (key == Qt::Key_Down) {
    car_.SetFlagDown(false);
  }
  if (key == Qt::Key_Left) {
    car_.SetFlagLeft(false);
  }
  if (key == Qt::Key_Right) {
    car_.SetFlagRight(false);
  }
}

std::pair<int, int> Model::GetCarCoordinates() const {
  return std::make_pair(car_.GetX(), car_.GetY());
}

double Model::GetCarAngle() const {
  return car_.GetAngle();
}

void Model::ParseMapBorders() {
  QTextStream out(stdout);
  QFile file(":resources/images/map_data/map_1.txt");
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Cannot open file for reading");
  }
  QTextStream in(&file);
  bool left_part = true;
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line.startsWith('-')) {
      left_part = false;
      continue;
    }
    if (left_part) {
      left_borders_->push_back(ParseLine(line));
    } else {
      right_borders_->push_back(ParseLine(line));
    }
  }
  file.close();
}

std::pair<int, int> Model::ParseLine(const QString& line) {
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
