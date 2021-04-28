#include "pixmap_loader.h"

PixmapLoader::PixmapLoader(const QString& filepath) : map_filepath_(filepath) {
  InitPixmaps();
  InitOffsets();
}

void PixmapLoader::InitPixmaps() {
  QString basic_path = ":resources/images/";
  QPixmap car(basic_path + "cars/car1.png");
  QPixmap dead_car(basic_path + "cars/car1_dead.png");
  QPixmap shooting_car(basic_path + "cars/car1_shoot.png");
  QPixmap mine(basic_path + "other_stuff/mine.png");
  QPixmap exploded_mine(basic_path + "other_stuff/exploded_mine.png");
  QPixmap health_bonus(basic_path + "other_stuff/hp.png");
  QPixmap bullets_ammo_bonus(basic_path + "other_stuff/ammo.png");
  QPixmap mines_bonus(basic_path + "other_stuff/mines_ammo.png");
  QPixmap map(map_filepath_);

  pixmaps_[PixmapID::kCar] = car;
  pixmaps_[PixmapID::kDeadCar] = dead_car;
  pixmaps_[PixmapID::kMine] = mine;
  pixmaps_[PixmapID::kExplodedMine] = exploded_mine;
  pixmaps_[PixmapID::kShootingCar] = shooting_car;
  pixmaps_[PixmapID::kBonusHealth] = health_bonus;
  pixmaps_[PixmapID::kBonusBulletsAmmo] = bullets_ammo_bonus;
  pixmaps_[PixmapID::kBonusMineAmmo] = mines_bonus;
  pixmaps_[PixmapID::kMap] = map;
}

void PixmapLoader::InitOffsets() {
  offsets_[PixmapID::kCar] = QPoint(-5, -10);
  offsets_[PixmapID::kDeadCar] = QPoint(-5, -10);
  offsets_[PixmapID::kShootingCar] = QPoint(-5, -16);
  offsets_[PixmapID::kMine] = QPoint(-2, -2);
  offsets_[PixmapID::kExplodedMine] = QPoint(-5, -5);
  offsets_[PixmapID::kBonusHealth] = QPoint(-5, -5);
  offsets_[PixmapID::kBonusBulletsAmmo] = QPoint(-5, -5);
  offsets_[PixmapID::kBonusMineAmmo] = QPoint(-5, -5);
  offsets_[PixmapID::kMap] = QPoint(0, 0);
}

const QPixmap& PixmapLoader::GetPixmap(PixmapID id) {
  return pixmaps_[id];
}

const QPoint& PixmapLoader::GetOffset(PixmapID id) {
  return offsets_[id];
}
