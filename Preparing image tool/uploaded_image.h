#pragma once

#include <iostream>
#include <vector>

#include <QApplication>
#include <QFile>
#include <QKeyEvent>
#include <QTextStream>
#include <QTime>
#include <QPainter>
#include <QWidget>

class PrepareImage : public QWidget {

 public:
  explicit PrepareImage(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  void WriteToFile();
  void RequestPhotoPath();
  void RequestCoordsPath();

  enum class step {
    left = 0,
    right = 1
  };

  QImage image_;
  QFile output_file_;
  step step_now = step::left;
  int image_offset_x_ = 0;
  int image_offset_y_ = 0;
  int scaled_image_size_ = 1000;
  int speed_scale_factor_ = 10;
  double image_scale_ = 1;
  std::string picture_path_;
  std::string coords_path_;
  std::vector<std::pair<int, int>> coordinates_left_;
  std::vector<std::pair<int, int>> coordinates_right_;
};