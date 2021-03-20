#pragma once

#include <QSize>

namespace menu_sizes {

constexpr QSize kMenuSize(800, 800);
constexpr int kMenuSpacing = 16;
constexpr QSize
    kMenuMinButtonSize(kMenuSize.width() * 3 / 8, kMenuSize.height() / 7);
constexpr QSize kPauseMenuSize(500, 500);
constexpr QSize kPauseMenuMinButtonSize
    (kPauseMenuSize.width() * 3 / 5, kPauseMenuSize.height() * 9 / 50);
constexpr QSize kSmallExitWindowSize(250, 100);
constexpr int kSmallExitWindowMoveCoef = 2;

}  // namespace menu_sizes

namespace mainwindow_sizes {

constexpr QSize kDefaultScreenSize(800, 800);

}  // mainwindow_sizes
