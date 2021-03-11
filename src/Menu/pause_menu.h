#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>
#include <QStyle>

class SmallExitWindow : public QWidget {
 Q_OBJECT
 public:
  explicit SmallExitWindow(QWidget * = nullptr);
 protected:
  ~SmallExitWindow() override = default;
 private:
  QWidget *parent_;
  int width_;
  int height_;
  QLabel *question_;
  QPushButton *yes_button_;
  QPushButton *no_button_;
  friend class PauseMenu;
};

class PauseMenu : public QWidget {
 Q_OBJECT
 public:
  explicit PauseMenu(QWidget * = nullptr);
  int GetWidth() const;
  int GetHeight() const;
 protected:
  ~PauseMenu() override = default;
  //void keyPressEvent(QKeyEvent*) override;
 private:
  QWidget *parent_;
  int width_;
  int height_;
  QPushButton *settings_button_;
  QPushButton *exit_button_;
  QPushButton *continue_button_;
  QStackedWidget* stacked_widget_;
  SmallExitWindow *small_exit_window_;
  friend class Controller;
};
