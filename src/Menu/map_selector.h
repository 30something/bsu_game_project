#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QImage>
#include <QStackedWidget>

#include "map_selector_tile.h"

class MapSelector : public QWidget {
 Q_OBJECT
 public:
  explicit MapSelector(QWidget* parent = nullptr);
  ~MapSelector() override = default;

  int GetMapId() const;

 signals:
  void StartGame();
  void ReturnToMainMenu();

 private:
  QPushButton start_game_;
  QPushButton back_to_main_menu_;
  QPushButton left_;
  QPushButton right_;
  QHBoxLayout layout_;
  QStackedWidget stacked_widget_;
  MapSelectorTile tile1;
  MapSelectorTile tile2;
  MapSelectorTile tile3;
  void SwitchRight();
  void SwitchLeft();
  int current_id = 0;
  const int kNumberOfMaps = 3;
};
