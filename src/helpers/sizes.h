#pragma once

#include <QSize>

namespace menu_sizes {

constexpr QSize kMenuSize(800, 400);
constexpr int kMenuSpacing = 16;

constexpr QSize kSettingsSize(800, 400);
constexpr QSize kSettingsMinButtonSize
    (kSettingsSize.width() / 4, kSettingsSize.height() / 6);

constexpr QSize kPauseMenuSize(500, 250);
constexpr QSize kPauseMenuMinButtonSize
    (kPauseMenuSize.width() * 3 / 5, kPauseMenuSize.height() * 9 / 50);

constexpr QSize kSmallExitWindowSize(250, 100);
constexpr int kSmallExitWindowMoveCoef = 2;

}  // namespace menu_sizes

namespace mainwindow_sizes {

constexpr QSize kDefaultScreenSize(800, 400);

}  // mainwindow_sizes

namespace button_sizes {

constexpr QSize kDefaultButtonSize(300, 60);
constexpr QSize kMapSelectorsSize(250, 60);

}  // button_sizes

namespace combo_boxes_sizes {

constexpr QSize kComboBoxDefaultSize(200, 30);

}  // combo_boxes_sizes
