#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>

#include "small_exit_window.h"

class PauseMenu : public QWidget {
  Q_OBJECT

 public:
  explicit PauseMenu(QWidget* parent = nullptr);
  ~PauseMenu() override = default;
  void Close();

 protected:
  void resizeEvent(QResizeEvent*) override;

 signals:
  void ContinueGame();
  void ReturnToMainMenu();

 private:
  QVBoxLayout* main_layout_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  QPushButton* continue_button_;
  SmallExitWindow* small_exit_window_;
};
