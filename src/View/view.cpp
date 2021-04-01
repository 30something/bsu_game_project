#include "src/View/view.h"

View::View(QWidget* events_controller, GameController* model) :
    model_(model),
    map_(":resources/images/maps/map_1.jpg"),
    car_(":resources/images/cars/car_1.png"),
    engine_(new Engine(events_controller)),
    drift_(new Drift(events_controller)) {
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

void View::ChangeEngineVolume(double coefficient) {
    engine_->ChangeVolume(coefficient);
}

void View::PlayDrift(double coefficient) {
    drift_->Play(coefficient);
}
