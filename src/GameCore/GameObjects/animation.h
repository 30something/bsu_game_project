#pragma once

#include "src/GameCore/GameObjects/game_object.h"
#include "src/helpers/game_object_states.h"

class Animation : public GameObject {
 public:
  void GoToNextFrame();
  explicit Animation(Vec2f position, AnimationTypes animation_type);
  explicit Animation(const Vec2f* position_of_attached_object,
                     AnimationTypes animation_type);
  ~Animation() override = default;
  bool IsEnded() const;

  bool operator==(const Animation& rhs) const {
    return animation_type_ == rhs.animation_type_ &&
        position_ == rhs.position_;
  }

  bool operator!=(const Animation& rhs) const {
    return !(rhs == *this);
  }

 private:
  class AnimationPixmapComponent : public PixmapComponent {
   public:
    void SetAnimationPixmapId(AnimationTypes animation_type, int32_t frame);
    ~AnimationPixmapComponent() override = default;
  };

  const Vec2f* position_of_attached_object_ = nullptr;
  AnimationTypes animation_type_;
  int32_t counter_of_renderings_ = 0;
  int32_t current_frame_ = 0;
  int32_t last_frame_ = 0;
  int32_t amount_of_frame_renderings_ = 0;
  int32_t first_frame_of_cycle_ = 0;
  bool is_ended_ = false;
  bool is_cyclic_ = false;
};
