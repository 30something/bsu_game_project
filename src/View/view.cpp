#include "src/View/view.h"
#include <iostream>

View::View(QWidget* parent, GameController* model, GameMode* game_mode) :
    model_(model),
    car_(":resources/images/cars/car_1.png"),
    dead_car_(":resources/images/cars/car_1_dead.png"),
    mine_(":resources/images/other_stuff/mine.png"),
    shot_(":resources/images/other_stuff/shot.png"),
    start_label_(new QLabel("Get ready!", parent)),
    players_amount_(game_mode->players_amount),
    laps_amount_(game_mode->laps_amount) {
  start_label_->setAlignment(Qt::AlignCenter);
  map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter* painter) {
  start_label_->setGeometry(0,
                            0,
                            painter->window().width(),
                            painter->window().height());
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

  UpdateInfoDescription(painter);
}

void View::UpdateStartLabel(const std::string& new_text) {
  start_label_->setText(QString::fromStdString(new_text));
}

void View::UpdateInfoDescription(QPainter* painter) {
  painter->save();
  painter->drawText(0,
                    10,
                    QString::fromStdString("Velocity: " +
                        std::to_string(model_->GetVelocity(0)) +
                        ", Laps: " +
                        std::to_string(model_->GetLapsCounter(0)) +
                        " / " +
                        std::to_string(laps_amount_)));
  if (players_amount_ > 1) {
    painter->drawText(painter->window().width() / 4,
                      10,
                      QString::fromStdString("Velocity: " +
                          std::to_string(model_->GetVelocity(1)) +
                          ", Laps: " +
                          std::to_string(model_->GetLapsCounter(1)) +
                          " / " +
                          std::to_string(laps_amount_)));
  }
  painter->restore();
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
