#include "src/View/view.h"

View::View(GameController* model, int map_index) :
    model_(model),
    car_(":resources/images/cars/car_1.png") {
  map_.load(map_data::map_filepaths[map_index].second);
}

void View::Repaint(QPainter* painter) {
  // Dis works only for 2 cars
  double width = painter->window().width();
  double height = painter->window().height();

  painter->scale(kScaleFactor, kScaleFactor);
  std::vector<std::pair<int, int>> coordinates_ = model_->GetCarCoordinates();
  std::vector<double> angles_ = model_->GetCarAngles();
  // Draw two maps
  painter->drawImage(0,
                     0,
                     map_,
                     coordinates_[0].first - width / 2 / kScaleFactor / 2,
                     coordinates_[0].second - height / kScaleFactor / 2,
                     width / 2 / kScaleFactor,
                     height / kScaleFactor);
  painter->drawImage(width / 2 / kScaleFactor,
                     0,
                     map_,
                     coordinates_[1].first - width / 2 / kScaleFactor / 2,
                     coordinates_[1].second - height / kScaleFactor / 2,
                     width / 2 / kScaleFactor,
                     height / kScaleFactor);
  // Draw first car
  painter->save();
  painter->translate(width / 4 / kScaleFactor,
                     height / 2. / kScaleFactor);
  painter->rotate(angles_[0]);
  painter->drawImage(-5, -10, car_);
  painter->restore();
  // draw second car on first map
  painter->save();
  painter->translate(
      coordinates_[1].first - coordinates_[0].first
          + width / 2 / kScaleFactor / 2,
      coordinates_[1].second - coordinates_[0].second
          + height / kScaleFactor / 2);
  painter->rotate(angles_[1]);
  painter->drawImage(-5, -10, car_);
  painter->restore();
  // draw second car
  painter->save();
  painter->translate(width / 4. * 3 / kScaleFactor,
                     height / 2. / kScaleFactor);
  painter->rotate(angles_[1]);
  painter->drawImage(-5, -10, car_);
  painter->restore();
  // draw first car on second map
  painter->save();
  painter->translate(width / 2 / kScaleFactor, 0);
  painter->translate(
      coordinates_[0].first - coordinates_[1].first
          + width / 2 / kScaleFactor / 2,
      coordinates_[0].second - coordinates_[1].second
          + height / kScaleFactor / 2);
  painter->rotate(angles_[0]);
  painter->drawImage(-5, -10, car_);
  painter->restore();
}
