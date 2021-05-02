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
  const std::pair<QPixmap, QPoint>& GetPixmap(PixmapID id);
  const QPixmap& GetMapPixmap();

 private:
  void InitPixmaps();

  QString map_filepath_;
  QPixmap map_pixmap_;
  std::unordered_map<CarStates,
                     std::vector<std::pair<QPixmap, QPoint>>> cars_pixmaps_;
  std::unordered_map<MineStates,
                     std::vector<std::pair<QPixmap, QPoint>>> mines_pixmaps_;
  std::unordered_map<BonusStates,
                     std::vector<std::pair<QPixmap, QPoint>>> bonuses_pixmaps_;
};
