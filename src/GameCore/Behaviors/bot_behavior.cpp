#include "bot_behavior.h"
#include <iostream>

BotBehavior::BotBehavior(std::vector <std::vector<QPoint>> borders,
                         const std::vector <Car>* cars,
                         const std::vector <Bonus>* bonuses,
                         const std::vector <Mine>* mines,
                         const std::vector <Vec2f>& waypoints,
                         const std::vector <Line>& no_go_lines) :
    borders_(std::move(borders)),
    cars_(cars),
    bonuses_(bonuses),
    mines_(mines),
    waypoints_(waypoints),
    no_go_lines_(no_go_lines) {
}

void BotBehavior::HandleTick(const GameObject* car) {
  car_ = dynamic_cast<const Car*>(car);
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

  size_t closest_index = FindIndexOfClosestWaypoint();
  size_t next_index =
      (closest_index == waypoints_.size() - 1 ? 0 : closest_index + 1);
  Vec2f
      vec_to_next(waypoints_.at(next_index).GetX() - car_->GetPosition().GetX(),
                  waypoints_.at(next_index).GetY()
                      - car_->GetPosition().GetY());
  if (std::abs(
        vec_to_next.GetAngleDegrees() - car_->GetAngleVec().GetAngleDegrees())
        > 90) {
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
}

void BotBehavior::ProceedDistancesToBorders() {
  Vec2f front_angle_vec = car_->GetAngleVec();
  front_distance_ =
      FindMinDistanceToBorder(front_angle_vec, car_->GetPosition());
  Vec2f back_angle_vec = car_->GetAngleVec();
  back_angle_vec.Rotate(M_PI);
  back_distance_ = FindMinDistanceToBorder(back_angle_vec, car_->GetPosition());
  Vec2f left_angle_vec = car_->GetAngleVec();
  left_angle_vec.Rotate(-M_PI / 4);
  left_distance_ = FindMinDistanceToBorder(left_angle_vec, car_->GetPosition());
  Vec2f right_angle_vec = car_->GetAngleVec();
  right_angle_vec.Rotate(M_PI / 4);
  right_distance_ =
      FindMinDistanceToBorder(right_angle_vec, car_->GetPosition());
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
  for (auto line : no_go_lines_) {
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
  for (const auto& car : *cars_) {
    if (car.GetPosition() == car_->GetPosition()) {
      continue;
    }
    auto car_lines = car.GetCollisionLines();
    Line shooting_trajectory(
        car_->GetPosition().GetX(),
        car_->GetPosition().GetY(),
        car_->GetAngleVec().GetX() * kShootingRange
            + car_->GetPosition().GetX(),
        car_->GetAngleVec().GetY() * kShootingRange
            + car_->GetPosition().GetY());
    for (const auto& line : car_lines) {
      if (physics::IsIntersects(line, shooting_trajectory)) {
        return true;
      }
    }
  }
  return false;
}

bool BotBehavior::AnyCarInBack() const {
  for (const auto& car : *cars_) {
    if (car.GetPosition() == car_->GetPosition()) {
      continue;
    }
    auto car_lines = car.GetCollisionLines();
    Line shooting_trajectory(
        car_->GetPosition().GetX(),
        car_->GetPosition().GetY(),
        -car_->GetAngleVec().GetX() * kMineRange + car_->GetPosition().GetX(),
        -car_->GetAngleVec().GetY() * kMineRange + car_->GetPosition().GetY());
    for (const auto& line : car_lines) {
      if (physics::IsIntersects(line, shooting_trajectory)) {
        return true;
      }
    }
  }
  return false;
}

size_t BotBehavior::FindIndexOfClosestWaypoint() {
  std::vector<double> distances;
  for (auto waypoint : waypoints_) {
    distances.push_back(physics::Distance(QPoint(waypoint.GetX(),
                                                 waypoint.GetY()),
                                          QPoint(car_->GetPosition().GetX(),
                                                 car_->GetPosition().GetY())));
  }
  size_t minimal_index = 0;
  for (size_t i = 0; i < distances.size(); i++) {
    if (distances[i] < distances[minimal_index]) {
      minimal_index = i;
    }
  }
  return minimal_index;
}