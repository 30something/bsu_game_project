#include "src/View/view.h"

View::View(GameMode* game_mode) :
    players_amount_(game_mode->players_amount),
    pixmap_loader_(map_data::image_filepaths[game_mode->map_index]),
    start_label_(new QLabel("Get ready!", parent)),
    players_amount_(game_mode->players_amount),
    laps_amount_(game_mode->laps_amount) {
  start_label_->setAlignment(Qt::AlignCenter);

}

void View::Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
                   const std::vector<Vec2f>& cars_positions,
                   QPainter* painter) {
  start_label_->setGeometry(0,
                            0,
                            painter->window().width(),
                            painter->window().height());
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);

  for (size_t i = 0; i < frames.size(); i++) {
    Vec2f position = cars_positions[i];
    DrawMap(painter, frames[i], position);
    DrawObjects(painter, frames[i], position, objects);
  }
  UpdateAllInfoDescription(painter);
}

void View::UpdateStartLabel(int seconds_before_start) {
  if (seconds_before_start == 0) {
    start_label_->setText("Go!");
  } else {
    start_label_->setText(
        QString::fromStdString(std::to_string(seconds_before_start)));
  }
}

void View::ClearStartLabel() {
  start_label_->clear();
}

void View::UpdatePlayerInfoDescription(QPainter* painter,
                                       int x_pos,
                                       int y_pos,
                                       int index) {
  painter->drawText(x_pos,
                    y_pos,
                    QString::fromStdString("Velocity: " +
                        std::to_string(model_->GetVelocity(index)) +
                        ", Laps: " +
                        std::to_string(model_->GetLapsCounter(index)) +
                        " / " +
                        std::to_string(laps_amount_)));
}

void View::UpdateAllInfoDescription(QPainter* painter) {
  painter->save();
  UpdatePlayerInfoDescription(painter, 0, 10, 0);
  if (players_amount_ > 1) {
    UpdatePlayerInfoDescription(painter, painter->window().width() / 4, 10, 1);
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
                      pixmap_loader_.GetPixmap(PixmapID::kMap),
                      pos.GetX() - frame.width() / 2 / kScale,
                      pos.GetY() - frame.height() / 2 / kScale,
                      frame.width() / kScale,
                      frame.height() / kScale);
}

void View::DrawObjects(QPainter* painter,
                       const QRect& frame,
                       const Vec2f& frame_center,
                       const std::vector<WrapperBase<GameObject>*>& objects) {
  for (const auto& object : objects) {
    for (size_t i = 0; i < object->Size(); i++) {
      double x = frame.left() / kScale + (*object)[i].GetPosition().GetX()
          - frame_center.GetX()
          + frame.width() / kScale / 2;
      double y = (*object)[i].GetPosition().GetY() - frame_center.GetY()
          + frame.height() / kScale / 2;
      if (frame.contains(x * kScale, y * kScale)) {
        painter->save();
        painter->translate(x, y);
        painter->rotate((*object)[i].GetAngle());
        painter->drawPixmap(pixmap_loader_.GetOffset(
                                (*object)[i].GetPixmapId()).x(),
                            pixmap_loader_.GetOffset(
                                (*object)[i].GetPixmapId()).y(),
                            pixmap_loader_.GetPixmap(
                                (*object)[i].GetPixmapId()));
        painter->restore();
      }
    }
  }
}
