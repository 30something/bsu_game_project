#pragma once

#include <QPushButton>
#include <QWidget>

class Menu : public QWidget {
  Q_OBJECT
 public:
  explicit Menu(QWidget* parent = nullptr);

  QPushButton button;
  // Here are all menu_'s and stuff
};

