#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>
#include <QTimer>

#include "src/Menu/pause_menu.h"
#include "src/Model/model.h"
#include "src/View/view.h"

class Controller : public QWidget {
  Q_OBJECT

 public:
  explicit Controller(QWidget* parent = nullptr);
  ~Controller() override = default;

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

  void PhysicsTimerEvent();
  void ViewTimerEvent();

  QTimer view_timer_;
  QTimer controller_timer_;
  Model* model_;
  View* view_;
  PauseMenu* pause_menu_;
  GameStatus game_status_ = GameStatus::kRunning;
  static constexpr int kMillisPerFrame = 10;
  static constexpr int kMillisPerPhysicsTick = 5;

};
