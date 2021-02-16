#include <QApplication>
#include "car.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  Car car;
  car.resize(800, 800);
  car.show();
  return QApplication::exec();
}
