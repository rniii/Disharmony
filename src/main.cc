#include <QtWidgets>
#include <mpd.h>

class Player : public QWidget {
public:
  explicit Player();

private:
  QLabel *title;
  QLabel *artist;

  MpdThread mpdThread;
};

Player::Player() {
  mpdThread.start();

  title = new QLabel("title");
  artist = new QLabel("artist");
  title->setStyleSheet("font-weight: bold");

  connect(&mpdThread, &MpdThread::songChanged, [&](QString a, QString t) {
    artist->setText(a);
    title->setText(t);
  });

  auto layout = new QGridLayout;
  layout->addWidget(title, 0, 0);
  layout->addWidget(artist, 1, 0);
  setLayout(layout);
  setFixedHeight(80);
}

int main(int argc, char *argv[]) {
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
