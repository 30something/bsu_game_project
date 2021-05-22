#pragma once

#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>

#include "small_exit_window.h"
#include "src/helpers/fonts.h"
#include "src/helpers/sizes.h"

class PauseMenu : public QWidget {
  Q_OBJECT

 public:
  explicit PauseMenu(QWidget* parent = nullptr);
  ~PauseMenu() override = default;

  void Close();

 signals:
  void ContinueGame();
  void ReturnToMainMenu();
  void ShowSettingsFromPM();

 private:
  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;

  void SetFonts();
  void SetSizes();
  void SetUpLayout();
  void ConnectUI();

  enum class Actions {
    kCloseMenu = Qt::Key_Escape,
  };

  QVBoxLayout* main_layout_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;
  QPushButton* continue_button_;
  SmallExitWindow* small_exit_window_;
};
