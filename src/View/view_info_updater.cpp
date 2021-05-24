#include "view_info_updater.h"

ViewInfoUpdater::ViewInfoUpdater(QWidget* parent,
                                 GameMode* game_mode) :
    game_mode_(game_mode),
    start_label_(new QLabel("Get ready!", parent)),
    layout_(new QVBoxLayout(parent)),
    laps_amount_(game_mode_->laps_amount),
    players_amount_(game_mode_->players_amount + game_mode_->bots_amount +
        game_mode_->network_players_amount),
    hp_(":resources/images/other_stuff/hp.png"),
    bullets_(":resources/images/other_stuff/ammo.png"),
    mines_(":resources/images/other_stuff/mines_ammo.png") {
  layout_->setAlignment(Qt::AlignCenter);
  start_label_->setAlignment(Qt::AlignCenter);
  start_label_->setFont(fonts::kStartInfoFont);
  start_label_->setStyleSheet("QLabel {"
                              "color: #ff0000;"
                              "font: bold 60px; }");
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

void ViewInfoUpdater::UpdateTopInfo(QPainter* painter,
                                    int x_pos,
                                    int y_pos,
                                    int index) {
  painter->setPen(QPen(QColor(0, 0, 153)));
  int32_t description_offset = fonts::kDefaultInfoFont.pointSize() + 5;
  y_pos -= 5;
  painter->setFont(fonts::kDefaultInfoFont);
  painter->drawText(x_pos,
                    y_pos + description_offset,
                    QString::fromStdString("Laps: " +
                        std::to_string(std::min(laps_amount_,
                                                cars_data_.GetLapsCounter(index)))
                                               + " / " +
                        std::to_string(laps_amount_)));
  painter->drawText(x_pos,
                    y_pos + 2 * description_offset,
                    GetEditedTimeInfo(index));
  painter->drawText(x_pos,
                    y_pos + 3 * description_offset,
                    QString::fromStdString(
                        "Position: " + std::to_string(
                            cars_data_.GetCurrentOrderPosition(index)) + " / " +
                            std::to_string(players_amount_)));
  if (cars_data_.GetFinishPosition(index) > 0) {
    painter->drawText(x_pos,
                      y_pos + 4 * description_offset,
                      GetEditedFinishInfo(index));
  } else if (cars_data_.GetHP(index) == 0) {
    painter->drawText(x_pos,
                      y_pos + 4 * description_offset,
                      QString::fromStdString("Oops, you've exploded!"));
  }
}

void ViewInfoUpdater::DrawSpeed(QPainter* painter, int index) {
  painter->setPen(QPen(QColor(0, 0, 153)));
  painter->drawEllipse(10, 10, 30, 30);
  painter->save();
  painter->translate(25, 25);
  double angle = cars_data_.GetVelocity(index) * 1.4;
  painter->rotate(angle + 45);
  painter->drawLine(0, 0, 10, 10);
  painter->restore();
  painter->drawText(50,
                    30,
                    QString::number(cars_data_.GetVelocity(index))
                        + QString(" km/h"));
}

void ViewInfoUpdater::DrawHP(QPainter* painter, int index) {
  painter->setPen(QPen(QColor(0, 0, 153)));
  painter->scale(2, 2);
  painter->drawPixmap(5, 25, hp_);
  painter->scale(0.5, 0.5);

  painter->setPen(QPen(QColor(0, 0, 0)));
  painter->setBrush(QBrush(QColor(0, 0, 0, 0)));
  painter->drawRect(30, 50, 60, 13);

  painter->setBrush(QBrush(QColor(255, 0, 0)));
  painter->setPen(QPen(QColor(255, 0, 0)));
  double hp = cars_data_.GetHP(index);
  painter->drawRect(31, 51, hp * 59 / 200, 11);

  painter->scale(0.5, 0.5);
  painter->setPen(QPen(QColor(50, 50, 200)));
  painter->drawText(115, 118, QString::number(hp));
  painter->scale(2, 2);
}

void ViewInfoUpdater::DrawAmmo(QPainter* painter, int index) {
  painter->scale(3. / 2, 3. / 2);
  painter->drawPixmap(5, 52, bullets_);
  painter->scale(2. / 3, 2. / 3);
  painter->drawText(20,
                    90,
                    QString::number(cars_data_.GetBulletsAmount(index)));
  painter->save();
  painter->scale(3. / 2, 3. / 2);
  painter->drawPixmap(5 + 40, 52, mines_);
  painter->scale(2. / 3, 2. / 3);
  painter->drawText(20 + 65,
                    90,
                    QString::number(cars_data_.GetMinesAmount(index)));

  painter->restore();
}

void ViewInfoUpdater::UpdateBottomInfo(QPainter* painter,
                                       int x_pos,
                                       int y_pos,
                                       int index) {
  painter->setBrush(QBrush(QColor(255, 255, 255)));
  painter->setPen(QPen(QColor(255, 255, 255)));
  painter->drawRoundedRect(x_pos + 3, y_pos - 103, 120, 100, 10, 10);
  painter->save();
  painter->translate(x_pos + 3, y_pos - 103);
  DrawSpeed(painter, index);
  DrawHP(painter, index);
  DrawAmmo(painter, index);
  painter->restore();
}

void ViewInfoUpdater::UpdateAllInfoDescription(QPainter* painter,
                                               const std::vector<QRect>& frames,
                                               double scale) {
  if (game_mode_->network_controller != nullptr) {
    UpdateTopInfo(painter,
                  frames[0].left() / scale,
                  frames[0].top() / scale,
                  network_id_);
    UpdateBottomInfo(painter,
                     frames[0].left() / scale,
                     frames[0].bottom() / scale,
                     network_id_);
  } else {
    for (int32_t i = 0; i < static_cast<int>(frames.size()); i++) {
      UpdateTopInfo(painter,
                    frames[i].left() / scale,
                    frames[i].top() / scale,
                    i);
      UpdateBottomInfo(painter,
                       frames[i].left() / scale,
                       frames[i].bottom() / scale,
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
  return QString::fromStdString("Time: " +
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

