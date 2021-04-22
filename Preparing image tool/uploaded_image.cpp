#include "uploaded_image.h"
#include <QPainter>
#include <QTime>
#include <iostream>

PrepareImage::PrepareImage(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color:black;");
  resize(800, 800);
  image_.load("map1.jpg");
}

void PrepareImage::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter qp(this);
  qp.scale(image_scale_, image_scale_);
  qp.drawImage(0,
               0,
               image_,
               image_offset_x_,
               image_offset_y_,
               scaled_image_size_,
               scaled_image_size_);
  qp.scale(1, 1);
  qp.setPen(QColor("red"));
  for (int i = 1; i < coordinates_left_.size(); i++) {
    qp.drawLine(
        coordinates_left_[i - 1].first - image_offset_x_,
        coordinates_left_[i - 1].second - image_offset_y_,
        coordinates_left_[i].first - image_offset_x_,
        coordinates_left_[i].second - image_offset_y_);
  }

  for (int i = 1; i < coordinates_right_.size(); i++) {
    qp.drawLine(coordinates_right_[i - 1].first - image_offset_x_,
                coordinates_right_[i - 1].second - image_offset_y_,
                coordinates_right_[i].first - image_offset_x_,
                coordinates_right_[i].second - image_offset_y_);
  }
  QString phase = "phase: ";
  phase += (step_now == step::left) ? ("left") : ("right");
  qp.drawText(10, 10, phase);
}

void PrepareImage::keyPressEvent(QKeyEvent* e) {
  int key = e->key();
  if (key == Qt::Key_Backspace) {
    if (step_now == step::left) {
      coordinates_left_.pop_back();
    } else {
      coordinates_right_.pop_back();
    }
  }
  if (key == Qt::Key_Space) {
    if (step_now == step::left) {
      step_now = step::right;
    } else {
      WriteToFile();
      QApplication::quit();
    }
  } else if (key == Qt::Key_Left) {
    image_offset_x_ -= speed_scale_factor_;
  } else if (key == Qt::Key_Right) {
    image_offset_x_ += speed_scale_factor_;
  } else if (key == Qt::Key_Down) {
    image_offset_y_ += speed_scale_factor_;
  } else if (key == Qt::Key_Up) {
    image_offset_y_ -= speed_scale_factor_;
  }
  repaint();
}
void PrepareImage::mousePressEvent(QMouseEvent* event) {
  if (step_now == step::left) {
    coordinates_left_.emplace_back(
        event->x() / image_scale_ + image_offset_x_,
        event->y() / image_scale_ + image_offset_y_);
  } else {
    coordinates_right_.emplace_back(
        event->x() / image_scale_ + image_offset_x_,
        event->y() / image_scale_ + image_offset_y_);
  }
  repaint();
}

void PrepareImage::WriteToFile() {
  std::cout << "processing a file" << std::endl;
  QTextStream out(stdout);
  QString filename =
      //"c:/Dima/mama i am programmer/"
      "coords.txt";
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    for (auto i : coordinates_left_) {
      out << "{\"x\": " << i.first << ", \"y\": " << ' ' << i.second << "},\n";
    }
    out << "---" << '\n';
    for (auto i : coordinates_right_) {
      out << i.first << ' ' << i.second << '\n';
    }
    out << "end_file";
  } else {
    qWarning("Could not open file");
  }
  file.close();
}

