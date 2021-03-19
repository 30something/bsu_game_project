#include "menu.h"
#include "src/helpers/menu_sizes.h"

Menu::Menu(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    name_label_(new QLabel("Death Rally", this)),
    start_game_button_(new QPushButton("Start game", this)),
    settings_button_(new QPushButton("Settings", this)),
    credits_button_(new QPushButton("Credits", this)),
    exit_button_(new QPushButton("Exit", this)),
    size_(new QSize(menu_sizes::kMenuWidth, menu_sizes::kMenuHeight)) {
  setMinimumSize(size_->width(), size_->height());
  start_game_button_->setMinimumSize(menu_sizes::kMenuMinButtonWidth,
                                     menu_sizes::kMenuMinButtonHeight);
  settings_button_->setMinimumSize(menu_sizes::kMenuMinButtonWidth,
                                   menu_sizes::kMenuMinButtonHeight);
  credits_button_->setMinimumSize(menu_sizes::kMenuMinButtonWidth,
                                  menu_sizes::kMenuMinButtonHeight);
  exit_button_->setMinimumSize(menu_sizes::kMenuMinButtonWidth,
                               menu_sizes::kMenuMinButtonHeight);
  main_layout_->setSpacing(menu_sizes::kMenuSpacing);
  main_layout_->addStretch(5);
  main_layout_->addWidget(name_label_, 1, Qt::AlignCenter);
  main_layout_->addStretch(5);
  main_layout_->addWidget(start_game_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(settings_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(credits_button_, 1, Qt::AlignCenter);
  main_layout_->addWidget(exit_button_, 1, Qt::AlignCenter);
  main_layout_->addStretch(5);
}

QPushButton* Menu::GetStartButton() {
  return start_game_button_;
}

QPushButton* Menu::GetExitButton() {
  return exit_button_;
}
