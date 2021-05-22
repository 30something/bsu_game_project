#include "image_selector_tile.h"

ImageSelectorTile::ImageSelectorTile(QWidget* parent, const QString& filename) :
    QWidget(parent),
    pixmap_(new QPixmap(filename)) {
  QTransform transform;
  QTransform trans;
  trans = transform.rotate(90);
  pixmap_ = new QPixmap(pixmap_->transformed(trans));
  repaint();
  setMinimumSize(pixmap_->width(), pixmap_->height());
}

void ImageSelectorTile::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  qp.drawPixmap(0, 0, *pixmap_, 0, 0, pixmap_->width(), pixmap_->height());
}
