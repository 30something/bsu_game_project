#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPainter>

#include "src/View/view.h"
#include "src/Model/model.h"
#include "src/Menu/pause_menu.h"

class Controller : public QWidget {
 public:
  explicit Controller(QWidget* parent = nullptr);
  ~Controller() override = default;

  void timerEvent(QTimerEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  void resizeEvent(QResizeEvent*) override;
  void SetOrUnsetPause();

 private:
  Model* model_;
  View* view_;
  PauseMenu* pause_menu_;
  enum GameStatus {
    kPaused,
    kRunning,
  };
  enum Actions {
    kOpenOrCloseMenu = Qt::Key_Escape,
  };
  static constexpr int kMillisPerFrame = 20;
  int game_status_ = GameStatus::kRunning;
};
