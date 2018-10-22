CompileFiles=menu.c

all:
	gcc main.c $(CompileFiles) -o play -I ./include -L ./lib -l SDL2-2.0.0 -lSDL2_image
