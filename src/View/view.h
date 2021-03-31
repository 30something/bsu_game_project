#pragma once

#include <utility>
#include <vector>

#include <QPainter>
#include <QImage>

#include "src/GameCore/GameController.h"
#include "engine.h"

class View {
 public:
  explicit View(GameController* model);
  ~View() = default;

  void Repaint(QPainter* painter);

  void ChangeEngineVolume(double coefficient);

 private:
  GameController* model_ = nullptr;
  QImage map_;
  QImage car_;
  Engine* engine_;
};
