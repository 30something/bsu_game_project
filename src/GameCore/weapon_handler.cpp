#include "weapon_handler.h"

WeaponHandler::WeaponHandler(std::vector<Car>* cars) :
    cars_(cars) {
}

void WeaponHandler::ShotBullet(Car* car) {
  if (car->GetBulletsAmount() > 0) {
    for (auto& second_car : *cars_) {
      if (&second_car == car) {
        continue;
      }
      car->SetBulletsAmount(car->GetBulletsAmount() - 1);
      Line shoot_trajectory;
      shoot_trajectory.x1 = car->GetPosition().GetX();
      shoot_trajectory.y1 = car->GetPosition().GetY();
      shoot_trajectory.x2 =
          car->GetAngleVec().GetX() * kShootingRange
              + car->GetPosition().GetX();
      shoot_trajectory.y2 =
          car->GetAngleVec().GetY() * kShootingRange
              + car->GetPosition().GetY();
      std::vector<Line> car_lines = second_car.GetLines();
      for (const auto& line : car_lines) {
        if (Line::IsIntersects(shoot_trajectory, line)) {
          second_car.SetHitPoints(second_car.GetHitPoints() - kBulletDamage);
          break;
        }
      }
    }
  }
}

void WeaponHandler::PutMine(Car* car) {
  if (car->GetMinesAmount() > 0) {
    mines_.emplace_back(
        car->GetAngleVec().GetX() * (-15) + car->GetPosition().GetX(),
        car->GetAngleVec().GetY() * (-15) + car->GetPosition().GetY()
    );
    car->SetMinesAmount(car->GetMinesAmount() - 1);
  }
}

void WeaponHandler::ProceedWeapons() {
  for (auto& car : *cars_) {
    if (car.IsShooting()) {
      ShotBullet(&car);
    }
  }
  for (auto& mine : mines_) {
    for (auto& car : *cars_) {
      if (CarIsAboveMine(car, mine)) {
        car.SetHitPoints(car.GetHitPoints() - kMineDamage);
        car.SetVelocity(Vec2f(car.GetVelocity()).Normalize() * -100);
        mines_.erase(std::find(mines_.begin(), mines_.end(), mine));
      }
    }
  }
}

bool WeaponHandler::CarIsAboveMine(const Car& car, const QPoint& mine) {
  std::vector<Line> lines = car.GetLines();
  int p1 = Product(mine,
                   QPoint(lines[0].x1, lines[0].y1),
                   QPoint(lines[0].x2, lines[0].y2));
  int p2 = Product(mine,
                   QPoint(lines[0].x2, lines[0].y2),
                   QPoint(lines[1].x2, lines[1].y2));
  int p3 = Product(mine,
                   QPoint(lines[1].x2, lines[1].y2),
                   QPoint(lines[2].x2, lines[2].y2));
  int p4 = Product(mine,
                   QPoint(lines[2].x2, lines[2].y2),
                   QPoint(lines[0].x1, lines[0].y1));
  return ((p1 < 0 && p2 < 0 && p3 < 0 && p4 < 0) ||
      (p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0));
}

int WeaponHandler::Product(const QPoint& m,
                           const QPoint& p1,
                           const QPoint& p2) {
  return (p2.x() - p1.x()) * (m.y() - p1.y())
      - (p2.y() - p1.y()) * (m.x() - p1.x());
}

const std::vector<QPoint>& WeaponHandler::GetMines() const {
  return mines_;
}
