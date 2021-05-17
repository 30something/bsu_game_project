#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include <cmath>

class ImageSelectorTile : public QWidget {
 Q_OBJECT

 public:
  ImageSelectorTile(QWidget* parent,
                    const QString& filename);
  ~ImageSelectorTile() override = default;

 private:
  void paintEvent(QPaintEvent*) override;

  QPixmap* pixmap_ = nullptr;
};
