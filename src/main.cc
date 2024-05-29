#include <QtWidgets>
#include <player.h>

int main(int argc, char *argv[]) {
  qRegisterMetaType<MpdResponse>("MpdResponse");

  QApplication app(argc, argv);

  QCoreApplication::setApplicationName("Disharmony");
  QCoreApplication::setApplicationVersion("0.1.0");
  QCoreApplication::setOrganizationDomain("rinici.de");

  auto main = new QWidget;
  auto mainLayout = new QVBoxLayout(main);
  mainLayout->addWidget(new Player());

  QMainWindow win;
  win.setCentralWidget(main);
  win.show();

  return app.exec();
}
