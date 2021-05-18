#include <QApplication>
#include "server_controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  ServerController butt;
  butt.show();
  return QApplication::exec();
}
