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
  void CloseSmallExitWindow();
  const QPushButton* GetReturnToMainMenuButton() const;
  const QPushButton* GetContinueButton() const;

 protected:
  void resizeEvent(QResizeEvent*) override;

 private:
  QVBoxLayout* main_layout_ = nullptr;
  QPushButton* settings_button_ = nullptr;
  QPushButton* exit_button_ = nullptr;
  QPushButton* continue_button_ = nullptr;
  SmallExitWindow* small_exit_window_ = nullptr;
  int width_ = 500;
  int height_ = 500;
};
