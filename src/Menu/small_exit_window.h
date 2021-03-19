#pragma once

#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QWidget>

class SmallExitWindow : public QWidget {
  Q_OBJECT

 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;
  QPushButton* GetYesButton() const;
  QPushButton* GetNoButton() const;
  int GetWidth() const;
  int GetHeight() const;

 private:
  QWidget* main_widget_ = nullptr;
  QLabel* question_ = nullptr;
  QPushButton* yes_button_ = nullptr;
  QPushButton* no_button_ = nullptr;
  int width_ = 250;
  int height_ = 100;
};
