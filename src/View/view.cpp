#include "src/View/view.h"

View::View(GameController* model, GameMode* game_mode) :
    model_(model),
    car_(":resources/images/cars/car_1.png"),
    dead_car_(":resources/images/cars/car_1_dead.png"),
    mine_(":resources/images/other_stuff/mine.png"),
    shot_(":resources/images/other_stuff/shot.png"),
    players_amount_(game_mode->players_amount) {
  map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  std::vector<Car> cars = model_->GetCars();
  std::vector<QPoint> mines = model_->GetMinesCoordinates();
  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], cars[i].GetPosition());
    for (size_t j = 0; j < cars.size(); j++) {
      DrawPicture(
          painter,
          frames[i],
          cars[i].GetPosition(),
          cars[j].GetPosition(),
          cars[j].GetAngle(),
          (cars[j].IsAlive() ? car_ : dead_car_),
          QPoint(-5, -10));
      if (cars[j].IsShooting()) {
        DrawPicture(
            painter,
            frames[i],
            cars[i].GetPosition(),
            cars[j].GetPosition(),
            cars[j].GetAngle(),
            shot_,
            QPoint(-2, -20));
      }
    }
    for (auto& mine : mines) {
      DrawPicture(
          painter,
          frames[i],
          cars[i].GetPosition(),
          Vec2f(mine.x(), mine.y()),
          0,
          mine_,
          QPoint(-2, -2));
    }
  }
}

std::vector<QRect> View::GetFramesVector(const QPainter* painter) const {
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
  return frames;
}

void View::DrawMap(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& pos) {
  painter->drawPixmap(frame.left() / kScale,
                      0,
                      map_,
                      pos.GetX() - frame.width() / 2 / kScale,
                      pos.GetY() - frame.height() / 2 / kScale,
                      frame.width() / kScale,
                      frame.height() / kScale);
}

void View::DrawPicture(QPainter* painter,
                       const QRect& frame,
                       const Vec2f& frame_center,
                       const Vec2f& coords,
                       double angle,
                       const QPixmap& pixmap,
                       const QPoint& offset) const {
  int x = frame.left() / kScale + coords.GetX() - frame_center.GetX()
      + frame.width() / kScale / 2;
  int y = coords.GetY() - frame_center.GetY()
      + frame.height() / kScale / 2;
  if (frame.contains(x * kScale, y * kScale)) {
    painter->save();
    painter->translate(x, y);
    painter->rotate(angle);
    painter->drawPixmap(offset.x(), offset.y(), pixmap);
    painter->restore();
  }
}
