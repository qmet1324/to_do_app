#include "mainwindow.h"
#include <QApplication>
#include <qnamespace.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv); // Init application

  // Create the UI
  MainWindow window;
  window.setAttribute(Qt::WA_DeleteOnClose);
  window.resize(800, 600);
  window.show();

  return a.exec(); // Execute eventloop
}
