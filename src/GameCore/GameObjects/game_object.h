#pragma once

#include <string>
#include <vector>

#include <QPixmap>

#include "src/helpers/vec2f.h"
#include "src/helpers/line.h"
#include "src/helpers/game_object_states.h"
#include "src/helpers/pixmap_categories.h"

using PixmapID = int32_t;

class GameObject {
 public:
  explicit GameObject(const Vec2f& position);
  virtual ~GameObject();
  Vec2f GetPosition() const;
  virtual double GetAngle() const;
  virtual PixmapID GetPixmapId() const;
  virtual const std::vector<Line>& GetCollisionLines() const;

 protected:
  virtual void UpdateCollisionLines();

  class PixmapComponent {
   public:
    virtual PixmapID GetPixmapId() const;
    virtual ~PixmapComponent() = default;

   protected:
    PixmapID pixmap_id_ = 0;
  };

  Vec2f position_;
  std::vector<Line> collision_lines_;
  PixmapComponent* pixmap_component_;

 private:
  static constexpr double kDefaultSize = 5;
};
