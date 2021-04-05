#include "json_parser.h"

JsonOurParser::JsonOurParser(GameMode* game_mode) {
  QFile file;
  file.setFileName(map_data::json_filepaths[game_mode->map_index]);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  json_string_ = file.readAll();
  file.close();
}

std::vector<std::vector<QPoint>> JsonOurParser::GetBorders() {
  std::vector<std::vector<QPoint>> result;
  QJsonDocument doc = QJsonDocument::fromJson(json_string_.toUtf8());
  QJsonObject json = doc.object();
  QJsonArray borders_array = json["border_coords"].toArray();
  for (const auto& border : borders_array) {
    QJsonArray coords = border.toArray();
    std::vector<QPoint> border_vector;
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

std::vector<std::pair<QPoint, double>> JsonOurParser::GetCarStartPositionsAndAngles() {
  std::vector<std::pair<QPoint, double>> result;
  QJsonDocument doc = QJsonDocument::fromJson(json_string_.toUtf8());
  QJsonObject json = doc.object();
  QJsonArray positions_array = json["car_start_positions"].toArray();
  for (const auto& position : positions_array) {
    QJsonObject position_obj = position.toObject();
    result.emplace_back(
        std::make_pair(QPoint(position_obj["x"].toInt(),
                              position_obj["y"].toInt()),
                       position_obj["angle"].toDouble()));
  }
  return result;
}

Line JsonOurParser::GetFinishLine() {
  QJsonDocument doc = QJsonDocument::fromJson(json_string_.toUtf8());
  QJsonObject json = doc.object();
  QJsonObject finish_line = json["finish_line"].toObject();
  return Line(
      finish_line["x1"].toInt(),
      finish_line["y1"].toInt(),
      finish_line["x2"].toInt(),
      finish_line["y2"].toInt()
      );
}
