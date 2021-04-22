#pragma once

#include <vector>
#include <utility>

#include <QPoint>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "game_mode.h"
#include "line.h"
#include "map_data.h"

class JsonMapParser {
 public:
  explicit JsonMapParser(const QString& filepath);
  std::vector<std::vector<QPoint>> GetBorders();
  std::vector<std::pair<QPoint, double>> GetCarStartPositionsAndAngles();
  Line GetFinishLine();
  std::vector<Vec2f> GetWaypoints();
  std::vector<Line> GetNoGoLines();

 private:
  QJsonObject json_;
};
