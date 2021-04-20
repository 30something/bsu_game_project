#pragma once

#include <QSize>

namespace menu_sizes {

constexpr QSize kMenuSize(800, 400);
constexpr int kMenuSpacing = 16;
constexpr QSize
    kMenuMinButtonSize(kMenuSize.width() * 3 / 8, kMenuSize.height() / 7);

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

namespace car_sizes {

constexpr int kPercentageOfCarSizeOnSceeen = 3;
constexpr int kCarDiagonalInPixels = 20;

}  // car_sizes
