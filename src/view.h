#pragma once

#include <QPainter>

class View {
 public:
  View() = default;
  ~View() = default;

  void Repaint(QPainter* painter);

 private:

};
