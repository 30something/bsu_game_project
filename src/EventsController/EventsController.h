#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/GameCore/GameController.h"
#include "src/View/view.h"

class EventsController : public QWidget {
  Q_OBJECT

 public:
  explicit EventsController(QWidget* parent = nullptr);
  ~EventsController() override = default;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void SetUnsetPause();
  const QPushButton* GetReturnToMainMenuButton() const;

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

  void PhysicsTimerEvent();
  void ViewTimerEvent();

  QTimer view_timer_;
  QTimer controller_timer_;
  GameController* model_ = nullptr;
  View* view_ = nullptr;
  PauseMenu* pause_menu_ = nullptr;
  GameStatus game_status_ = GameStatus::kRunning;
  static constexpr int kMillisPerFrame = 10;
  static constexpr int kMillisPerPhysicsTick = 5;
  void PrepareTimer();
  void PreparePauseMenu();
};
