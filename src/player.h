#include <QtWidgets>
#include <mpd.h>

class Player : public QWidget {
  Q_OBJECT;

public:
  Player();

public slots:
  void updateSong(MpdResponse song, MpdResponse status);
  void updateTime();

private:
  QLabel *title = new QLabel;
  QLabel *artist = new QLabel;
  QProgressBar *time;
  QTimer *barTimer;
  QTime songStart;

  MpdThread mpdThread;
};
