#include "src/View/view.h"

View::View(GameController* model, GameMode* game_mode) :
    model_(model),
    players_amount_(game_mode->players_amount) {
  PixmapLoader pixmap_loader(map_data::image_filepaths[game_mode->map_index]);
  pixmaps_ = pixmap_loader.GetPixmaps();
  offsets_ = pixmap_loader.GetOffsets();
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  const auto& cars = model_->GetCars();
  const auto& mines = model_->GetMines();
  const auto& bonuses = model_->GetBonuses();

  for (size_t i = 0; i < frames.size(); i++) {
    Vec2f position = cars[i]->GetPosition();
    DrawMap(painter, frames[i], position);
    DrawGameObjects(painter, frames[i], position, cars);
    DrawGameObjects(painter, frames[i], position, mines);
    DrawGameObjects(painter, frames[i], position, bonuses);
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
                      pixmaps_[PixmapID::kMap],
                      pos.GetX() - frame.width() / 2 / kScale,
                      pos.GetY() - frame.height() / 2 / kScale,
                      frame.width() / kScale,
                      frame.height() / kScale);
}

void View::DrawGameObjects(QPainter* painter,
                           const QRect& frame,
                           const Vec2f& frame_center,
                           const std::vector<const GameObject*>& game_objects) {
  for (const auto& object : game_objects) {
    double x = frame.left() / kScale + object->GetPosition().GetX()
        - frame_center.GetX()
        + frame.width() / kScale / 2;
    double y = object->GetPosition().GetY() - frame_center.GetY()
        + frame.height() / kScale / 2;
    if (frame.contains(x * kScale, y * kScale)) {
      painter->save();
      painter->translate(x, y);
      painter->rotate(object->GetAngle());
      pixmaps_[object->GetPixmapId()];
      painter->drawPixmap(offsets_[object->GetPixmapId()].x(),
                          offsets_[object->GetPixmapId()].y(),
                          pixmaps_[object->GetPixmapId()]);
      painter->restore();
    }
  }
}
