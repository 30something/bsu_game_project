#include "view_info_updater.h"

ViewInfoUpdater::ViewInfoUpdater(QWidget* parent,
                                 GameMode* game_mode) :
    game_mode_(game_mode),
    start_label_(new QLabel("Get ready!", parent)),
    layout_(new QVBoxLayout(parent)),
    laps_amount_(game_mode_->laps_amount),
    players_amount_(game_mode_->players_amount + game_mode_->bots_amount +
        game_mode_->network_players_amount) {
  layout_->setAlignment(Qt::AlignCenter);
  start_label_->setAlignment(Qt::AlignCenter);
  start_label_->setFont(fonts::kStartInfoFont);
  layout_->addWidget(start_label_);
  if (game_mode_->network_controller != nullptr) {
    network_id_ = game_mode_->network_controller->GetId();
  }
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
  int32_t description_offset = fonts::kDefaultInfoFont.pointSize();
  painter->setFont(fonts::kDefaultInfoFont);
  painter->drawText(x_pos,
                    y_pos + description_offset,
                    QString::fromStdString("Velocity: " +
                        std::to_string(cars_data_.GetVelocity(index)) +
                        ", Laps: " +
                        std::to_string(std::min(
                            static_cast<int>(laps_amount_),
                            cars_data_.GetLapsCounter(index)))
                                               + " / " +
                        std::to_string(laps_amount_)));
  painter->drawText(x_pos,
                    y_pos + 2 * description_offset,
                    QString::fromStdString("Bullets: " +
                        std::to_string(cars_data_.GetBulletsAmount(index)) +
                        ", Mines: " +
                        std::to_string(cars_data_.GetMinesAmount(index))));
  painter->drawText(x_pos,
                    y_pos + 3 * description_offset,
                    QString::fromStdString("HP: " +
                        std::to_string(cars_data_.GetHP(index))));
  painter->drawText(x_pos,
                    y_pos + 4 * description_offset,
                    GetEditedTimeInfo(index));
  painter->drawText(x_pos,
                    y_pos + 5 * description_offset,
                    QString::fromStdString(
                        "Current position: " + std::to_string(
                            cars_data_.GetCurrentOrderPosition(index)) + " / " +
                            std::to_string(players_amount_)));
  if (cars_data_.GetFinishPosition(index) > 0) {
    painter->drawText(x_pos,
                      y_pos + 6 * description_offset,
                      GetEditedFinishInfo(index));
  } else if (cars_data_.GetHP(index) == 0) {
    painter->drawText(x_pos,
                      y_pos + 6 * description_offset,
                      QString::fromStdString("Oops, you've exploded!"));
  }
}

void ViewInfoUpdater::UpdateAllInfoDescription(QPainter* painter,
                                               const std::vector<QRect>& frames,
                                               double scale) {
  if (game_mode_->network_controller != nullptr) {
    UpdatePlayerInfoDescription(
        painter,
        frames[0].left() / scale,
        frames[0].top() / scale,
        network_id_);
  } else {
    for (int32_t i = 0; i < static_cast<int>(frames.size()); i++) {
      UpdatePlayerInfoDescription(
          painter,
          frames[i].left() / scale,
          frames[i].top() / scale,
          i);
    }
  }
}

bool ViewInfoUpdater::GetStartState() const {
  return is_game_started_;
}

QString ViewInfoUpdater::GetEditedTimeInfo(int index) const {
  std::vector<size_t> parsed_time = physics::TimeParse(
      cars_data_.GetElapsedTime(index));
  size_t minutes = parsed_time[0];
  size_t seconds = parsed_time[1];
  size_t millis = parsed_time[2];
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
  auto finish_position = cars_data_.GetFinishPosition(index);
  auto pos_with_suffix = std::to_string(finish_position) +
      GetSuffix(finish_position);
  return QString::fromStdString(
      "You finished on " + pos_with_suffix + " position!");
}

std::string ViewInfoUpdater::GetSuffix(int value) {
  switch (value) {
    case 1: {
      return "st";
    }
    case 2: {
      return "nd";
    }
    case 3: {
      return "rd";
    }
    default: {
      return "th";
    }
  }
}
