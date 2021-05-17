#pragma once

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "src/helpers/cars_data.h"

class EndGameStats : public QWidget {
  Q_OBJECT

 public:
  explicit EndGameStats(QWidget* parent = nullptr);
  ~EndGameStats() override = default;

  void UpdateStats(const CarsData& cars_data);

 signals:
  void ReturnToMainMenu();

 private:
  QLabel* stats_label_ = nullptr;
  QVBoxLayout* layout_ = nullptr;
  QVBoxLayout* positions_layout_ = nullptr;
  QPushButton* return_to_main_menu_button_ = nullptr;
};
