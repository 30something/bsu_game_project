#pragma once

enum class CarStates {
  kDead,
  kStandard,
  kDamaged,
  kHealthy
};

enum class MineStates {
  kStandard,
  kExploded
};

enum class BonusTypes {
  kHealth,
  kBulletsAmmo,
  kMineAmmo
};

// alphabet order is important here to correct reading from directory
enum class AnimationTypes {
  kExplosion,
  kFire,
  kShooting
};
