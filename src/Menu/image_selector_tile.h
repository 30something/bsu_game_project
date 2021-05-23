#pragma once

#include <cmath>

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class ImageSelectorTile : public QWidget {
  Q_OBJECT

 public:
  ImageSelectorTile(QWidget* parent, const QString& filename);
  ~ImageSelectorTile() override;
  void LoadImage(const QString& filename);

 private:
  void paintEvent(QPaintEvent*) override;
  QPixmap* pixmap_ = nullptr;
};
