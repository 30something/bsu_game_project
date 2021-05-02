#include "pixmap_loader.h"
#include <iostream>

PixmapLoader::PixmapLoader(const QString& filepath) : map_filepath_(filepath) {
  InitPixmaps();
}

void PixmapLoader::InitPixmaps() {
  QFileInfoList standard_cars_list =
      QDir(":resources/images/cars/standard_cars").entryInfoList();
  for (const auto& file : standard_cars_list) {
    cars_pixmaps_[CarStates::kStandard].emplace_back(QPixmap(file.filePath()),
                                                     QPoint(-5, -10));
  }
  QFileInfoList shooting_cars_list =
      QDir(":resources/images/cars/shooting_cars").entryInfoList();
  for (const auto& file : shooting_cars_list) {
    cars_pixmaps_[CarStates::kShooting].emplace_back(QPixmap(file.filePath()),
                                                     QPoint(-5, -16));
  }

  QString basic_path = ":resources/images/";
  QPixmap dead_car(basic_path + "cars/car_dead.png");
  QPixmap mine(basic_path + "other_stuff/mine.png");
  QPixmap exploded_mine(basic_path + "other_stuff/exploded_mine.png");
  QPixmap health_bonus(basic_path + "other_stuff/hp.png");
  QPixmap bullets_ammo_bonus(basic_path + "other_stuff/ammo.png");
  QPixmap mines_bonus(basic_path + "other_stuff/mines_ammo.png");
  map_pixmap_ = QPixmap(map_filepath_);

  cars_pixmaps_[CarStates::kDead].emplace_back(dead_car,
                                               QPoint(-5, -10));
  mines_pixmaps_[MineStates::kStandard].emplace_back(mine,
                                                     QPoint(-2, -2));
  mines_pixmaps_[MineStates::kExploded].emplace_back(exploded_mine,
                                                     QPoint(-2, -2));
  bonuses_pixmaps_[BonusStates::kHealth].emplace_back(health_bonus,
                                                      QPoint(-5, -5));
  bonuses_pixmaps_[BonusStates::kBulletsAmmo].emplace_back(bullets_ammo_bonus,
                                                           QPoint(-5, -5));
  bonuses_pixmaps_[BonusStates::kMineAmmo].emplace_back(mines_bonus,
                                                        QPoint(-5, -5));
}

const std::pair<QPixmap, QPoint>& PixmapLoader::GetPixmap(PixmapID id) {
  auto pixmap_category = static_cast<PixmapCategories>(id >> 24);
  int32_t state_value = (id << 8) >> 24;
  int32_t pixmap_number = (id << 16) >> 16;
  switch (pixmap_category) {
    case PixmapCategories::kCar: {
      auto pixmap_state = static_cast<CarStates>(state_value);
      return cars_pixmaps_[pixmap_state][pixmap_number];
    }
    case PixmapCategories::kMine: {
      auto pixmap_state = static_cast<MineStates>(state_value);
      return mines_pixmaps_[pixmap_state][pixmap_number];
    }
    default: {
      auto pixmap_state = static_cast<BonusStates>(state_value);
      return bonuses_pixmaps_[pixmap_state][pixmap_number];
    }
  }
}

const QPixmap& PixmapLoader::GetMapPixmap() {
  return map_pixmap_;
}
