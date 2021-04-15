#pragma once

#include <map>

#include <QString>
#include <QPixmap>
#include <QPoint>

#include "src/helpers/pixmapIDs.h"

class PixmapLoader {
 public:
  explicit PixmapLoader(const QString& filepath);
  std::map<PixmapID, QPixmap> GetPixmaps();
  std::map<PixmapID, QPoint> GetOffsets();

 private:
  QString map_filepath_;
};
