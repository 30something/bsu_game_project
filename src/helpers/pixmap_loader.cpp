#include <iostream>
#include "pixmap_loader.h"

PixmapLoader::PixmapLoader(const QString& filepath) : map_filepath_(filepath) {
  InitPixmaps();
}

void PixmapLoader::InitPixmaps() {
  QFileInfoList standard_cars_list =
      QDir(":resources/images/cars/standard_cars").entryInfoList();
  for (const auto& standard_car : standard_cars_list) {
    cars_pixmaps_[CarStates::kStandard].emplace_back(
        QPixmap(standard_car.filePath()));
  }

  QFileInfoList animations_folders_list =
      QDir(":resources/images/images_for_animations").entryInfoList();
  auto animation_type = static_cast<AnimationTypes>(0);
  for (const auto& folder : animations_folders_list) {
    QFileInfoList animation_list = QDir(folder.filePath()).entryInfoList();
    for (const auto& animation_frame : animation_list) {
      animation_pixmaps_[animation_type].emplace_back(QPixmap(
          animation_frame.filePath()));
    }
    animation_type =
        static_cast<AnimationTypes>(static_cast<int>(animation_type) + 1);
  }

  QString basic_path = ":resources/images/";
  map_pixmap_ = QPixmap(map_filepath_);

  cars_pixmaps_[CarStates::kDead].emplace_back(
      QPixmap(basic_path + "cars/car_dead.png"));
  cars_pixmaps_[CarStates::kDamaged].emplace_back(
      QPixmap(basic_path + "cars/damaged_car.png"));
  cars_pixmaps_[CarStates::kHealthy].emplace_back(
      QPixmap(basic_path + "cars/healthy_car.png"));
  mines_pixmaps_[MineStates::kStandard].emplace_back(
      QPixmap(basic_path + "other_stuff/mine.png"));
  mines_pixmaps_[MineStates::kExploded].emplace_back(
      QPixmap(basic_path + "other_stuff/explosion_trace.png"));
  bonuses_pixmaps_[BonusTypes::kHealth].emplace_back(
      QPixmap(basic_path + "other_stuff/hp.png"));
  bonuses_pixmaps_[BonusTypes::kBulletsAmmo].emplace_back(
      QPixmap(basic_path + "other_stuff/ammo.png"));
  bonuses_pixmaps_[BonusTypes::kMineAmmo].emplace_back(
      QPixmap(basic_path + "other_stuff/mines_ammo.png"));
}

const QPixmap& PixmapLoader::GetPixmap(PixmapID id) {
  auto pixmap_category =
      static_cast<PixmapCategories>(id >> kCategoryPixmapShift);
  int32_t state_value = (id & kStatePixmapMask) >> kStatePixmapShift;
  int32_t pixmap_number = id & kNumberPixmapMask;
  switch (pixmap_category) {
    case PixmapCategories::kCar: {
      auto pixmap_state = static_cast<CarStates>(state_value);
      if (pixmap_state == CarStates::kStandard) {
        return cars_pixmaps_[pixmap_state][pixmap_number];
      } else {
        return cars_pixmaps_[pixmap_state][0];
      }
    }
    case PixmapCategories::kMine: {
      auto pixmap_state = static_cast<MineStates>(state_value);
      return mines_pixmaps_[pixmap_state][pixmap_number];
    }
    case PixmapCategories::kBonus: {
      auto pixmap_state = static_cast<BonusTypes>(state_value);
      return bonuses_pixmaps_[pixmap_state][pixmap_number];
    }
    default: {
      auto pixmap_state = static_cast<AnimationTypes>(state_value);
      return animation_pixmaps_[pixmap_state][pixmap_number];
    }
  }
}

const QPixmap& PixmapLoader::GetMapPixmap() {
  return map_pixmap_;
}
