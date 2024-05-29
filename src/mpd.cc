#include <mpd.h>

Mpd::Mpd(const QString &host, quint16 port) { sock.connectToHost(host, port); }

void Mpd::connect() {
  sock.waitForReadyRead();
  auto line = sock.readLine();
  assert(line.startsWith("OK MPD"));
}

MpdResponse Mpd::sendRequest(MpdRequest req) {
  auto cmd = req.cmd;

  for (auto arg : req.args) {
    cmd += ' ', cmd += '"';
    cmd += arg.replace('\\', "\\\\").replace('"', "\\\"");
    cmd += '"';
  }

  cmd += '\n';

  sock.write(cmd);
  sock.waitForReadyRead();

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

QString Mpd::idle(QList<QByteArray> systems) {
  return sendRequest({"idle", systems}).data["changed"];
}

MpdThread::MpdThread() { setTerminationEnabled(false); }

MpdThread::~MpdThread() {
  quitting = true;
  terminate();
  wait();
}

void MpdThread::run() {
  Mpd mpd("localhost", 6600);
  mpd.connect();

  setTerminationEnabled();

  while (!quitting) {
    auto song = mpd.sendRequest({"currentsong"});
    auto status = mpd.sendRequest({"status"});
    emit songChanged(song, status);

    mpd.idle({"player"});
  }
}
