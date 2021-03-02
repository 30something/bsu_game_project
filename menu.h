#pragma once

#include <QWidget>
#include <QPushButton>

class Menu : public QWidget {
  Q_OBJECT
 public:
  explicit Menu(QWidget* parent = nullptr);
  QPushButton button;
  // Here are all menu's and stuff
};

