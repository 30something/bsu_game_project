#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/Menu/end_game_stats.h"
#include "src/GameCore/game_controller.h"
#include "src/View/view.h"

class EventsController : public QWidget {
  Q_OBJECT

 public:
  explicit EventsController(QWidget* parent, GameMode* game_mode);
  ~EventsController() override = default;

  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  void SetUnsetPause();

  void PhysicsTimerEvent();
  void ViewTimerEvent();

  void CheckFinish();

 signals:
  void SetGamePause();
  void StopGamePause();
  void ReturnToMainMenu();

 private:
  void PrepareGameTimers();
  void PrepareStartCountdownTimer();
  void PrepareEndGameStats();
  void CheckStartCountdownTimer();

  enum class Actions {
    kOpenOrCloseMenu = Qt::Key_Escape,
  };

  enum class GameStatus {
    kPaused,
    kRunning,
  };

  QTimer start_countdown_timer_;
  QTimer view_timer_;
  QTimer controller_timer_;
  QTimer end_game_check_timer_;
  QTimer finish_pause_timer_;
  GameController* game_controller_ = nullptr;
  View* view_ = nullptr;
  EndGameStats* end_game_stats_ = nullptr;
  GameStatus game_status_ = GameStatus::kRunning;

  static constexpr int kMillisPerFrame = 15;
  static constexpr int kMillisPerPhysicsTick = 5;
  static constexpr int kMillisInSecond = 1000;
  int seconds_before_start_ = 4;
};
