#include <mainwindow.h>
#include <player.h>

MainWindow::MainWindow() {
  auto player = new Player();
  connect(&mpdThread, &MpdThread::songChanged, player, &Player::updateSong);
  connect(player, &Player::nextSong, [&]() { mpd.writeRequest({"next"}); });
  connect(player, &Player::previousSong, [&]() { mpd.writeRequest({"previous"}); });
  connect(player, &Player::pause, [&]() { mpd.writeRequest({"pause"}); });

  auto main = new QWidget;
  auto layout = new QVBoxLayout(main);
  layout->addWidget(player);

  setCentralWidget(main);

  mpdThread.start();
  mpd.connect("localhost", 6600);
}
