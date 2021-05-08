#include "animation.h"

Animation::Animation(Vec2f position, AnimationTypes type_of_animation) :
    GameObject(position, new AnimationPixmapComponent),
    animation_type_(type_of_animation) {
  switch (type_of_animation) {
    case AnimationTypes::kExplosion: {
      last_frame_ = 4;
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
  current_frame_++;
  if (current_frame_ > last_frame_) {
    is_ended_ = true;
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
