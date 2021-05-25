#include <QApplication>
#include "server_controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  ServerController server_controller;
  server_controller.show();
  return QApplication::exec();
}
