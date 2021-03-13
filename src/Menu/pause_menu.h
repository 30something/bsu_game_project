#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class SmallExitWindow : public QWidget {

 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;

 private:
  QWidget* main_widget_;
  QLabel* question_;
  QPushButton* yes_button_;
  QPushButton* no_button_;
  int width_ = 250;
  int height_ = 100;
  friend class PauseMenu;
};

class PauseMenu : public QWidget {
  Q_OBJECT

 public:
  explicit PauseMenu(QWidget* parent = nullptr);
  ~PauseMenu() override = default;

 protected:
  void resizeEvent(QResizeEvent*) override;

 private:
  QVBoxLayout* main_layout_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  QPushButton* continue_button_;
  SmallExitWindow* small_exit_window_;
  int width_ = 500;
  int height_ = 500;
  friend class Controller;
};
