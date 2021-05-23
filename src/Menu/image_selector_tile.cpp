#include "image_selector_tile.h"

ImageSelectorTile::ImageSelectorTile(QWidget* parent, const QString& filename) :
    QWidget(parent) {
  LoadImage(filename);
}

ImageSelectorTile::~ImageSelectorTile() {
  delete pixmap_;
}

void ImageSelectorTile::LoadImage(const QString& filename) {
  QTransform trans;
  trans.rotate(90);
  delete pixmap_;
  auto transformed_pixmap = new QPixmap(filename);
  pixmap_ = new QPixmap(transformed_pixmap->transformed(trans));
  delete transformed_pixmap;
  setMinimumSize(pixmap_->width(), pixmap_->height());
  repaint();
}

void ImageSelectorTile::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  qp.drawPixmap(0, 0, *pixmap_, 0, 0, pixmap_->width(), pixmap_->height());
}
