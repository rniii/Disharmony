#include <QtWidgets>
#include <mpd.h>

class MainWindow : public QMainWindow {
  Q_OBJECT;

public:
  MainWindow();

private:
  MpdThread mpdThread;
  Mpd mpd;
};
