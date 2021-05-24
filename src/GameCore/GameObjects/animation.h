#pragma once

#include "src/GameCore/GameObjects/game_object.h"

class Animation : public GameObject {
 public:
  void GoToNextFrame();
  explicit Animation(AnimationTypes animation_type, const Vec2f& position);
  explicit Animation(AnimationTypes animation_type,
                     const Vec2f* position_of_attached_object,
                     const Vec2f* angle_of_attached_object = nullptr,
                     const bool* flag_for_playback = nullptr);
  ~Animation() override = default;

  double GetAngle() const override;
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
  const Vec2f* angle_vec_of_attached_object_ = nullptr;
  const bool* flag_for_playback_from_attached_object_ = nullptr;
  AnimationTypes animation_type_;
  int32_t counter_of_renderings_ = 0;
  int32_t current_frame_ = -1;
  int32_t last_frame_ = 0;
  int32_t amount_of_frame_renderings_ = 0;
  int32_t first_frame_of_cycle_ = 0;
  bool is_ended_ = false;
  bool is_cyclic_ = false;
};
