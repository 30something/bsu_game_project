#include "view_info_updater.h"

ViewInfoUpdater::ViewInfoUpdater(QWidget* parent,
                                 GameMode* game_mode) :
    game_mode_(game_mode),
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
  UpdateAllInfoDescription(painter, frames, scale);
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
                    y_pos + kDescriptionOffset,
                    QString::fromStdString("Velocity: " +
                        std::to_string(cars_data_.GetVelocity(index)) +
                        ", Laps: " +
                        std::to_string(cars_data_.GetLapsCounter(index))
                        + " / " +
                        std::to_string(laps_amount_)));
  painter->drawText(x_pos,
                    y_pos + 2 * kDescriptionOffset,
                    QString::fromStdString("Bullets: " +
                        std::to_string(cars_data_.GetBulletsAmount(index)) +
                        ", Mines: " +
                        std::to_string(cars_data_.GetMinesAmount(index))));
  painter->drawText(x_pos,
                    y_pos + 3 * kDescriptionOffset,
                    QString::fromStdString("HP: " +
                        std::to_string(cars_data_.GetHP(index))));
  painter->drawText(x_pos,
                    y_pos + 4 * kDescriptionOffset,
                    GetEditedTimeInfo(index));
  if (cars_data_.GetFinishPosition(index) < INT32_MAX) {
    painter->drawText(x_pos,
                      y_pos + 5 * kDescriptionOffset,
                      GetEditedFinishInfo(index));
  } else if (cars_data_.GetHP(index) == 0) {
    painter->drawText(x_pos,
                      y_pos + 5 * kDescriptionOffset,
                      QString::fromStdString("Oops, you've exploded!"));
  }
}

void ViewInfoUpdater::UpdateAllInfoDescription(QPainter* painter,
                                               const std::vector<QRect>& frames,
                                               double scale) {
  // TODO(dima_makarov): fix info shown for network players
  for (int i = 0; i < static_cast<int>(frames.size()); i++) {
    UpdatePlayerInfoDescription(
        painter,
        frames[i].left() / scale,
        frames[i].top() / scale,
        i);
  }
}

bool ViewInfoUpdater::GetStartState() const {
  return is_game_started_;
}

QString ViewInfoUpdater::GetEditedTimeInfo(int index) const {
  size_t elapsed_time = cars_data_.GetElapsedTime(index);
  size_t minutes = elapsed_time / 60000;
  size_t seconds = (elapsed_time / 1000) % 60;
  size_t millis = elapsed_time % 1000;
  std::string minutes_str;
  std::string seconds_str;
  std::string millis_str;
  if (minutes < 10) {
    minutes_str += "0";
  }
  minutes_str += std::to_string(minutes);
  if (seconds < 10) {
    seconds_str += "0";
  }
  seconds_str += std::to_string(seconds);
  if (millis < 100) {
    millis_str += "0";
  }
  if (millis < 10) {
    millis_str += "0";
  }
  millis_str += std::to_string(millis);
  return QString::fromStdString("Elapsed time: " +
      minutes_str + ":" + seconds_str + ":" + millis_str);
}

QString ViewInfoUpdater::GetEditedFinishInfo(int index) const {
  int32_t finish_position = cars_data_.GetFinishPosition(index);
  std::string pos_with_prefix = std::to_string(finish_position);
  if (finish_position == 1) {
    pos_with_prefix += "st";
  } else if (finish_position == 2) {
    pos_with_prefix += "nd";
  } else if (finish_position == 3) {
    pos_with_prefix += "rd";
  } else {
    pos_with_prefix += "th";
  }
  return QString::fromStdString(
      "You finished on " + pos_with_prefix + " position!");
}
