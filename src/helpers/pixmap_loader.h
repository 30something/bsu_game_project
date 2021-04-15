#pragma once

#include <map>

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
  void GetPixmaps();
  void GetOffsets();
  QString map_filepath_;
  std::map<PixmapID, QPixmap> pixmaps_;
  std::map<PixmapID, QPoint> offsets_;
};
