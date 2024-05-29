#include <QTcpSocket>
#include <QThread>

class MpdRequest {
public:
  QByteArray cmd;
  QList<QByteArray> args;
};

class MpdResponse {
public:
  QMap<QByteArray, QByteArray> data;
};

class Mpd : QObject {
  Q_OBJECT;

public:
  Mpd(const QString &host, quint16 port);

  void connect();
  MpdResponse sendRequest(MpdRequest req);
  QString idle(QList<QByteArray> systems);

private:
  QTcpSocket sock;
};

class MpdThread : public QThread {
  Q_OBJECT;

public:
  MpdThread();
  ~MpdThread();
  void run() override;

signals:
  void songChanged(MpdResponse song, MpdResponse status);

private:
  bool quitting;
};
