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
        if (physics::IsIntersects(*shoot_trajectory, line)) {
          second_car.AddHitPoints(-kBulletDamage);
          break;
        }
      }
    }
  }
}

void WeaponHandler::PutMine(Car* car) {
  std::optional<QPoint> position = car->DropMine();
  if (position) {
    mines_.emplace_back(*position);
  }
}

void WeaponHandler::ProceedWeapons(std::vector<Car>* cars) {
  for (auto& car : *cars) {
    if (car.IsShooting()) {
      ShootBullet(&car, cars);
    }
  }
  mine_is_exploded_ = false;
  for (auto& mine : mines_) {
    int index_of_car = 0;
    for (auto& car : *cars) {
      if (physics::IsInside(car.GetLines(), mine)) {
        car.AddHitPoints(-kMineDamage);
        car.SetVelocity(Vec2f(car.GetVelocity()).Normalize() * -kMineSplash);
        mines_.erase(std::find(mines_.begin(), mines_.end(), mine));
        if (index_of_car == 0) {
            mine_is_exploded_ = true;
        }
      }
      index_of_car++;
    }
  }
}

const std::vector<QPoint>& WeaponHandler::GetMinesCoordinates() const {
  return mines_;
}

bool WeaponHandler::MineIsExploded() const {
    return mine_is_exploded_;
}
