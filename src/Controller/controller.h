#pragma once

#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>

#include "src/Model/model.h"
#include "src/View/view.h"

class Controller : public QWidget {
  Q_OBJECT

 public:
  explicit Controller(QWidget* parent = nullptr);
  ~Controller() override = default;
  void SetUnsetPause();

 protected:
  void timerEvent(QTimerEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

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

  Model* model_;
  View* view_;
  GameStatus game_status_ = GameStatus::kRunning;
  static constexpr int kMillisPerFrame = 20;
};
