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

  painter->scale(kScale, kScale);
  std::vector<std::pair<int, int>> coordinates_ = model_->GetCarCoordinates();
  std::vector<double> angles_ = model_->GetCarAngles();
  // Draw two maps
  painter->drawImage(0,
                     0,
                     map_,
                     coordinates_[0].first - width / 2 / kScale / 2,
                     coordinates_[0].second - height / kScale / 2,
                     width / 2 / kScale,
                     height / kScale);
  painter->drawImage(width / 2 / kScale,
                     0,
                     map_,
                     coordinates_[1].first - width / 2 / kScale / 2,
                     coordinates_[1].second - height / kScale / 2,
                     width / 2 / kScale,
                     height / kScale);
  // Draw first car
  PaintCar(painter,
           width / 4 / kScale,
           height / 2 / kScale,
           angles_[0]);
  // draw second car on first map
  PaintCar(painter,
           coordinates_[1].first - coordinates_[0].first
               + width / 2 / kScale / 2,
           coordinates_[1].second - coordinates_[0].second
               + height / kScale / 2,
           angles_[1]);
  // draw second car
  PaintCar(painter,
           width / 4. * 3 / kScale,
           height / 2. / kScale,
           angles_[1]);
  // draw first car on second map
  painter->translate(width / 2 / kScale, 0);
  PaintCar(painter,
           coordinates_[0].first - coordinates_[1].first
               + width / 2 / kScale / 2,
           coordinates_[0].second - coordinates_[1].second
               + height / kScale / 2,
           angles_[0]);
}

void View::PaintCar(QPainter* painter,
                    double width,
                    double height,
                    double angle) const {
  painter->save();
  painter->translate(width, height);
  painter->rotate(angle);
  painter->drawImage(-5, -10, car_);
  painter->restore();
}
