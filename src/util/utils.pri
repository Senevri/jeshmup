INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += 3dsFileFormat.h \
    3dsLoader.h \
    Logging.h \
    RawLoader.h \
    lwoLoader.h \
    ChunkReader.h \
    List.h \
    Conversion.h \
    Timer.h \
    util/MathHelp.h

SOURCES += 3dsLoader.cpp \
    Logging.cpp \
    RawLoader.cpp \
    lwoLoader.cpp \
    ChunkReader.cpp \
    List.cpp \
    Timer.cpp
	
