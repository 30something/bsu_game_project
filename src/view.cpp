#include "view.h"

void View::Repaint(QPainter* painter) {
  painter->save();
  // PaintCars(painter);
  // PaintMap(painter);
  // PaintAllTheOtherStuff(painter):
  painter->restore();
}
