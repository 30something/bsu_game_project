#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class MapSelectorTile : public QWidget {
 Q_OBJECT

 public:
  MapSelectorTile(QWidget* parent,
                  const QString& filename);
  ~MapSelectorTile() override = default;

 private:
  void paintEvent(QPaintEvent*) override;

  QPixmap* pixmap_ = nullptr;
  QWidget* parent_ = nullptr;
};
