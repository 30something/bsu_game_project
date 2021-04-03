#include "src/View/view.h"

View::View(QWidget* parent, GameController* model, GameMode* game_mode) :
    model_(model),
    parent_(parent),
    start_label_(new QLabel("Get ready!", parent)),
    car_(":resources/images/cars/car_1.png"),
    players_amount_(game_mode->players_amount) {
  start_label_->setAlignment(Qt::AlignCenter);
  for (int i = 0; i < players_amount_; i++) {
    laps_labels_.emplace_back(new QLabel(parent));
    velocity_labels_.emplace_back(new QLabel(parent));
    laps_labels_[i]->setAlignment(Qt::AlignRight);
    velocity_labels_[i]->setAlignment(Qt::AlignLeft);
  }
  map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  std::vector<QPoint> coordinates = model_->GetCarCoordinates();
  std::vector<double> angles = model_->GetCarAngles();

  start_label_->setGeometry(
      0, 0, parent_->width(), parent_->height());
  for (int i = 0; i < players_amount_; i++) {
    UpdateLapsLabel(laps_labels_[i], model_->GetLapsCounter(i));
    UpdateVelocityLabel(velocity_labels_[i], model_->GetVelocity(i));
  }
  if (players_amount_ == 1) {
    laps_labels_[0]->setGeometry(0, 0, parent_->width(), parent_->height());
    velocity_labels_[0]->setGeometry(0, 0, parent_->width(), parent_->height());
  } else {
    laps_labels_[0]->setGeometry(
        0, 0, parent_->width() / 2, parent_->height() / 2);
    velocity_labels_[0]->setGeometry(0, 0, parent_->width(), parent_->height());
    laps_labels_[1]->setGeometry(0, 0, parent_->width(), parent_->height());
    velocity_labels_[1]->setGeometry(
        parent_->width() / 2, 0, parent_->width(), parent_->height());
  }

  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], coordinates[i]);
  }
  for (size_t i = 0; i < frames.size(); i++) {
    for (size_t j = 0; j < coordinates.size(); j++) {
      DrawCar(painter, frames[i], coordinates[i], coordinates[j], angles[j]);
    }
  }
}

void View::UpdateStartLabel(const std::string& new_text) {
  start_label_->setText(QString::fromStdString(new_text));
}

void View::UpdateLapsLabel(QLabel* label, int laps_counter) {
  label->setText(QString::fromStdString(
      "Laps: " + std::to_string(laps_counter) + " / 3"));
}

void View::UpdateVelocityLabel(QLabel* label, double velocity) {
  label->setText(QString::fromStdString(
      "Velocity: " + std::to_string(velocity)));
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
