#include "map.h"

Map::Map( JsonOurParser* parser) :
    parser_(parser) {
  borders_ = parser_->GetBorders();
}

void Map::ProceedCollisions(Car* car) {
  // For every line of the car find the interceptions
  // with every line of the borders
  auto lines = car->GetLines();
  for (int i = 0; i < 4; i++) {
    for (const auto& border : borders_) {
      for (size_t j = 0; j < border.size(); j++) {
        Line l2;
        size_t border_i = (j == (border.size()) - 1 ? 0 : j + 1);
        l2.x1 = border[j].x();
        l2.y1 = border[j].y();
        l2.x2 = border[border_i].x();
        l2.y2 = border[border_i].y();
        if (Line::IsIntersects(lines[i], l2)) {
          Vec2f point = Line::FindIntersectionPoint(lines[i], l2);
          CollideCar(car, point);
          return;
        }
      }
    }
  }
}

void Map::CollideCar(Car* car, const Vec2f& point) {
  Vec2f position = car->GetPosition();
  car->SetHitPoints(
      car->GetHitPoints() - car->GetVelocity().GetLength() * kHPDecrease);
  Vec2f deviation
      (position.GetX() - point.GetX(), position.GetY() - point.GetY());
  deviation.Normalize();
  Vec2f velocity = car->GetVelocity()
      + deviation * physics::kCollisionDeviationScalar;
  velocity *= kVelocityDecrease;
  car->SetVelocity(velocity);
  car->SetPosition(position + deviation);
}
