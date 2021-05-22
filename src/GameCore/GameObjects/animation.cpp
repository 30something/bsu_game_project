#include "animation.h"
#include "src/helpers/animations_info.h"

Animation::Animation(AnimationTypes type_of_animation, const Vec2f& position) :
    GameObject(position, new AnimationPixmapComponent),
    animation_type_(type_of_animation) {
  std::string string_with_info =
      (animations_info::animations_info.find(type_of_animation))->second;
  std::size_t pos_of_current_separator =
      string_with_info.find(animations_info::symbol_for_separation);
  std::size_t current_pos = 0;
  last_frame_ = std::stoi(string_with_info.substr(
      current_pos, pos_of_current_separator - current_pos));

  current_pos = pos_of_current_separator + 1;
  pos_of_current_separator = string_with_info.find(
      animations_info::symbol_for_separation, current_pos);
  counter_of_renderings_ = amount_of_frame_renderings_ =
      std::stoi(string_with_info.substr(
          current_pos, pos_of_current_separator - current_pos));

  current_pos = pos_of_current_separator + 1;
  pos_of_current_separator = string_with_info.find(
      animations_info::symbol_for_separation, current_pos);
  is_cyclic_ = std::stoi(string_with_info.substr(
      current_pos, pos_of_current_separator - current_pos));

  if (is_cyclic_) {
    current_pos = pos_of_current_separator + 1;
    pos_of_current_separator = string_with_info.find(
        animations_info::symbol_for_separation, current_pos);
    first_frame_of_cycle_ = std::stoi(string_with_info.substr(
        current_pos, pos_of_current_separator - current_pos));
  }
}

Animation::Animation(AnimationTypes animation_type,
                     const Vec2f* position_of_attached_object,
                     const Vec2f* angle_vec_of_attached_object,
                     const bool* flag_for_playback) :
    Animation(animation_type, *position_of_attached_object) {
  position_of_attached_object_ = position_of_attached_object;
  angle_vec_of_attached_object_ = angle_vec_of_attached_object;
  flag_for_playback_from_attached_object_ = flag_for_playback;
}

void Animation::GoToNextFrame() {
  if ((flag_for_playback_from_attached_object_ != nullptr)
      && (!(*flag_for_playback_from_attached_object_))) {
    is_ended_ = true;
    return;
  }
  if (position_of_attached_object_ != nullptr) {
    position_ = *position_of_attached_object_;
  }
  if (counter_of_renderings_ == amount_of_frame_renderings_) {
    current_frame_++;
    counter_of_renderings_ = 0;
  } else {
    counter_of_renderings_++;
  }
  if (current_frame_ > last_frame_) {
    if (is_cyclic_) {
      current_frame_ = first_frame_of_cycle_;
    } else {
      is_ended_ = true;
    }
    return;
  }
  dynamic_cast<AnimationPixmapComponent*>(pixmap_component_.get())->
      SetAnimationPixmapId(animation_type_, current_frame_);
}

double Animation::GetAngle() const {
  if (angle_vec_of_attached_object_ == nullptr) {
    return 0;
  }
  return angle_vec_of_attached_object_->GetAngleDegrees() + 90;
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
