#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/Menu/end_game_stats.h"
#include "src/GameCore/GameController.h"
#include "src/View/view.h"

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

  void FinishCheck();

 signals:
  void SetGamePause();
  void StopGamePause();
  void ShowStats();

 private:
  void PrepareTimer();
  void StartTimer();

  enum class Actions {
    kOpenOrCloseMenu = Qt::Key_Escape,
  };

  enum class GameStatus {
    kPaused,
    kRunning,
  };

  QTimer start_timer_;
  QTimer view_timer_;
  QTimer view_labels_update_timer_;
  QTimer controller_timer_;
  QTimer end_game_check_timer_;
  GameController* game_controller_ = nullptr;
  View* view_ = nullptr;
  GameStatus game_status_ = GameStatus::kRunning;

  static constexpr int kMillisPerFrame = 15;
  static constexpr int kMillisPerPhysicsTick = 5;
  static constexpr int kMillisInSecond = 1000;
  int seconds_before_start_ = 4;
};
