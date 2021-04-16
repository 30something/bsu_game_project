#include "uploaded_image.h"

#include <QPainter>
#include <QTime>

#include <iostream>

PrepareImage::PrepareImage(QWidget* parent) : QWidget(parent) {
  setStyleSheet("background-color:black;");
  setFixedSize(800, 800);
  RequestPhotoPath();
  RequestCoordsPath();
  std::cerr << "File opened to process..." << '\n';
}

void PrepareImage::RequestPhotoPath() {
  std::cerr << "Enter the absolute file path of the image\n";
  std::cerr << R"(For example: "C:\Users\User\Desktop\map.jpg")" << '\n';
  getline(std::cin, picture_path_);
  if (!image_.load(QString::fromStdString(picture_path_))) {
    std::cerr << "Unable to open file\n";
    std::cerr << "You should reopen tool and edit the file path\n";
    std::exit(0);
  }
}

void PrepareImage::RequestCoordsPath() {
  std::cerr << "Enter the absolute file path of the txt file to put coords\n";
  std::cerr << R"(For example: "C:\Users\User\Desktop\coords.txt")" << '\n';
  getline(std::cin, coords_path_);
  output_file_.setFileName(QString::fromStdString(coords_path_));
  if (!output_file_.open(QIODevice::WriteOnly)) {
    std::cerr << "Unable to open file\n";
    std::cerr << "You should reopen tool and edit the file path\n";
    std::exit(0);
  }
}

void PrepareImage::paintEvent(QPaintEvent*) {
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
  for (size_t i = 1; i < coordinates_left_.size(); i++) {
    qp.drawLine(
        coordinates_left_[i - 1].first - image_offset_x_,
        coordinates_left_[i - 1].second - image_offset_y_,
        coordinates_left_[i].first - image_offset_x_,
        coordinates_left_[i].second - image_offset_y_);
  }
  for (size_t i = 1; i < coordinates_right_.size(); i++) {
    qp.drawLine(coordinates_right_[i - 1].first - image_offset_x_,
                coordinates_right_[i - 1].second - image_offset_y_,
                coordinates_right_[i].first - image_offset_x_,
                coordinates_right_[i].second - image_offset_y_);
  }
  QString phase = "Phase: ";
  phase += (step_now == step::left) ? ("left") : ("right");
  qp.drawText(0, 10, phase);
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
    coordinates_left_.emplace_back(event->x() / image_scale_ + image_offset_x_,
                                   event->y() / image_scale_ + image_offset_y_);
  } else {
    coordinates_right_.emplace_back(event->x() / image_scale_ + image_offset_x_,
                                    event->y() / image_scale_
                                        + image_offset_y_);
  }
  repaint();
}

void PrepareImage::WriteToFile() {
  QTextStream out(&output_file_);
  out << "x | y\n";
  for (const auto& pair : coordinates_left_) {
    out << pair.first << ' ' << pair.second << '\n';
  }
  out << "---" << '\n';
  for (const auto& pair : coordinates_right_) {
    out << pair.first << ' ' << pair.second << '\n';
  }
  std::cerr << "Data successfully was written to file";
  output_file_.close();
}
