#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>

#include "src/Menu/pause_menu.h"
#include "src/Model/model.h"
#include "src/View/view.h"

class Controller : public QWidget {
 public:
  explicit Controller(QWidget* parent = nullptr);
  ~Controller() override = default;

  void timerEvent(QTimerEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void SetUnsetPause();
  QPushButton* GetReturnToMainMenuButton() const;

 protected:
  void resizeEvent(QResizeEvent*) override;

 private:
  enum class Actions {
    kOpenOrCloseMenu = Qt::Key_Escape,
  };

  enum class GameStatus {
    kPaused,
    kRunning,
  };

  Model* model_;
  View* view_;
  PauseMenu* pause_menu_;
  GameStatus game_status_ = GameStatus::kRunning;
  static constexpr int kMillisPerFrame = 20;
};
