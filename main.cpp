#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv); // Init application

  // Create the UI
  MainWindow window;
  window.setAttribute(Qt::WA_DeleteOnClose);
  window.resize(800, 600);
  window.show();

  // Apply QSS config
  QFile qssFile("mystyles.qss");
  if (qssFile.open(QFile::ReadOnly | QFile::Text)) {
    QTextStream stream(&qssFile);
    window.setStyleSheet(stream.readAll());
    qssFile.close();
  } else {
    qWarning() << "Could not load QSS file!";
  }

  return a.exec(); // Execute eventloop
}
