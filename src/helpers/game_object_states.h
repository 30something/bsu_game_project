#pragma once

enum class CarStates {
  kDead,
  kStandard,
  kShooting,
  kDamaged,
  kDamagedAndShooting,
  kHealthy,
  kHealthyAndShooting
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

enum class AnimationTypes {
  kExplosion,
  kFire
};
