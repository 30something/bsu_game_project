#include "weapon_handler.h"

void WeaponHandler::ShootBullet(Car* car, std::vector<Car>* cars) {
  std::optional<Line> shoot_trajectory = car->ShootBullet();
  if (shoot_trajectory) {
    for (auto& second_car : *cars) {
      if (&second_car == car) {
        continue;
      }
      std::vector<Line> car_lines = second_car.GetLines();
      for (const auto& line : car_lines) {
        if (Physics::IsIntersects(*shoot_trajectory, line)) {
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

void WeaponHandler::ProceedWeapons(std::vector<Car>* cars) {
  for (auto& car : *cars) {
    if (car.IsShooting()) {
      ShootBullet(&car, cars);
    }
    if(car.IsPuttingMine()) {
      PutMine(&car);
    }
  }
  for (const auto& mine : mines_) {
    for (auto& car : *cars) {
      if (Physics::IsInside(car.GetLines(), QPoint(mine.GetPosition().GetX(), mine.GetPosition().GetY()))) {
        car.AddHitPoints(-kMineDamage);
        car.SetVelocity(Vec2f(car.GetVelocity()).Normalize() * -kMineSplash);
        mines_.erase(std::find(mines_.begin(), mines_.end(), mine));
      }
    }
  }
}

const std::vector<Mine>& WeaponHandler::GetMines() const {
  return mines_;
}
