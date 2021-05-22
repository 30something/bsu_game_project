#pragma once

#include <map>

#include "game_object_states.h"

namespace animations_info {

const char symbol_for_separation = '_';

// last frame -> amount of frame renderings -> is cyclic -> first cycle frame
const std::map<AnimationTypes, std::string> animations_info = {
    {AnimationTypes::kExplosion, "15_2_0"},
    {AnimationTypes::kFire, "18_3_1_8"},
    {AnimationTypes::kShooting, "4_3_1_0"}
};

}  // namespace animations_info
