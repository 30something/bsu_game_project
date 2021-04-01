#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "EngineSound.h"
#include "DriftSound.h"

class View {

 public:
  explicit View(QWidget* events_controller, GameController* model);
  ~View() = default;

  void Repaint(QPainter* painter);

  void ChangeEngineVolume(double coefficient);
  void PlayDrift(double coefficient);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  Engine* engine_;
  Drift* drift_;
};
