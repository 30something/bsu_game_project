#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QWidget>

class SmallExitWindow : public QWidget {
 public:
  explicit SmallExitWindow(QWidget* parent = nullptr);
  ~SmallExitWindow() override = default;
  QPushButton* GetYesButton() const;
  QPushButton* GetNoButton() const;
  int GetWidth() const;
  int GetHeight() const;

 private:
  QWidget* main_widget_;
  QGridLayout* grid_layout_;
  QLabel* question_;
  QPushButton* yes_button_;
  QPushButton* no_button_;
  QSize* size_;
};
