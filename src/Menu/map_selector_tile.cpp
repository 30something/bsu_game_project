#include "map_selector_tile.h"

MapSelectorTile::MapSelectorTile(QWidget* parent,
                                 const QString& filename) :
    QWidget(parent),
    pixmap_(new QPixmap(filename)) {
  repaint();
  setMinimumSize(400, 400);
}

void MapSelectorTile::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  qp.scale(0.5, 0.5);
  qp.drawPixmap(0, 0, *pixmap_, 800, 800, 1000, 1000);
}
