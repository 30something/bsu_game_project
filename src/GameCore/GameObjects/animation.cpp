#include "animation.h"
#include "src/helpers/animations_info.h"

Animation::Animation(Vec2f position, AnimationTypes type_of_animation) :
    GameObject(position, new AnimationPixmapComponent),
    animation_type_(type_of_animation) {
  switch (type_of_animation) {
    case AnimationTypes::kExplosion: {
      last_frame_ = last_frames_for_animations::kExplosionAnimationLastFrame;
      amount_of_frame_renderings =
          frame_renderings::kExplosionAnimationFrameRenderings;
      break;
    }
    case AnimationTypes::kFire: {
      last_frame_ = last_frames_for_animations::kFireAnimationLastFrame;
      amount_of_frame_renderings =
          frame_renderings::kFireAnimationFrameRenderings;
      break;
    }
    default: {
      last_frame_ = 0;
    }
  }
  dynamic_cast<AnimationPixmapComponent*>(pixmap_component_.get())->
      SetAnimationPixmapId(animation_type_, current_frame_);
}

void Animation::GoToNextFrame() {
  static int32_t counter_of_renderings = 0;
  if (counter_of_renderings == amount_of_frame_renderings) {
    current_frame_++;
    counter_of_renderings = 0;
  } else {
    counter_of_renderings++;
  }
  if (current_frame_ > last_frame_) {
    is_ended_ = true;
    return;
  }
  dynamic_cast<AnimationPixmapComponent*>(pixmap_component_.get())->
      SetAnimationPixmapId(animation_type_, current_frame_);
}

bool Animation::IsEnded() const {
  return is_ended_;
}

void Animation::AnimationPixmapComponent::SetAnimationPixmapId(
    AnimationTypes animation_type, int32_t frame) {
  auto category_value = static_cast<int32_t>(PixmapCategories::kAnimations);
  auto animation_type_value = static_cast<int32_t>(animation_type);
  pixmap_id_ = (category_value << 24) + (animation_type_value << 16) + frame;
}
