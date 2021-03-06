#include "view.h"

View::View(Model* model) :
    model_(model),
    map_(":resources/images/maps/map_1.jpg"),
    car_(":resources/images/cars/car_1.png") {
}

void View::Repaint(QPainter* painter) {
  // painter->save();
  painter->scale(3, 3);
  painter->drawImage(0,
                     0,
                     map_,
                     model_->GetCarCoordinates().first,
                     model_->GetCarCoordinates().second,
                     800,
                     800);
  painter->translate(400. / 3, 400. / 3);
  painter->rotate(-model_->GetCarAngle());
  painter->drawImage(-5, -5, car_);
  // painter->restore();
}
