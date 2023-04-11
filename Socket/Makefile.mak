FILES =tsoft_mime_types.cpp Project_Server.cpp sstsoft_sockets.cpp ..\..\Libraries\kop32\tsoft_io32.cpp
TARGET=SS_WWW.exe
OBJS  =tsoft_mime_types.o Project_Server.o sstsoft_sockets.o tsoft_io32.o

MINGW =$(MINGW_PATH)
LIBS  = -L"$(MINGW)\lib"
CFLAGS= -I"$(MINGW)\include"
CPP   =g++.exe

all: build

build: compile
	@$(CPP) -Wall -s -O2 -o $(TARGET) $(OBJS) $(LIBS)

compile: $(FILES)
	@$(CPP) -Wall -s -O2 -c $(FILES) $(CFLAGS)
