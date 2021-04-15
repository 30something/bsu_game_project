#include "src/View/view.h"

View::View(GameMode* game_mode) :
    players_amount_(game_mode->players_amount),
    pixmap_loader_(map_data::image_filepaths[game_mode->map_index]) {}

void View::Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
                   const std::vector<Vec2f>& cars_positions,
                   QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);

  for (size_t i = 0; i < frames.size(); i++) {
    Vec2f position = cars_positions[i];
    DrawMap(painter, frames[i], position);
    DrawGameObjects(painter, frames[i], position, objects);
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
                      pixmap_loader_.GetPixmap(PixmapID::kMap),
                      pos.GetX() - frame.width() / 2 / kScale,
                      pos.GetY() - frame.height() / 2 / kScale,
                      frame.width() / kScale,
                      frame.height() / kScale);
}

void View::DrawGameObjects(QPainter* painter,
                           const QRect& frame,
                           const Vec2f& frame_center,
                           const std::vector<WrapperBase<GameObject>*>& objects) {
  for (const auto& object : objects) {
    for (size_t i = 0; i < object->size(); i++) {
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
