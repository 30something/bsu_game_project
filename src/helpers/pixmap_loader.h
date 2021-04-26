#pragma once

#include <map>
#include <vector>

#include <QString>
#include <QPixmap>
#include <QPoint>

#include "src/helpers/pixmapIDs.h"

class PixmapLoader {
 public:
  explicit PixmapLoader(const QString& filepath);
  const QPixmap& GetPixmap(PixmapID id);
  const QPoint& GetOffset(PixmapID id);

 private:
  void InitPixmaps();
  void InitOffsets();

  QString map_filepath_;
  std::map<PixmapID, QPixmap> pixmaps_;
  std::map<PixmapID, QPoint> offsets_;

  static constexpr int32_t kCarsPixmapsAmount = 8;
};
