#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

class Menu : public QWidget {
  Q_OBJECT

 public:
  explicit Menu(QWidget* parent = nullptr);
  ~Menu() override = default;

 signals:
  void StartButtonPressed();
  void ExitButtonPressed();

 private:
  QVBoxLayout* main_layout_;
  QLabel* name_label_;
  QPushButton* start_game_button_;
  QPushButton* settings_button_;
  QPushButton* credits_button_;
  QPushButton* exit_button_;
};
