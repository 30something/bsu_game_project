#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>

class MapSelectorTile : public QWidget {
 Q_OBJECT
 public:
  MapSelectorTile(QWidget* parent,
                  const QString& filename,
                  const QString& name);
  ~MapSelectorTile() override = default;

 private:
  void paintEvent(QPaintEvent*) override;
  QPixmap* pixmap_ = nullptr;
  QLabel* name_ = nullptr;
};
