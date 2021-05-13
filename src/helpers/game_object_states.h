#pragma once

enum class CarStates {
  kDead,
  kStandard,
  kShooting
};

enum class MineStates {
  kStandard,
  kExploded
};

enum class BonusTypes {
  kHealth = 0,
  kBulletsAmmo = 1,
  kMineAmmo = 2
};
