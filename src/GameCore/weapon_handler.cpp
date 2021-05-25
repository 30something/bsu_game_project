#include "weapon_handler.h"

void WeaponHandler::ShootBullet(Car* car, std::vector<Car>* cars) {
  std::optional<Line> shoot_trajectory = car->ShootBullet();
  if (shoot_trajectory) {
    for (auto& second_car : *cars) {
      if (&second_car == car) {
        continue;
      }
      std::vector<Line> car_lines = second_car.GetCollisionLines();
      for (const auto& line : car_lines) {
        if (physics::IsIntersects(*shoot_trajectory, line)) {
          second_car.AddHitPoints(-kBulletDamage);
          break;
        }
      }
    }
  }
}

void WeaponHandler::PutMine(Car* car) {
  std::optional<Vec2f> position = car->DropMine();
  if (position) {
    mines_.emplace_back(*position);
  }
}

void WeaponHandler::ProceedWeapons(
    std::vector<Car>* cars,
    std::vector<CarAchievements>* car_achievements,
    std::vector<Animation>* animations) {
  if (!enable_weapons_) {
    return;
  }
  for (size_t i = 0; i < cars->size(); i++) {
    if (cars->at(i).IsShooting()) {
      ShootBullet(&(cars->at(i)), cars);
      if (!(car_achievements->at(i).animation_of_shooting_state)) {
        car_achievements->at(i).animation_of_shooting_state = true;
        animations->emplace_back(
            AnimationTypes::kShooting, cars->at(i).GetPositionPointer(),
            cars->at(i).GetAngleVecPointer(),
            &(car_achievements->at(i).animation_of_shooting_state));
      }
    } else {
      car_achievements->at(i).animation_of_shooting_state = false;
    }
    if (cars->at(i).IsPuttingMine()) {
      PutMine(&(cars->at(i)));
    }
  }
  std::vector<bool> cars_on_mines(cars->size(), false);
  for (auto &mine : mines_) {
    if (!mine.IsExploded()) {
      for (uint32_t i = 0; i < cars->size(); i++) {
        if (physics::IsIntersects((*cars)[i].GetCollisionLines(),
                                  mine.GetCollisionLines())) {
          animations->emplace_back(AnimationTypes::kExplosion,
                                   mine.GetPosition());
          (*cars)[i].AddHitPoints(-kMineDamage);
          (*cars)[i].SetVelocity(
              Vec2f((*cars)[i].GetVelocity()).Normalize() *
                  -kMineSplash);
          mine.SetExploded();
          cars_on_mines[i] = true;
        }
      }
    }
    cars_on_mines_ = cars_on_mines;
  }
}

const std::vector<Mine>& WeaponHandler::GetMines() const {
  return mines_;
}

void WeaponHandler::SetEnableWeapons(bool enable_weapons) {
  enable_weapons_ = enable_weapons;
}

std::vector<bool> WeaponHandler::CarsOnMines() const {
    return cars_on_mines_;
}

bool WeaponHandler::GetEnableWeapons() const {
    return enable_weapons_;
}
