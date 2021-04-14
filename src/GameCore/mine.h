#pragma once

#include <string>
#include <vector>

#include "src/helpers/vec2f.h"
#include "game_object.h"

class Mine : public GameObject {
 public:
  explicit Mine(Vec2f position);
  Vec2f GetPosition() const override;
  PixmapID GetPixmapId() const override;
  bool operator==(const Mine& rhs) const;
  bool operator!=(const Mine& rhs) const;

 private:
  Vec2f position_;
};



