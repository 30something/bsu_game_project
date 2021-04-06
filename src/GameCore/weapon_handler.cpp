#include "weapon_handler.h"

void WeaponHandler::ShootBullet(Car* car, std::vector<Car>* cars) {
  for (auto& second_car : *cars) {
    if (&second_car == car) {
      continue;
    }
    bool successful_shot = false;
    Line shoot_trajectory = car->ShootBullet(&successful_shot);
    if (successful_shot) {
      std::vector<Line> car_lines = second_car.GetLines();
      for (const auto& line : car_lines) {
        if (Physics::IsIntersects(shoot_trajectory, line)) {
          second_car.AddHitPoints(-kBulletDamage);
          break;
        }
      }
    }
  }
}

void WeaponHandler::PutMine(Car* car) {
  bool successful_drop = false;
  QPoint position = car->DropMine(&successful_drop);
  if(successful_drop) {
    mines_.emplace_back(position);
  }
}

void WeaponHandler::ProceedWeapons(std::vector<Car>* cars) {
  for (auto& car : *cars) {
    if (car.IsShooting()) {
      ShootBullet(&car, cars);
    }
  }
  for (auto& mine : mines_) {
    for (auto& car : *cars) {
      if (Physics::IsInside(car.GetLines(), mine)) {
        car.AddHitPoints(-kMineDamage);
        car.SetVelocity(Vec2f(car.GetVelocity()).Normalize() * -kMineSplash);
        mines_.erase(std::find(mines_.begin(), mines_.end(), mine));
      }
    }
  }
}

const std::vector<QPoint>& WeaponHandler::GetMinesCoordinates() const {
  return mines_;
}
