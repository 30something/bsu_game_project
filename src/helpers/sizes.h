#pragma once

#include <QSize>

namespace menu_sizes {

constexpr QSize kMenuSize(800, 400);
constexpr int kMenuSpacing = 16;

constexpr QSize kSettingsSize(800, 400);
constexpr QSize kPauseMenuSize(500, 250);

constexpr QSize kSmallExitWindowSize(250, 100);
constexpr int kSmallExitWindowMoveCoef = 2;

}  // namespace menu_sizes

namespace mainwindow_sizes {

constexpr QSize kDefaultScreenSize(800, 600);

}  // mainwindow_sizes

namespace button_sizes {

constexpr QSize kDefaultButtonSize(300, 60);
constexpr QSize kSmallChooseButtonSize(100, 20);
constexpr QSize kMapSelectorsSize(200, 60);
constexpr QSize kSettingsMinButtonSize(200, 65);
constexpr QSize kMultiplayerButtonMinSize(0, 50);
constexpr QSize kPauseMenuMinButtonSize(350, 60);

}  // button_sizes

namespace combo_boxes_sizes {

constexpr QSize kComboBoxDefaultSize(200, 30);

}  // combo_boxes_sizes

namespace car_sizes {

constexpr int kPercentageOfCarSizeOnSceeen = 3;
constexpr int kCarDiagonalInPixels = 20;

}  // car_sizes
