#pragma once

#include <QFileInfoList>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

#include "src/Menu/image_selector_tile.h"
#include "src/helpers/game_mode.h"
#include "src/helpers/fonts.h"
#include "src/helpers/sizes.h"
#include "src/helpers/styles.h"

class ImageSelector : public QWidget {
  Q_OBJECT

 public:
  explicit ImageSelector(QWidget* parent = nullptr,
                         GameMode* game_mode_ = nullptr);
  ~ImageSelector() override = default;

  void InitializeImages(const QFileInfoList& images_list);

 private:
  void InitializeInfo();
  void SwitchLeft();
  void SwitchRight();

  QHBoxLayout* layout_ = nullptr;
  QPushButton* left_ = nullptr;
  QPushButton* right_ = nullptr;
  QStackedWidget* image_widget_ = nullptr;
  GameMode* game_mode_ = nullptr;

  uint32_t number_of_images_ = 0;
};
