#pragma once

#include "src/helpers/vec2f.h"
#include "game_object.h"

class Mine : public GameObject {
 public:
  Mine(Vec2f position);
  const Vec2f& GetPosition() const override;
  double GetAngle() const override;
  std::string GetPixmapId() const override;
  std::vector<Line> GetLines() const override;
  bool operator==(const Mine& rhs) const;
  bool operator!=(const Mine& rhs) const;

 private:
  Vec2f position_;
};



