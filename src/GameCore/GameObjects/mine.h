#pragma once

#include <string>
#include <vector>

#include "src/helpers/vec2f.h"
#include "src/GameCore/GameObjects/game_object.h"

class Mine : public GameObject {
 public:
  explicit Mine(Vec2f position);
  bool operator==(const Mine& rhs) const;
  bool operator!=(const Mine& rhs) const;
  void SetExploded();
  bool IsExploded() const;

 private:
  bool is_exploded_ = false;
};
