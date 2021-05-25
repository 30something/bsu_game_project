#pragma once

#include <vector>

#include <QKeyEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/Menu/end_game_stats.h"
#include "src/View/view.h"
#include "src/View/view_info_updater.h"
#include "src/GameCore/input_controller.h"
#include "src/GameCore/game_controller.h"
#include "src/helpers/cars_data.h"
#include "src/View/Sounds/sound.h"

class EventsController : public QWidget {
 Q_OBJECT

 public:
  explicit EventsController(QWidget* parent, GameMode* game_mode);
  ~EventsController() override;

  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

  void SetUnsetPause();

  void PhysicsTimerEvent();
  void ViewTimerEvent();
  void FinishCheckEvent();

  void UpdateStartInfo();
  void ShowEndGameStats();

  void PlaySounds();

 signals:
  void SetGamePause();
  void StopGamePause();
  void ReturnToMainMenu();

 private:
  void LaunchStartCountdownTimer();
  void LaunchGameTimers();
  void LaunchFinishTimer();
  void PrepareEndGameStats();
  void SendFinishData();

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
  QTimer finish_pause_timer_;
  QTimer finish_check_timer_;
  InputController input_controller_;
  GameController* game_controller_ = nullptr;
  View* view_ = nullptr;
  Sound* sound_ = nullptr;
  ViewInfoUpdater* view_info_updater_ = nullptr;
  EndGameStats* end_game_stats_ = nullptr;
  GameStatus game_status_ = GameStatus::kRunning;

  static constexpr int kMillisInSecond = 1000;
  static constexpr int kMillisPerFrame = 15;
  static constexpr int kMillisPerPhysicsTick = 5;
};
