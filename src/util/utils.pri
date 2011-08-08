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
	MathHelp.h \
	JMFImport.h \
	Resource.h

SOURCES += 3dsLoader.cpp \
	Logging.cpp \
	RawLoader.cpp \
	lwoLoader.cpp \
	ChunkReader.cpp \
	JMFImport.cpp \
	List.cpp \
	Timer.cpp 
	
