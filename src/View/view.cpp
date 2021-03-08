#include "src/View/view.h"

View::View(Model* model) :
    model_(model),
    map_(":resources/images/maps/map_1.jpg"),
    car_(":resources/images/cars/car_1.png") {
}

void View::Repaint(QPainter* painter) {
  painter->save();
  painter->scale(3, 3);
  painter->drawImage(0,
                     0,
                     map_,
                     model_->GetCarCoordinates().first,
                     model_->GetCarCoordinates().second,
                     painter->window().width(),
                     painter->window().height());
  painter->translate(painter->window().width() / 6.0,
                     painter->window().height() / 6.0);
  painter->rotate(model_->GetCarAngle());
  painter->drawImage(-5, -10, car_);
  painter->restore();
}
