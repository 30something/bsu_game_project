#include "pixmap_loader.h"

PixmapLoader::PixmapLoader(const QString& filepath) : map_filepath_(filepath) {
  InitPixmaps();
  InitOffsets();
}

void PixmapLoader::InitPixmaps() {
  QString basic_path = ":resources/images/";
  std::vector<QPixmap> standard_cars;
  std::vector<QPixmap> shooting_cars;

  for (int32_t i = 0; i < kCarsPixmapsAmount; i++) {
    QString car_path = basic_path +
        "cars/car" + QString::fromStdString(std::to_string(i + 1));
    QString standard_car_path = car_path + ".png";
    QString shooting_car_path = car_path + "_shoot.png";
    standard_cars.emplace_back(QPixmap(standard_car_path));
    shooting_cars.emplace_back(QPixmap(shooting_car_path));
    pixmaps_[static_cast<PixmapID>(i)] = standard_cars[i];
    pixmaps_[static_cast<PixmapID>(i + kCarsPixmapsAmount)] = shooting_cars[i];
  }

  QPixmap dead_car(basic_path + "cars/car_dead.png");
  QPixmap mine(basic_path + "other_stuff/mine.png");
  QPixmap health_bonus(basic_path + "other_stuff/hp.png");
  QPixmap bullets_ammo_bonus(basic_path + "other_stuff/ammo.png");
  QPixmap mines_bonus(basic_path + "other_stuff/mines_ammo.png");
  QPixmap map(map_filepath_);

  pixmaps_[PixmapID::kDeadCar] = dead_car;
  pixmaps_[PixmapID::kMine] = mine;
  pixmaps_[PixmapID::kBonusHealth] = health_bonus;
  pixmaps_[PixmapID::kBonusBulletsAmmo] = bullets_ammo_bonus;
  pixmaps_[PixmapID::kBonusMineAmmo] = mines_bonus;
  pixmaps_[PixmapID::kMap] = map;
}

void PixmapLoader::InitOffsets() {
  for (int32_t i = 0; i < kCarsPixmapsAmount; i++) {
    offsets_[static_cast<PixmapID>(i)] = QPoint(-5, -10);
    offsets_[static_cast<PixmapID>(i + kCarsPixmapsAmount)] = QPoint(-5, -16);
  }

  offsets_[PixmapID::kDeadCar] = QPoint(-5, -10);
  offsets_[PixmapID::kMine] = QPoint(-2, -2);
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
