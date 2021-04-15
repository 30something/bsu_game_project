#include "pixmap_loader.h"

PixmapLoader::PixmapLoader(const QString& filepath) : map_filepath_(filepath) {}

std::map<PixmapID, QPixmap> PixmapLoader::GetPixmaps() {
  std::map<PixmapID, QPixmap> result;

  QPixmap car(":resources/images/cars/car_1.png");
  QPixmap dead_car(":resources/images/cars/car_1_dead.png");
  QPixmap shooting_car(":resources/images/cars/car_1_shoot.png");
  QPixmap mine(":resources/images/other_stuff/mine.png");
  QPixmap health_bonus(":resources/images/other_stuff/hp.png");
  QPixmap bullets_ammo_bonus(":resources/images/other_stuff/ammo.png");
  QPixmap mines_bonus(":resources/images/other_stuff/mines_ammo.png");
  QPixmap map(map_filepath_);

  result[PixmapID::kCar] = car;
  result[PixmapID::kDeadCar] = dead_car;
  result[PixmapID::kMine] = mine;
  result[PixmapID::kShootingCar] = shooting_car;
  result[PixmapID::kBonusHealth] = health_bonus;
  result[PixmapID::kBonusBulletsAmmo] = bullets_ammo_bonus;
  result[PixmapID::kBonusMineAmmo] = mines_bonus;
  result[PixmapID::kMap] = map;

  return result;
}

std::map<PixmapID, QPoint> PixmapLoader::GetOffsets() {
  std::map<PixmapID, QPoint> offsets;
  offsets[PixmapID::kCar] = QPoint(-5, -10);
  offsets[PixmapID::kDeadCar] = QPoint(-5, -10);
  offsets[PixmapID::kShootingCar] = QPoint(-5, -16);
  offsets[PixmapID::kMine] = QPoint(-2, -2);
  offsets[PixmapID::kBonusHealth] = QPoint(-5, -5);
  offsets[PixmapID::kBonusBulletsAmmo] = QPoint(-5, -5);
  offsets[PixmapID::kBonusMineAmmo] = QPoint(-5, -5);
  offsets[PixmapID::kMap] = QPoint(0, 0);
  return offsets;
}
