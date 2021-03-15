#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Menu : public QWidget {
  Q_OBJECT
 public:
  explicit Menu(QWidget* parent = nullptr);
  ~Menu() override = default;
  QPushButton* GetStartButton();
  QPushButton* GetExitButton();

 protected:
  void resizeEvent(QResizeEvent*) override;

 private:
  QVBoxLayout* main_layout_;
  QLabel* name_label_;
  QPushButton* start_game_button_;
  QPushButton* settings_button_;
  QPushButton* credits_button_;
  QPushButton* exit_button_;
  int width_ = 800;
  int height_ = 800;
};
