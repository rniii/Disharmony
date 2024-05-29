#include <QtWidgets>
#include <mpd.h>

class Player : public QWidget {
  Q_OBJECT;

public:
  Player();

signals:
  void nextSong();
  void previousSong();
  void pause();

public slots:
  void updateSong(MpdResponse song, MpdResponse status);
  void updateTime();

private:
  QLabel *title;
  QLabel *artist;
  QSlider *time;
  QTimer *barTimer;
  QTime songStart;
};
