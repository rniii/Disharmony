#include <mpd.h>

void Mpd::connect(const QString &host, quint16 port) {
  sock.connectToHost(host, port);
  sock.waitForReadyRead();
  auto line = sock.readLine();
  assert(line.startsWith("OK MPD"));
}

void Mpd::writeRequest(MpdRequest req) {
  if (sock.state() != QTcpSocket::ConnectedState) {
    QTextStream(stdout) << "reconnecting\n";
    connect("127.0.0.1", 6600);
  }

  auto cmd = req.cmd;

  for (auto arg : req.args) {
    cmd += ' ', cmd += '"';
    cmd += arg.replace('\\', "\\\\").replace('"', "\\\"");
    cmd += '"';
  }

  cmd += '\n';

  sock.write(cmd);
}

MpdResponse Mpd::readResponse() {
  while (!sock.waitForReadyRead())
    ;

  MpdResponse res;
  for (;;) {
    auto line = sock.readLine().trimmed();
    if (line == "OK")
      return res;
    if (line.startsWith("ACK"))
      throw;

    auto p = line.indexOf(':');
    auto key = line.left(p);
    res.data[key] = line.remove(0, p + 1).trimmed();
  }
}

MpdResponse Mpd::sendRequest(MpdRequest req) {
  return writeRequest(req), readResponse();
}

QString Mpd::idle(QList<QByteArray> systems) {
  return sendRequest({"idle", systems}).data["changed"];
}

MpdThread::~MpdThread() {
  terminate();
  wait();
}

void MpdThread::run() {
  Mpd mpd;
  mpd.connect("localhost", 6600);

  setTerminationEnabled();

  for (;;) {
    auto song = mpd.sendRequest({"currentsong"});
    auto status = mpd.sendRequest({"status"});
    emit songChanged(song, status);

    mpd.idle({"player"});
  }
}
