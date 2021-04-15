#pragma once

#include <string>
#include <vector>

#include <QPixmap>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "src/helpers/pixmapIDs.h"

class GameObject {
 public:
  virtual Vec2f GetPosition() const = 0;
  virtual double GetAngle() const;
  virtual PixmapID GetPixmapId() const = 0;
  virtual std::vector<Line> GetCollisionLines() const;
};
