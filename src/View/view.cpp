#include "src/View/view.h"

View::View(GameController* model, int map_index) :
    model_(model),
    car_(":resources/images/cars/car_1.png") {
  map_.load(map_data::map_filepaths[map_index].second);
}

void View::Repaint(QPainter* painter) {
  // Dis works only for 2 cars
  QSize size(painter->window().width(), painter->window().height());

  painter->scale(kScale, kScale);
  std::vector<std::pair<int, int>> coordinates_ = model_->GetCarCoordinates();
  std::vector<double> angles_ = model_->GetCarAngles();
  // Draw two maps
  painter->drawImage(0,
                     0,
                     map_,
                     coordinates_[0].first - size.width() / 2 / kScale / 2,
                     coordinates_[0].second - size.height() / kScale / 2,
                     size.width() / 2 / kScale,
                     size.height() / kScale);
  painter->drawImage(size.width() / 2 / kScale,
                     0,
                     map_,
                     coordinates_[1].first - size.width() / 2 / kScale / 2,
                     coordinates_[1].second - size.height() / kScale / 2,
                     size.width() / 2 / kScale,
                     size.height() / kScale);
  // Draw first car
  PaintCar(painter,
           size.width() / 4 / kScale,
           size.height() / 2 / kScale,
           angles_[0]);
  // draw second car on first map
  PaintCar(painter,
           coordinates_[1].first - coordinates_[0].first
               + size.width() / 2 / kScale / 2,
           coordinates_[1].second - coordinates_[0].second
               + size.height() / kScale / 2,
           angles_[1]);
  // draw second car
  PaintCar(painter,
           size.width() / 4. * 3 / kScale,
           size.height() / 2. / kScale,
           angles_[1]);
  // draw first car on second map
  painter->translate(size.width() / 2 / kScale, 0);
  PaintCar(painter,
           coordinates_[0].first - coordinates_[1].first
               + size.width() / 2 / kScale / 2,
           coordinates_[0].second - coordinates_[1].second
               + size.height() / kScale / 2,
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
