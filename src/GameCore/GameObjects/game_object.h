#pragma once

#include <string>
#include <vector>

#include <QPixmap>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "src/helpers/pixmapIDs.h"

class GameObject {
 public:
  explicit GameObject(const Vec2f& position);
  Vec2f GetPosition() const;
  virtual double GetAngle() const;
  virtual PixmapID GetPixmapId() const;
  virtual const std::vector<Line>& GetCollisionLines() const;

 protected:
  Vec2f position_;
  PixmapID pixmap_id_;
  std::vector<Line> collision_lines_;
  virtual void UpdateCollisionLines();

 private:
  static constexpr double kDefaultSize = 5;
};
