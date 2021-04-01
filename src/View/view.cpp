#include "src/View/view.h"

View::View(GameController* model, GameMode* game_mode) :
    model_(model),
    car_(":resources/images/cars/car_1.png"),
    players_amount_(game_mode->players_amount) {
  map_.load(map_data::map_filepaths[game_mode->map_index].second);
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames;
  if (players_amount_ == 1) {
    frames.emplace_back(0,
                        0,
                        painter->window().width(),
                        painter->window().height());
  } else {
    frames.emplace_back(0,
                        0,
                        painter->window().width() / 2,
                        painter->window().height());
    frames.emplace_back(painter->window().width() / 2,
                        0,
                        painter->window().width() / 2,
                        painter->window().height());
  }
  painter->scale(kScale, kScale);
  std::vector<QPoint> coordinates = model_->GetCarCoordinates();
  std::vector<double> angles = model_->GetCarAngles();

  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], coordinates[i]);
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < coordinates.size(); j++) {
      DrawCar(painter, frames[i], coordinates[i], coordinates[j], angles[j]);
    }
  }
}

void View::DrawMap(QPainter* painter,
                   const QRect& frame,
                   const QPoint& pos) {
  painter->drawImage(frame.left() / kScale,
                     0,
                     map_,
                     pos.x() - frame.width() / 2 / kScale,
                     pos.y() - frame.height() / 2 / kScale,
                     frame.width() / kScale,
                     frame.height() / kScale);
}

void View::DrawCar(QPainter* painter,
                   const QRect& frame,
                   const QPoint& center,
                   const QPoint& frame_center,
                   double angle) {
  int x_coord = frame.left() / kScale + frame_center.x() - center.x()
      + frame.width() / kScale / 2;
  int y_coord = frame_center.y() - center.y()
      + frame.height() / kScale / 2;
  if (frame.contains(x_coord * kScale, y_coord * kScale)) {
    painter->save();
    painter->translate(x_coord, y_coord);
    painter->rotate(angle);
    painter->drawImage(-5, -10, car_);
    painter->restore();
  }
}
