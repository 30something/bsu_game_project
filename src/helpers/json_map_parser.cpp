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

std::vector<std::vector<QPoint>> JsonMapParser::GetBorders() {
  std::vector<std::vector<QPoint>> result;
  QJsonArray borders_array = json_["border_coords"].toArray();
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

std::vector<std::pair<QPoint, double>>
JsonMapParser::GetCarStartPositionsAndAngles() {
  std::vector<std::pair<QPoint, double>> result;
  QJsonArray positions_array = json_["car_start_positions"].toArray();
  for (const auto& position : positions_array) {
    QJsonObject position_obj = position.toObject();
    result.emplace_back(
        std::make_pair(QPoint(position_obj["x"].toInt(),
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
