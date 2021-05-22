#include "weapon_handler.h"

void WeaponHandler::ShootBullet(Car *car, std::vector<Car> *cars) {
    std::optional<Line> shoot_trajectory = car->ShootBullet();
    if (shoot_trajectory) {
        for (auto &second_car : *cars) {
            if (&second_car == car) {
                continue;
            }
            std::vector<Line> car_lines = second_car.GetCollisionLines();
            for (const auto &line : car_lines) {
                if (physics::IsIntersects(*shoot_trajectory, line)) {
                    second_car.AddHitPoints(-kBulletDamage);
                    break;
                }
            }
        }
    }
}

void WeaponHandler::PutMine(Car *car) {
    std::optional<Vec2f> position = car->DropMine();
    if (position) {
        mines_.emplace_back(*position);
    }
}

void WeaponHandler::ProceedWeapons(std::vector<Car> *cars) {
    if (!enable_weapons_) {
        return;
    }
    for (auto &car : *cars) {
        if (car.IsShooting()) {
            ShootBullet(&car, cars);
        }
        if (car.IsPuttingMine()) {
            PutMine(&car);
        }
    }
    cars_on_mines_.clear();
    cars_on_mines_.reserve(cars->size());
    for (auto &mine : mines_) {
        if (!mine.IsExploded()) {
            for (auto &car : *cars) {
                if (physics::IsIntersects(car.GetCollisionLines(),
                                          mine.GetCollisionLines())) {
                    car.AddHitPoints(-kMineDamage);
                    car.SetVelocity(Vec2f(car.GetVelocity()).Normalize() *
                                    -kMineSplash);
                    mine.SetExploded();
                    cars_on_mines_.push_back(true);
                    continue;
                }
                cars_on_mines_.push_back(false);
            }
        }
    }
}

const std::vector<Mine> &WeaponHandler::GetMines() const {
    return mines_;
}

std::vector<bool> WeaponHandler::CarsOnMines() const {
    return cars_on_mines_;
}

void WeaponHandler::SetEnableWeapons(bool enable_weapons) {
    enable_weapons_ = enable_weapons;
}

bool WeaponHandler::GetEnableWeapons() const {
    return enable_weapons_;
}
