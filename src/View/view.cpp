#include "src/View/view.h"

View::View(GameController* model, int map_index) :
    model_(model),
    car_(":resources/images/cars/car_1.png") {
  switch (map_index) {
    case 0: {
      map_.load(":resources/images/maps/map_1.jpg");
      break;
    }
    case 1: {
      map_.load(":resources/images/maps/map_2.jpg");
      break;
    }
    case 2: {
      map_.load(":resources/images/maps/map_3.jpg");
      break;
    }
    default: {
      qWarning("Something went wrong with view");
    }
  }
}

void View::Repaint(QPainter* painter) {
  painter->drawImage(0, 0, map_);
  std::vector<std::pair<int, int>> coordinates_ = model_->GetCarCoordinates();
  std::vector<double> angles_ = model_->GetCarAngles();
  for (size_t i = 0; i < coordinates_.size(); i++) {
    painter->save();
    painter->translate(coordinates_[i].first, coordinates_[i].second);
    painter->rotate(angles_[i]);
    painter->drawImage(-5, -10, car_);
    painter->restore();
  }
}
