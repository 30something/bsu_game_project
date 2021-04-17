#pragma once

#include <string>
#include <vector>

#include "src/helpers/vec2f.h"
#include "src/GameCore/GameObjects/game_object.h"

class Mine : public GameObject {
 public:
  explicit Mine(Vec2f position);
  PixmapID GetPixmapId() const override;
  bool operator==(const Mine& rhs) const;
  bool operator!=(const Mine& rhs) const;
};



