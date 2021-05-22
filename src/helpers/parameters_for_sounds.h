#pragma once
#include "types_of_motion.h"

struct EngineParameters {
    double speed_parameter;
    Motion motion_parameter;
    bool play;
};

struct DriftParameters {
    double speed_parameter;
    bool enable_drifting;
};

struct ShootingParameters {
    bool using_gun;
    bool bullets;
    bool enable_weapons;
};