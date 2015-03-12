TEMPLATE = subdirs # lest qmake decides to build an app w/o any sources
CONFIG -= qt moc
HEADERS += $$files(*.hpp)
