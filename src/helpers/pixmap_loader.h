#pragma once

#include <unordered_map>
#include <vector>

#include <QDirIterator>
#include <QFileInfoList>
#include <QPixmap>
#include <QPoint>
#include <QString>

#include "src/helpers/cars_colors.h"
#include "src/helpers/game_object_states.h"
#include "src/helpers/pixmap_categories.h"

using PixmapID = int32_t;

class PixmapLoader {
 public:
  explicit PixmapLoader(const QString& filepath);
  const QPixmap& GetPixmap(PixmapID id);
  const QPixmap& GetMapPixmap();

 private:
  void InitPixmaps();

  QString map_filepath_;
  QPixmap map_pixmap_;
  std::unordered_map<CarStates, std::vector<QPixmap>> cars_pixmaps_;
  std::unordered_map<MineStates, std::vector<QPixmap>> mines_pixmaps_;
  std::unordered_map<BonusTypes, std::vector<QPixmap>> bonuses_pixmaps_;
  std::unordered_map<AnimationTypes, std::vector<QPixmap>> animation_pixmaps_;

  // Masks and shifts used to decode the pixmap id
  static constexpr int32_t kCategoryPixmapShift = 24;
  static constexpr int32_t kStatePixmapMask = 16711680;
  static constexpr int32_t kStatePixmapShift = 16;
  static constexpr int32_t kNumberPixmapMask = 255;
};
