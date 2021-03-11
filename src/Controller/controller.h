#pragma once

#include <QWidget>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPainter>

#include "src/View/view.h"
#include "src/Model/model.h"
#include "src/Menu/pause_menu.h"

class Controller : public QWidget {
  Q_OBJECT

 public:
  explicit Controller(QWidget *parent = nullptr);
  ~Controller() override = default;

  void timerEvent(QTimerEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void HandleKeyPressEvent(QKeyEvent *event);
  void HandleKeyReleaseEvent(QKeyEvent *event);
  void SetPause();
  void UnsetPause();

 private:
  const int kMillisPerFrame = 20;
  bool is_game_paused_ = false;

  Model *model_;
  View *view_;
  PauseMenu *pause_menu_;
};
