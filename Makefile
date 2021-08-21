CC=g++
SRCS=src/graphics/animation.cpp src/graphics/animator_controller.cpp src/graphics/imageBase.cpp src/graphics/image.cpp src/graphics/spritesheet.cpp src/graphics/tilemap.cpp src/graphics/window.cpp src/graphics/camera.cpp src/graphics/text.cpp
HEADERS=include/graphics/*.h
HEADERDIR=include
OBJDIR=obj
LIBDIR=lib
OUTLIB=libblackhole.so
INCLUDEDIR=/usr/local/include/blackhole
CFLAGS=-lpthread -lSDL2main -lSDL2 -lSDL_mixer -I$(HEADERDIR)

default: build build-headers

build : $(OBJDIR) $(LIBDIR) $(INCLUDEDIR)
	$(CC) -c -Wall -fpic $(SRCS) $(CFLAGS)
	mv *.o $(OBJDIR)
	$(CC) -shared -o $(LIBDIR)/$(OUTLIB) $(OBJDIR)/*.o
	cp $(LIBDIR)/$(OUTLIB) /usr/local/lib

build-headers:
	cp -r $(HEADERDIR)/* $(INCLUDEDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBDIR):
	mkdir $(LIBDIR)

$(INCLUDEDIR):
	mkdir $(INCLUDEDIR)

.PHONY : clean
clean : $(OBJS)
		find . -name "*~" -exec rm {} \;
		find . -name "#*#" -exec rm {} \;
		find . -name "*.gch" -exec rm {} \;
		find . -name "*.o" -exec rm {} \;
