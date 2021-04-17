#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/GameCore/GameController.h"
#include "src/View/view.h"
#include "src/GameCore/input_controller.h"

class EventsController : public QWidget {
  Q_OBJECT

 public:
  explicit EventsController(QWidget* parent, GameMode* game_mode);
  ~EventsController() override = default;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  void SetUnsetPause();

  void PhysicsTimerEvent();
  void ViewTimerEvent();

 signals:
  void SetGamePause();
  void StopGamePause();

 private:
  enum class Actions {
    kOpenOrCloseMenu = Qt::Key_Escape,
  };
  enum class GameStatus {
    kPaused,
    kRunning,
  };

  QTimer view_timer_;
  QTimer controller_timer_;
  InputController input_controller_;
  GameController* game_controller_ = nullptr;
  View* view_ = nullptr;
  GameStatus game_status_ = GameStatus::kRunning;

  static constexpr int kMillisPerFrame = 15;
  static constexpr int kMillisPerPhysicsTick = 5;

  void PrepareTimer();
};
