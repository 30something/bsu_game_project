#include <QApplication>
#include "uploaded_image.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  PrepareImage window;
  window.show();
  return QApplication::exec();
}
