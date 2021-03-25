#include "src/View/view.h"

View::View(GameController* model) :
    model_(model),
    map_(":resources/images/maps/map_1.jpg"),
    car_(":resources/images/cars/car_1.png") {
}

void View::Repaint(QPainter* painter) {
  // painter->save();
  // painter->scale(3, 3);
  // painter->drawImage(0,
  //                    0,
  //                    map_,
  //                    model_->GetCarCoordinates().first - 400 / 3,
  //                    model_->GetCarCoordinates().second - 400 / 3,
  //                    painter->window().width(),
  //                    painter->window().height());
  // painter->translate(painter->window().width() / 6.0,
  //                    painter->window().height() / 6.0);
  // painter->rotate(model_->GetCarAngles());
  // // painter->scale(1/3, 1/3);
  // painter->drawImage(-5, -10, car_);
  // painter->restore();

  painter->drawImage(0,0,map_);
  std::vector<std::pair<int, int>> coordinates_ = model_->GetCarCoordinates();
  std::vector<double> angles_ = model_->GetCarAngles();
  for(size_t i = 0; i < coordinates_.size(); i++) {
    painter->save();
    painter->translate(coordinates_[i].first, coordinates_[i].second);
    painter->rotate(angles_[i]);
    painter->drawImage(-5, -10, car_);
    painter->restore();
  }
}
