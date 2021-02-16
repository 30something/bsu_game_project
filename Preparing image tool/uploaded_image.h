#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <vector>
#include <QApplication>
#include <QFile>
#include <QTextStream>

class PrepareImage : public QWidget {

 public:
  explicit PrepareImage(QWidget* parent = 0);

 protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  QImage image_;
  enum class step {
    left = 0,
    right = 1
  };
  void WriteToFile();
  step step_now = step::left;
  int image_offset_x_ = 0;
  int image_offset_y_ = 0;
  double image_scale_ = 2.5;
  int scaled_image_size_ = 400;
  int speed_scale_factor_ = 10;
  std::vector<std::pair<int, int>> coordinates_left_;
  std::vector<std::pair<int, int>> coordinates_right_;
};