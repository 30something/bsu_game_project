#pragma once

#include <cmath>

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class ImageSelectorTile : public QWidget {
  Q_OBJECT

 public:
  ImageSelectorTile(QWidget* parent,
                    const QString& filename);
  ~ImageSelectorTile() override = default;

 private:
  void paintEvent(QPaintEvent*) override;

  QPixmap* pixmap_ = nullptr;
  static constexpr int32_t kImageOffsetX = 0;
  static constexpr int32_t kImageOffsetY = 6;
};
