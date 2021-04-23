#include "view_info_updater.h"

ViewInfoUpdater::ViewInfoUpdater(QWidget* parent,
                                 GameMode* game_mode) :
    game_mode_(game_mode),
    parent_(parent),
    start_label_(new QLabel("Get ready!", parent)),
    layout_(new QVBoxLayout(parent)),
    laps_amount_(game_mode_->laps_amount) {
  layout_->setAlignment(Qt::AlignCenter);
  start_label_->setAlignment(Qt::AlignCenter);
  layout_->addWidget(start_label_);
}

void ViewInfoUpdater::Repaint(QPainter* painter,
                              const CarsData& cars_data,
                              const std::vector<QRect>& frames,
                              double scale) {
  cars_data_ = cars_data;
  UpdateAllInfoDescription(painter,
                           frames,
                           scale);
}

void ViewInfoUpdater::UpdateStartInfo() {
  seconds_before_start_--;
  if (seconds_before_start_ == 0) {
    start_label_->clear();
    is_game_started_ = true;
  } else if (seconds_before_start_ == 1) {
    start_label_->setText("Go!");
  } else {
    start_label_->setText(
        QString::fromStdString(std::to_string(seconds_before_start_ - 1)));
  }
}

void ViewInfoUpdater::UpdatePlayerInfoDescription(QPainter* painter,
                                                  int x_pos,
                                                  int y_pos,
                                                  int index) {
  painter->drawText(x_pos,
                    y_pos,
                    QString::fromStdString("Velocity: " +
                        std::to_string(cars_data_.GetVelocity(index)) +
                        ", Laps: " +
                        std::to_string(cars_data_.GetLapsCounter(index))
                        + " / " +
                        std::to_string(laps_amount_)));
}

void ViewInfoUpdater::UpdateAllInfoDescription(QPainter* painter,
                                               const std::vector<QRect>& frames,
                                               double scale) {
  for (int i = 0; i < static_cast<int>(frames.size()); i++) {
    UpdatePlayerInfoDescription(
        painter,
        frames[i].left() / scale,
        frames[i].top() / scale + kDescriptionOffset,
        i);
  }
}

bool ViewInfoUpdater::GetStartState() const {
  return is_game_started_;
}