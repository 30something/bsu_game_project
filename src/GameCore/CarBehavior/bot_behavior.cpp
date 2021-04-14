#include "bot_behavior.h"

BotBehavior::BotBehavior(std::vector<std::vector<QPoint>> borders,
                         const std::vector<Car>* cars,
                         const std::vector<Bonus>* bonuses,
                         const std::vector<Mine>* mines) :
    borders_(std::move(borders)),
    cars_(cars),
    bonuses_(bonuses),
    mines_(mines) {}

void BotBehavior::HandleTick(GameObject* object) {
  Car* car = dynamic_cast<Car*>(object);
  ProceedDistancesToBorders(car);
  ProceedCarFlags(car);
}

void BotBehavior::ProceedCarFlags(Car* car) const {
  car->SetFlagUp(true);
  if (front_distance_ > left_distance_ && front_distance_ > right_distance_) {
    car->SetFlagRight(false);
    car->SetFlagLeft(false);
  } else if (left_distance_ < right_distance_) {
    car->SetFlagRight(true);
    car->SetFlagLeft(false);
  } else {
    car->SetFlagLeft(true);
    car->SetFlagRight(false);
  }
  if(AnyCarInFront(car)) {
    car->SetIsShooting(true);
  } else {
    car->SetIsShooting(false);
  }
  if(AnyCarInBack(car)) {
    car->SetIsPuttingMine(true);
  }
}

void BotBehavior::HandleKeyPressEvent(GameObject*, QKeyEvent*) {}

void BotBehavior::HandleKeyReleaseEvent(GameObject*, QKeyEvent*) {}

void BotBehavior::ProceedDistancesToBorders(Car* car) {
  Vec2f front_angle_vec = car->GetAngleVec();
  front_distance_ =
      FindMinDistanceToBorder(front_angle_vec, car->GetPosition());
  Vec2f back_angle_vec = car->GetAngleVec();
  back_angle_vec.Rotate(M_PI);
  back_distance_ = FindMinDistanceToBorder(back_angle_vec, car->GetPosition());
  Vec2f left_angle_vec = car->GetAngleVec();
  left_angle_vec.Rotate(-M_PI / 4);
  left_distance_ = FindMinDistanceToBorder(left_angle_vec, car->GetPosition());
  Vec2f right_angle_vec = car->GetAngleVec();
  right_angle_vec.Rotate(M_PI / 4);
  right_distance_ =
      FindMinDistanceToBorder(right_angle_vec, car->GetPosition());
}

double BotBehavior::FindMinDistanceToBorder(Vec2f angle_vec,
                                            Vec2f car_position) {
  std::vector<double> distances;
  Line search_line(
      car_position.GetX(),
      car_position.GetY(),
      car_position.GetX() + kDistanceRange * angle_vec.GetX(),
      car_position.GetY() + kDistanceRange * angle_vec.GetY()
  );
  for (const auto& border : borders_) {
    for (size_t j = 0; j < border.size(); j++) {
      size_t border_i = (j == (border.size()) - 1 ? 0 : j + 1);
      Line border_line(
          border[j].x(),
          border[j].y(),
          border[border_i].x(),
          border[border_i].y()
      );
      if (physics::IsIntersects(search_line, border_line)) {
        Vec2f point = physics::FindIntersectionPoint(search_line, border_line);
        distances.push_back(physics::Distance(QPoint(point.GetX(),
                                                     point.GetY()),
                                              QPoint(car_position.GetX(),
                                                     car_position.GetY())));
      }
    }
  }
  if (distances.empty()) {
    return kDistanceRange;
  }
  return *std::min_element(distances.begin(), distances.end());
}

bool BotBehavior::AnyCarInFront(Car* our_car) const {
  for(const auto& car : *cars_) {
    if(car.GetPosition() == our_car->GetPosition()) {
      continue;
    }
    auto car_lines = car.GetLines();
    Line shooting_trajectory(
        our_car->GetPosition().GetX(),
        our_car->GetPosition().GetY(),
        our_car->GetAngleVec().GetX() * kShootingRange + our_car->GetPosition().GetX(),
        our_car->GetAngleVec().GetY() * kShootingRange + our_car->GetPosition().GetY());
    for(const auto& line : car_lines) {
      if(physics::IsIntersects(line, shooting_trajectory)) {
        return true;
      }
    }
  }
  return false;
}

bool BotBehavior::AnyCarInBack(Car* our_car) const {
  for(const auto& car : *cars_) {
    if(car.GetPosition() == our_car->GetPosition()) {
      continue;
    }
    auto car_lines = car.GetLines();
    Line shooting_trajectory(
        our_car->GetPosition().GetX(),
        our_car->GetPosition().GetY(),
        -our_car->GetAngleVec().GetX() * kMineRange + our_car->GetPosition().GetX(),
        -our_car->GetAngleVec().GetY() * kMineRange + our_car->GetPosition().GetY());
    for(const auto& line : car_lines) {
      if(physics::IsIntersects(line, shooting_trajectory)) {
        return true;
      }
    }
  }
  return false;
}
