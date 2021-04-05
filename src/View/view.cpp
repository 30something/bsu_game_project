#include "src/View/view.h"

View::View(QWidget* parent, GameController* model, GameMode* game_mode) :
    model_(model),
    start_label_(new QLabel("Get ready!", parent)),
    car_(":resources/images/cars/car_1.png"),
    players_amount_(game_mode->players_amount),
    laps_amount_(game_mode->laps_amount) {
  start_label_->setAlignment(Qt::AlignCenter);
  // for (int i = 0; i < players_amount_; i++) {
  //   laps_labels_.emplace_back(new QLabel(parent));
  //   velocity_labels_.emplace_back(new QLabel(parent));
  //   laps_labels_[i]->setAlignment(Qt::AlignRight);
  //   velocity_labels_[i]->setAlignment(Qt::AlignLeft);
  // }
  // UpdateLapsLabels();
  // UpdateVelocityLabels();
  map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter* painter) {
  start_label_->setGeometry(0, 0, painter->window().width(), painter->window().height());
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  std::vector<QPoint> coordinates = model_->GetCarCoordinates();
  std::vector<double> angles = model_->GetCarAngles();
  std::vector<Car> cars = model_->GetCars();

  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], coordinates[i]);
  }

  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < coordinates.size(); j++) {
      DrawCar(painter, frames[i], coordinates[i], coordinates[j], angles[j]);
    }
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < coordinates.size(); j++) {
      DrawUI(painter, frames[i], cars[i]);
    }
  }
}
//
// void View::Resize(int width, int height) {
//   start_label_->setGeometry(0, 0, width, height);
//   if (players_amount_ == 1) {
//     laps_labels_[0]->setGeometry(0, 0, width, height);
//     velocity_labels_[0]->setGeometry(0, 0, width, height);
//   } else {
//     laps_labels_[0]->setGeometry(0, 0, width / 2, height / 2);
//     velocity_labels_[0]->setGeometry(0, 0, width, height);
//     laps_labels_[1]->setGeometry(0, 0, width, height);
//     velocity_labels_[1]->setGeometry(width / 2, 0, width, height);
//   }
// }

void View::UpdateStartLabel(const std::string& new_text) {
  start_label_->setText(QString::fromStdString(new_text));
}
//
// void View::UpdateLapsLabels() {
//   for (int i = 0; i < players_amount_; i++) {
//     laps_labels_[i]->setText(QString::fromStdString(
//         "Laps: " +
//             std::to_string(model_->GetLapsCounter(i)) +
//             " / " +
//             std::to_string(laps_amount_)));
//   }
// }
//
// void View::UpdateVelocityLabels() {
//   for (int i = 0; i < players_amount_; i++) {
//     velocity_labels_[i]->setText(QString::fromStdString(
//         "Velocity: " +
//             std::to_string(model_->GetVelocity(i))));
//   }
// }

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

void View::DrawUI(QPainter* painter,
                  const QRect& frame,
                  const Car& car) {
  int x_coord = frame.left() / kScale + 10;
  int y_coord = 10;
  painter->save();
  painter->translate(x_coord, y_coord);
  // TODO(dima_makarov): fix laps and velocity
  painter->drawText(0,
                    0,
                    QString::fromStdString("Velocity: "
                                               + std::to_string(car.GetVelocity().GetLength())
                                               + ", Laps:"
                                               + std::to_string(model_->GetLapsCounter(
                                                   0))));
  painter->restore();
}
