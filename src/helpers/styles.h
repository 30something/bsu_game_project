#pragma once

#include <QString>

namespace styles {

const QString kStandardPushbuttonStyle =
    "QPushButton {"
    "background-color: #ff9900;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "padding: 2px;"
    "font: bold 18px; }"

    "QPushButton::pressed {"
    "background-color: #e68a00;"
    "border-style: inset; }";

const QString kImageSelectorPushbuttonStyle =
    "QPushButton {"
    "background-color: #ff9900;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "padding: 2px;"
    "font: bold 14px; }"

    "QPushButton::pressed {"
    "background-color: #e68a00;"
    "border-style: inset; }";

const QString kPausePushbuttonStyle =
    "QPushButton {"
    "background-color: #ff9900;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "padding: 2px;"
    "font: bold 20px; }"

    "QPushButton::pressed {"
    "background-color: #e68a00;"
    "border-style: inset; }";

const QString kSmallPausePushbuttonStyle =
    "QPushButton {"
    "background-color: #ff9900;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "font: bold 18px; }"

    "QPushButton::pressed {"
    "background-color: #e68a00;"
    "border-style: inset; }";

const QString kStandardComboBoxStyle =
    "QComboBox {"
    "background-color: #ff9900;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-radius: 10px;"
    "border-color: beige;"
    "padding: 5px;"
    "font: bold 18px; }"

    "QComboBox::drop-down {"
    "border-width: 0px; }"

    "QComboBox::down-arrow {"
    "border-width: 0px; }";

const QString kPauseWidgetStyle =
    "QWidget {"
    "background-color: #ffff00;"
    "border-style: outset;"
    "border-width: 2px;"
    "border-color: beige;"
    "border-radius: 10px; }";

const QString kFinishWidgetStyle =
    "QWidget {"
    "background-color: rgba(255, 255, 255, 150);"
    "border-style: outset;"
    "border-width: 2px;"
    "border-color: beige;"
    "border-radius: 10px; }";

const QString kStandardSliderStyle =
    "QSlider::groove:horizontal {"
    "border: 2px solid #cc5200;"
    "height: 8px;"
    "background: qlineargradient(x1:0, y1:0, x2:0, "
    "y2:1, stop:0 #ff6600, stop:1 #ff6600);"
    "margin: 2px 0;"
    "border-radius: 5px; }"

    "QSlider::handle:horizontal {"
    "background: qlineargradient(x1:0, y1:0, x2:1, "
    "y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
    "border: 1px solid #5c5c5c;"
    "width: 18px;"
    "margin: -2px 0;"
    "border-radius: 5px; }";

const QString kStandardLineEditStyle =
    "QLineEdit {"
    "border: 2px solid gray;"
    "border-radius: 10px;"
    "padding: 0 8px;"
    "font: 15px;"
    "selection-background-color: darkgray; }";

const QString kMapWidgetStyle =
    "QWidget {"
    "border-style: solid;"
    "border-width: 5px;"
    "border-radius: 10px;"
    "border-color: #ff6600; }";

}  // namespace styles
