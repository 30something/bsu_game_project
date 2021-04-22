#pragma once

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

class EndGameStats : public QWidget {
  Q_OBJECT

 public:
  explicit EndGameStats(QWidget* parent = nullptr);
  ~EndGameStats() override = default;

 signals:
  void ReturnToMainMenu();

 private:
  QLabel* stats_label_ = nullptr;
  QVBoxLayout* layout_ = nullptr;
  QPushButton* return_to_main_menu_button_ = nullptr;
};
