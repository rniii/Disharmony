#include <QtWidgets>
#include <mainwindow.h>

int main(int argc, char *argv[]) {
  qRegisterMetaType<MpdResponse>("MpdResponse");

  QApplication app(argc, argv);

  QCoreApplication::setApplicationName("Disharmony");
  QCoreApplication::setApplicationVersion("0.1.0");
  QCoreApplication::setOrganizationDomain("rinici.de");

  MainWindow win;
  win.show();

  return app.exec();
}
