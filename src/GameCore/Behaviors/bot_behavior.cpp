#include "bot_behavior.h"
#include <iostream>
#include <utility>

BotBehavior::BotBehavior(const std::vector<std::vector<QPoint>>* borders,
                         const std::vector<Car>* cars,
                         const std::vector<Vec2f>* waypoints,
                         const std::vector<Line>* no_go_lines) :
    borders_(borders),
    cars_(cars),
    waypoints_(waypoints),
    no_go_lines_(no_go_lines) {
}

void BotBehavior::HandleTick(const GameObject* car) {
  car_ = dynamic_cast<const Car*>(car);
  closest_index_ = FindIndexOfClosestWaypoint(*car_);
  ProceedDistancesToBorders();
  ProceedCarFlags();
}

void BotBehavior::ProceedCarFlags() {
  flag_up_ = true;
  if (front_distance_ > left_distance_ && front_distance_ > right_distance_) {
    if (left_distance_ < 10) {
      flag_right_ = true;
      flag_left_ = false;
    } else if (right_distance_ < 10) {
      flag_right_ = false;
      flag_left_ = true;
    } else {
      flag_right_ = false;
      flag_left_ = false;
    }
  } else if (left_distance_ < right_distance_) {
    flag_right_ = true;
    flag_left_ = false;
  } else {
    flag_right_ = false;
    flag_left_ = true;
  }

  ProceedIfCorrectDirection();

  if (AnyCarInFront()) {
    flag_shoot_ = true;
  } else {
    flag_shoot_ = false;
  }
  if (AnyCarInBack()) {
    flag_mine_ = true;
  } else {
    flag_mine_ = false;
  }
  ProceedDistanceToPlayerCar();
}

void BotBehavior::ProceedIfCorrectDirection() {
  closest_index_ = FindIndexOfClosestWaypoint(*car_);
  size_t next_index =
      (closest_index_ == waypoints_->size() - 1 ? 0 : closest_index_ + 1);
  Vec2f vec_to_next(
      (*waypoints_)[next_index].GetX() - car_->GetPosition().GetX(),
      (*waypoints_)[next_index].GetY() - car_->GetPosition().GetY());
  if (std::abs(vec_to_next.GetAngleDegrees()
                   - car_->GetAngleVec().GetAngleDegrees()) > 90) {
    vec_to_next.Rotate(M_PI);
    // we need to rotate
    // now we need to determine in what direction to rotate
    if (vec_to_next.AngleBetween(car_->GetAngleVec()) > 0) {
      flag_left_ = true;
      flag_right_ = false;
    } else {
      flag_right_ = true;
      flag_left_ = false;
    }
  }
}

void BotBehavior::ProceedDistancesToBorders() {
  Vec2f car_angle_vec = car_->GetAngleVec();
  Vec2f car_position = car_->GetPosition();

  Vec2f front_angle_vec = car_angle_vec;
  front_distance_ =
      FindMinDistanceToBorder(front_angle_vec, car_position);

  Vec2f left_angle_vec = car_angle_vec;
  left_angle_vec.Rotate(-M_PI / 4);
  left_distance_ =
      FindMinDistanceToBorder(left_angle_vec, car_position);

  Vec2f right_angle_vec = car_angle_vec;
  right_angle_vec.Rotate(M_PI / 4);
  right_distance_ =
      FindMinDistanceToBorder(right_angle_vec, car_position);
}

double BotBehavior::FindMinDistanceToBorder(Vec2f angle_vec,
                                            Vec2f car_position) {
  std::vector<double> distances;
  Line search_line(
      car_position.GetX(),
      car_position.GetY(),
      car_position.GetX() + kDistanceRange * angle_vec.GetX(),
      car_position.GetY() + kDistanceRange * angle_vec.GetY());
  for (const auto& border : *borders_) {
    for (size_t j = 0; j < border.size(); j++) {
      size_t border_i = (j == (border.size()) - 1 ? 0 : j + 1);
      Line border_line(
          border[j].x(),
          border[j].y(),
          border[border_i].x(),
          border[border_i].y());
      if (physics::IsIntersects(search_line, border_line)) {
        Vec2f point = physics::FindIntersectionPoint(search_line, border_line);
        distances.push_back(physics::Distance(QPoint(point.GetX(),
                                                     point.GetY()),
                                              QPoint(car_position.GetX(),
                                                     car_position.GetY())));
      }
    }
  }
  for (auto line : *no_go_lines_) {
    if (physics::IsIntersects(search_line, line)) {
      Vec2f point = physics::FindIntersectionPoint(search_line, line);
      distances.push_back(physics::Distance(QPoint(point.GetX(),
                                                   point.GetY()),
                                            QPoint(car_position.GetX(),
                                                   car_position.GetY())));
    }
  }
  if (distances.empty()) {
    return kDistanceRange;
  }
  return *std::min_element(distances.begin(), distances.end());
}

bool BotBehavior::AnyCarInFront() const {
  Vec2f position = car_->GetPosition();
  Vec2f angle_vec = car_->GetAngleVec();
  Line shooting_trajectory(
      position.GetX(),
      position.GetY(),
      angle_vec.GetX() * kWeaponsRange + position.GetX(),
      angle_vec.GetY() * kWeaponsRange + position.GetY());
  return CheckCarInDirection(shooting_trajectory);
}

bool BotBehavior::AnyCarInBack() const {
  Vec2f position = car_->GetPosition();
  Vec2f angle_vec = car_->GetAngleVec();
  Line shooting_trajectory(
      position.GetX(),
      position.GetY(),
      -angle_vec.GetX() * kWeaponsRange + position.GetX(),
      -angle_vec.GetY() * kWeaponsRange + position.GetY());
  return CheckCarInDirection(shooting_trajectory);
}

size_t BotBehavior::FindIndexOfClosestWaypoint(const Car& car) const {
  std::vector<double> distances;
  for (auto waypoint : *waypoints_) {
    distances.push_back(physics::Distance(QPoint(waypoint.GetX(),
                                                 waypoint.GetY()),
                                          QPoint(car.GetPosition().GetX(),
                                                 car.GetPosition().GetY())));
  }
  size_t minimal_index = 0;
  for (size_t i = 0; i < distances.size(); i++) {
    if (distances[i] < distances[minimal_index]) {
      minimal_index = i;
    }
  }
  return minimal_index;
}

bool BotBehavior::CheckCarInDirection(Line shooting_trajectory) const {
  for (const auto& car : *cars_) {
    if (car.GetPosition() == car_->GetPosition()) {
      continue;
    }
    auto car_lines = car.GetCollisionLines();
    for (const auto& line : car_lines) {
      if (physics::IsIntersects(line, shooting_trajectory)) {
        return true;
      }
    }
  }
  return false;
}

void BotBehavior::ProceedDistanceToPlayerCar() {
  size_t car_closest_index = FindIndexOfClosestWaypoint((*cars_)[0]);
  size_t speed_coefficient =
      std::abs(static_cast<int64_t>(closest_index_ - car_closest_index));
  if (speed_coefficient > waypoints_->size() - 2) {
    speed_coefficient -= waypoints_->size();
  }
  speed_coefficient *= kSpeedCoefficientMultiplier;
  if (closest_index_ > car_closest_index) {
    max_speed_ = kMaxSpeed - speed_coefficient;
  }
  if (closest_index_ < car_closest_index) {
    max_speed_ = kMaxSpeed + speed_coefficient;
  }
  if (closest_index_ == car_closest_index) {
    max_speed_ = kMaxSpeed;
  }
}
