#include "src/helpers/sizes.h"
#include "src/View/view.h"

View::View(GameMode* game_mode) :
    pixmap_loader_(
        map_data::image_file_paths.file_paths[game_mode->map_index]),
    players_amount_(game_mode->players_amount) {}

void View::Repaint(const std::vector<WrapperBase<GameObject>*>& objects,
                   const std::vector<Vec2f>& cars_positions,
                   QPainter* painter) {
  painter->scale(scale_, scale_);
  for (size_t i = 0; i < frames_.size(); i++) {
    Vec2f position = cars_positions[i];
    DrawMap(painter, frames_[i], position);
    DrawObjects(painter, frames_[i], position, objects);
  }
}

void View::UpdateFrames(int width, int height) {
  frames_.clear();
  if (players_amount_ == 1) {
    frames_.emplace_back(0,
                         0,
                         width,
                         height);
  } else {
    frames_.emplace_back(0,
                         0,
                         width / 2,
                         height);
    frames_.emplace_back(width / 2,
                         0,
                         width / 2,
                         height);
  }
}

std::vector<QRect> View::GetFrames() const {
  return frames_;
}

double View::GetScale() const {
  return scale_;
}

void View::CalculateScale(int window_width, int window_height) {
  double screen_diagonal =
      std::hypot(window_width, window_height);
  screen_diagonal *= car_sizes::kPercentageOfCarSizeOnSceeen;
  screen_diagonal /= 100;
  screen_diagonal /= car_sizes::kCarDiagonalInPixels;
  scale_ = screen_diagonal;
}

void View::DrawMap(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& pos) {
  painter->drawPixmap(frame.left() / scale_,
                      0,
                      pixmap_loader_.GetPixmap(PixmapID::kMap),
                      pos.GetX() - frame.width() / 2 / scale_,
                      pos.GetY() - frame.height() / 2 / scale_,
                      frame.width() / scale_,
                      frame.height() / scale_);
}

void View::DrawObjects(QPainter* painter,
                       const QRect& frame,
                       const Vec2f& frame_center,
                       const std::vector<WrapperBase<GameObject>*>& objects) {
  for (const auto& object : objects) {
    for (size_t i = 0; i < object->Size(); i++) {
      double x = frame.left() / scale_ + (*object)[i].GetPosition().GetX()
          - frame_center.GetX()
          + frame.width() / scale_ / 2;
      double y = (*object)[i].GetPosition().GetY() - frame_center.GetY()
          + frame.height() / scale_ / 2;
      if (frame.contains(x * scale_, y * scale_)) {
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

void View::resizeEvent(int width, int height) {
  CalculateScale(width, height);
  UpdateFrames(width, height);
}
