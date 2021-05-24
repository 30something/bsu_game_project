#include "credits.h"

Credits::Credits(QWidget* parent) :
    credits_(new QLabel(this)),
    menu_button_(new QPushButton("Return to main menu", this)),
    layout_(new QVBoxLayout(this)) {
  layout_->setAlignment(Qt::AlignCenter);
  credits_->setStyleSheet("QLabel {"
                          "font: bold 25px; }");
  menu_button_->setStyleSheet(styles::kStandardPushbuttonStyle);
  menu_button_->setMinimumSize(button_sizes::kDefaultButtonSize);
  SetText();
  layout_->addStretch(1);
  layout_->addWidget(credits_, 1, Qt::AlignCenter);
  layout_->addWidget(menu_button_, 2, Qt::AlignCenter);
  layout_->addStretch(1);
  connect(menu_button_,
          &QPushButton::clicked,
          this,
          &Credits::ReturnToMainMenu);
}

void Credits::SetText() {
  credits_->setText(
      "Thanks for playing Survival Rally: Big Guns!\n\n"
      "This game was created by the team of enthusiasts\n"
      "as educational project\n\n"
      "Namely:\n"
      "@Dima-Makarov - Main game designer\n"
      "@30something - Game designer\n"
      "@Korbut-Anton - Game designer\n"
      "@antokir - Sound producer\n\n"
      "You can find more information on github:\n"
      "https://github.com/30something/bsu_game_project");
  credits_->setTextInteractionFlags(Qt::TextSelectableByMouse);
}
