moc = qt5.compile_moc(headers: 'mpd.h')

executable('disharmony', 'main.cc', 'mpd.cc', moc,
  cpp_pch: 'pch/qt.h',
  dependencies: qt5_dep,
  install: true)
