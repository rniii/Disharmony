#include <player.h>

Player::Player() {
  title = new QLabel;
  title->setStyleSheet("font-weight: bold");
  artist = new QLabel;
  time = new QSlider(Qt::Horizontal);

  barTimer = new QTimer();
  barTimer->start(200);
  connect(barTimer, &QTimer::timeout, this, &Player::updateTime);

  auto songInfo = new QWidget;
  auto infoLayout = new QGridLayout(songInfo);
  infoLayout->addWidget(title, 0, 1);
  infoLayout->addWidget(artist, 1, 1);
  infoLayout->addWidget(time, 2, 1);

  auto next = new QPushButton(">>");
  auto previous = new QPushButton("<<");
  auto pause = new QPushButton("|>");
  connect(next, &QPushButton::clicked, this, &Player::nextSong);
  connect(previous, &QPushButton::clicked, this, &Player::previousSong);
  connect(pause, &QPushButton::clicked, this, &Player::pause);

  auto layout = new QHBoxLayout;
  layout->addWidget(previous);
  layout->addWidget(pause);
  layout->addWidget(next);
  layout->addWidget(songInfo);
  setLayout(layout);

  setFixedHeight(80);
}

void Player::updateSong(MpdResponse song, MpdResponse status) {
  artist->setText(song.data["Artist"]);
  title->setText(song.data["Title"]);
  time->setMaximum(song.data["duration"].toFloat());

  auto elapsed = status.data["elapsed"].toFloat();
  songStart = QTime::currentTime().addSecs(-elapsed);
  time->setValue(elapsed);
}

void Player::updateTime() {
  time->setValue(songStart.secsTo(QTime::currentTime()));
}
