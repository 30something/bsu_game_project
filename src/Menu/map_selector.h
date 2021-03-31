#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "map_selector_tile.h"
#include "src/helpers/map_data.h"

class MapSelector : public QWidget {
  Q_OBJECT

 public:
  explicit MapSelector(QWidget* parent = nullptr);
  ~MapSelector() override = default;

  uint GetMapId() const;

 signals:
  void StartGame();
  void ReturnToMainMenu();

 private:
  void SetUpLayout();
  void ConnectUI();

  void SwitchRight();
  void SwitchLeft();

  QPushButton* start_game_;
  QPushButton* back_to_main_menu_;
  QPushButton* left_;
  QPushButton* right_;
  QHBoxLayout* layout_;
  QStackedWidget* stacked_widget_;
  uint current_id = 0;
};
