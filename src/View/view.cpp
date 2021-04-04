#include "src/View/view.h"

View::View(GameController* model, GameMode* game_mode) :
    model_(model),
    car_(":resources/images/cars/car_1.png"),
    mine_(":resources/images/other_stuff/mine.png"),
    shot_(":resources/images/other_stuff/shot.png"),
    players_amount_(game_mode->players_amount) {
  map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  std::vector<Car> cars = model_->GetCars();
  std::vector<QPoint> mines = model_->GetMines();
  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], cars[i].GetPosition());
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < cars.size(); j++) {
      if (cars[j].IsAlive()) {
        car_.load(":resources/images/cars/car_1.png");
      } else {
        car_.load(":resources/images/cars/car_1_dead.png");
      }
      DrawCar(painter,
              frames[i],
              cars[i].GetPosition(),
              cars[j].GetPosition(),
              cars[j].GetAngle(),
              car_);
    }
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (auto& mine : mines) {
      DrawMine(painter, frames[i], cars[i].GetPosition(), mine);
    }
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < cars.size(); j++) {
      if (cars[j].IsShooting()) {
        DrawShot(painter,
                 frames[i],
                 cars[i].GetPosition(),
                 cars[j].GetPosition(),
                 cars[j].GetAngle());
      }
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
  painter->drawImage(frame.left() / kScale,
                     0,
                     map_,
                     pos.GetX() - frame.width() / 2 / kScale,
                     pos.GetY() - frame.height() / 2 / kScale,
                     frame.width() / kScale,
                     frame.height() / kScale);
}

void View::DrawCar(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& center,
                   const Vec2f& frame_center,
                   double angle,
                   const QImage& car) {
  int x_coord = frame.left() / kScale + frame_center.GetX() - center.GetX()
      + frame.width() / kScale / 2;
  int y_coord = frame_center.GetY() - center.GetY()
      + frame.height() / kScale / 2;
  if (frame.contains(x_coord * kScale, y_coord * kScale)) {
    painter->save();
    painter->translate(x_coord, y_coord);
    painter->rotate(angle);
    painter->drawImage(-5, -10, car);
    painter->restore();
  }
}

void View::DrawMine(QPainter* painter,
                    const QRect& frame,
                    const Vec2f& frame_center,
                    const QPoint& mine) {
  int x_coord = frame.left() / kScale + mine.x() - frame_center.GetX()
      + frame.width() / kScale / 2;
  int y_coord = mine.y() - frame_center.GetY() + frame.height() / kScale / 2;
  if (frame.contains(x_coord * kScale, y_coord * kScale)) {
    painter->save();
    painter->translate(x_coord, y_coord);
    painter->drawImage(-2, -2, mine_);
    painter->restore();
  }
}

void View::DrawShot(QPainter* painter,
                    const QRect& frame,
                    const Vec2f& frame_center,
                    const Vec2f& coord,
                    double angle) {
  int x_coord = frame.left() / kScale + coord.GetX() - frame_center.GetX()
      + frame.width() / kScale / 2;
  int y_coord =
      coord.GetY() - frame_center.GetY() + frame.height() / kScale / 2;
  if (frame.contains(x_coord * kScale, y_coord * kScale)) {
    painter->save();
    painter->translate(x_coord, y_coord);
    painter->rotate(angle);
    painter->drawImage(-2, -20, shot_);
    painter->restore();
  }
}
