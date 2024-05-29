#include <player.h>

Player::Player() {
  mpdThread.start();

  title->setStyleSheet("font-weight: bold");

  time = new QProgressBar();
  time->setTextVisible(false);

  barTimer = new QTimer();
  barTimer->start(200);

  connect(&mpdThread, &MpdThread::songChanged, this, &Player::updateSong);
  connect(barTimer, &QTimer::timeout, this, &Player::updateTime);

  auto layout = new QGridLayout;
  layout->addWidget(title, 0, 1);
  layout->addWidget(artist, 1, 1);
  layout->addWidget(time, 2, 1);
  setLayout(layout);
  setFixedHeight(80);
}

void Player::updateSong(MpdResponse song, MpdResponse status) {
  artist->setText(song.data["Artist"]);
  title->setText(song.data["Title"]);
  time->setRange(0, song.data["duration"].toFloat());
  auto elapsed = status.data["elapsed"].toFloat();
  songStart = QTime::currentTime().addSecs(elapsed);
  time->setValue(elapsed);
}

void Player::updateTime() {
  time->setValue(songStart.secsTo(QTime::currentTime()));
}
