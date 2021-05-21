#include "map_selector_tile.h"

MapSelectorTile::MapSelectorTile(QWidget* parent,
                                 const QString& filename) :
    QWidget(parent),
    pixmap_(new QPixmap(filename)),
    parent_(parent) {
  repaint();
}

void MapSelectorTile::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  qp.drawPixmap(QRect(0, 0, parent_->width(), parent_->height()), *pixmap_);
}
