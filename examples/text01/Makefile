CC=g++
SRCS=src/*.cpp
HEADERS=
OUTDIR=bin
OUTFILE=main
CFLAGS=-Wall -pedantic -g -lbox2d -lblackhole -lSDL2_image -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -ltmxparser `sdl2-config --libs`

exec : $(OUTDIR)
	$(CC) $(SRCS) -o $(OUTDIR)/$(OUTFILE) $(CFLAGS)

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY : clean
clean : $(OBJS)
	find . -name "*~" -exec rm {} \;
	find . -name "#*#" -exec rm {} \;
	find . -name "*.gch" -exec rm {} \;
