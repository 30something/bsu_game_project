#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "src/helpers/sizes.h"
#include "src/helpers/fonts.h"
#include "src/helpers/styles.h"

class Credits : public QWidget {
  Q_OBJECT

 public:
  explicit Credits(QWidget* parent = nullptr);
  ~Credits() override = default;

 signals:
  void ReturnToMainMenu();

 private:
  void SetText();

  QLabel* credits_ = nullptr;
  QPushButton* menu_button_ = nullptr;
  QVBoxLayout* layout_ = nullptr;
};
