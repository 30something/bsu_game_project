#pragma once
#include "types_of_motion.h"

struct EngineParameters {
  double speed_parameter;
  Motion motion_parameter;
  double volume_parameter;
};

struct DriftParameters {
  double speed_parameter;
  bool enable_drifting;
  double volume_parameter;
};

struct BrakeParameters {
  double speed_parameter;
  double volume_parameter;
};

struct ShootingParameters {
  bool using_gun;
  bool bullets;
  bool enable_weapons;
  double volume_parameter;
};

struct EffectParameters {
  bool play;
  double volume_parameter;
};



