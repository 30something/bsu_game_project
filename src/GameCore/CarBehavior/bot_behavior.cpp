#include "bot_behavior.h"

BotBehavior::BotBehavior(std::vector<std::vector<QPoint>> borders) :
    borders_(std::move(borders)) {}

void BotBehavior::HandleTick(GameObject* object) {
  Car* car = dynamic_cast<Car*>(object);
  ProceedDistancesToBorders(car);
  car->SetFlagUp(true);
  if(front_distance_ > left_distance_ && front_distance_ > right_distance_) {
    car->SetFlagRight(false);
    car->SetFlagLeft(false);
  } else if (left_distance_ < right_distance_) {
    car->SetFlagRight(true);
    car->SetFlagLeft(false);
  } else {
    car->SetFlagLeft(true);
    car->SetFlagRight(false);
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
  double min = distances.at(0);
  for(double distance : distances) {
    if(distance < min) {
      min = distance;
    }
  }
  return min;
}
