#include "json_map_parser.h"

JsonMapParser::JsonMapParser(const QString& filepath) {
  QFile file;
  file.setFileName(filepath);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString json_string = file.readAll();
  file.close();
  QJsonDocument doc = QJsonDocument::fromJson(json_string.toUtf8());
  json_ = doc.object();
}

std::vector<std::vector<Vec2f>> JsonMapParser::GetBorders() {
  std::vector<std::vector<Vec2f>> result;
  QJsonArray borders_array = json_["border_coords"].toArray();
  for (const auto& border : borders_array) {
    QJsonArray coords = border.toArray();
    std::vector<Vec2f> border_vector;
    for (const auto& coordinate : coords) {
      QJsonObject coord_pair = coordinate.toObject();
      border_vector.emplace_back(
          coord_pair["x"].toInt(),
          coord_pair["y"].toInt());
    }
    result.push_back(border_vector);
  }
  return result;
}

std::vector<std::pair<Vec2f, double>>
JsonMapParser::GetCarStartPositionsAndAngles() {
  std::vector<std::pair<Vec2f, double>> result;
  QJsonArray positions_array = json_["car_start_positions"].toArray();
  for (const auto& position : positions_array) {
    QJsonObject position_obj = position.toObject();
    result.emplace_back(
        std::make_pair(Vec2f(position_obj["x"].toInt(),
                             position_obj["y"].toInt()),
                       position_obj["angle"].toDouble()));
  }
  return result;
}

Line JsonMapParser::GetFinishLine() {
  QJsonObject finish_line = json_["finish_line"].toObject();
  return Line(
      finish_line["x1"].toInt(),
      finish_line["y1"].toInt(),
      finish_line["x2"].toInt(),
      finish_line["y2"].toInt());
}

std::vector<Vec2f> JsonMapParser::GetWaypoints() {
  std::vector<Vec2f> result;
  QJsonArray waypoints_array = json_["bot_waypoints"].toArray();
  for (const auto& waypoint : waypoints_array) {
    QJsonObject waypoint_obj = waypoint.toObject();
    result.emplace_back(Vec2f(waypoint_obj["x"].toInt(),
                              waypoint_obj["y"].toInt()));
  }
  return result;
}

std::vector<Line> JsonMapParser::GetNoGoLines() {
  std::vector<Line> result;
  QJsonArray lines_array = json_["bot_no_go_lines"].toArray();
  for (const auto& line : lines_array) {
    QJsonObject line_obj = line.toObject();
    result.emplace_back(line_obj["x1"].toInt(),
                        line_obj["y1"].toInt(),
                        line_obj["x2"].toInt(),
                        line_obj["y2"].toInt());
  }
  return result;
}
