#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class SmallExitWindow : public QWidget {
 Q_OBJECT

 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);

 protected:
  ~SmallExitWindow() override = default;

 private:
  QWidget* main_widget_;
  QLabel* question_;
  QPushButton* yes_button_;
  QPushButton* no_button_;
  int width_;
  int height_;
  friend class PauseMenu;
};

class PauseMenu : public QWidget {
 Q_OBJECT

 public:
  explicit PauseMenu(QWidget* parent = nullptr);

 protected:
  ~PauseMenu() override = default;
  void resizeEvent(QResizeEvent*) override;

 private:
  QVBoxLayout* main_layout_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  QPushButton* continue_button_;
  SmallExitWindow* small_exit_window_;
  int width_;
  int height_;
  friend class Controller;
};
