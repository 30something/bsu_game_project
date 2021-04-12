#pragma once

#include <string>
#include <vector>

#include <QPixmap>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"

class GameObject {
 public:
  virtual const Vec2f& GetPosition() const = 0;
  virtual double GetAngle() const = 0;
  virtual std::string GetPixmapId() const = 0;
  virtual std::vector<Line> GetLines() const = 0;
};
