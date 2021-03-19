#include "small_exit_window.h"
#include "src/helpers/sizes.h"

SmallExitWindow::SmallExitWindow(QWidget* parent)
    : QWidget(parent),
      main_widget_(new QWidget(this)),
      grid_layout_(new QGridLayout(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("YES", main_widget_)),
      no_button_(new QPushButton("NO", main_widget_)),
      size_(menu_sizes::kSmallExitWindowWidth,
            menu_sizes::kSmallExitWindowHeight) {
  resize(size_.width(), size_.height());
  main_widget_->resize(size_.width(), size_.height());
  main_widget_->move(0, 0);
  grid_layout_->addWidget(question_, 0, 0, 1, 2, Qt::AlignCenter);
  grid_layout_->addWidget(yes_button_, 1, 0);
  grid_layout_->addWidget(no_button_, 1, 1);
}

QPushButton* SmallExitWindow::GetYesButton() const {
  return yes_button_;
}

QPushButton* SmallExitWindow::GetNoButton() const {
  return no_button_;
}
