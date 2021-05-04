#pragma once

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include "network_player.h"

class PlayerTile : public QWidget {
 Q_OBJECT
 public:
  PlayerTile(QWidget* parent, const NetworkPlayer* player);
  void Highlight();

 private:
  const NetworkPlayer* player_;
  QLabel* nickname_;
  QLabel* is_ready_;
  QHBoxLayout* main_layout_;
};
