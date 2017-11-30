TARGET=main.exe
CC=gcc
CXX=g++
CFLAGS=-g -O2 -w
CXXFLAGS=$(CFLAGS)
LDFLAGS=-static-libgcc -static-libstdc++ -mwindows
INCDIR=-I"./DxLib/"
LIBDIR=-L"./DxLib/"
LIBS=-lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static\
	 -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile\
	 -lopus -lsilk_common -lcelt
LIBS+=-lgdi32
OBJS=main.o

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCDIR) $(LIBDIR) -o $@ $^ $(LIBS) 

clean:
	del -fr $(TARGET) $(OBJS)