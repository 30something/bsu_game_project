#include "small_exit_window.h"

SmallExitWindow::SmallExitWindow(QWidget* parent)
    : QWidget(parent),
      main_widget_(new QWidget(this)),
      grid_layout_(new QGridLayout(this)),
      question_(new QLabel("Go to main menu?", main_widget_)),
      yes_button_(new QPushButton("Yes", main_widget_)),
      no_button_(new QPushButton("No", main_widget_)) {
  SetStyles();
  main_widget_->move(0, 0);
  SetUpLayout();
  ConnectUI();
}

void SmallExitWindow::SetStyles() {
  resize(menu_sizes::kSmallExitWindowSize);
  main_widget_->setStyleSheet("QWidget {"
                              "background-color: #ffff00;"
                              "border-style: outset;"
                              "border-width: 2px;"
                              "border-color: beige;"
                              "border-radius: 10px; }");
  for (auto& widget : main_widget_->children()) {
    auto* label_ptr = qobject_cast<QLabel*>(widget);
    auto* button_ptr = qobject_cast<QPushButton*>(widget);
    if (label_ptr) {
      label_ptr->setFont(fonts::kDefaultLabelFont);
      label_ptr->setStyleSheet("QLabel {"
                               "font: bold 18px; }");
    } else if (button_ptr) {
      button_ptr->setFont(fonts::kDefaultButtonFont);
      button_ptr->setStyleSheet("QPushButton {"
                                "background-color: #ffff00;"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 10px;"
                                "border-color: beige;"
                                "font: bold 18px; }"

                                "QPushButton::pressed {"
                                "background-color: #d5d501;"
                                "border-style: inset; }");
    }
  }
  main_widget_->resize(menu_sizes::kSmallExitWindowSize);
}

void SmallExitWindow::SetUpLayout() {
  grid_layout_->addWidget(question_, 0, 0, 1, 2, Qt::AlignCenter);
  grid_layout_->addWidget(yes_button_, 1, 0);
  grid_layout_->addWidget(no_button_, 1, 1);
}

void SmallExitWindow::ConnectUI() {
  connect(no_button_,
          &QPushButton::clicked,
          this,
          &SmallExitWindow::StayAtPauseMenu);
  connect(yes_button_,
          &QPushButton::clicked,
          this,
          &SmallExitWindow::ReturnToMainMenu);
}
