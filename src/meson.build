moc = qt5.compile_moc(headers: ['mpd.h', 'player.h', 'mainwindow.h'])

executable('disharmony', 'main.cc', 'mpd.cc', 'player.cc', 'mainwindow.cc', moc,
  cpp_pch: 'pch/qt.h',
  dependencies: qt5_dep,
  install: true)
