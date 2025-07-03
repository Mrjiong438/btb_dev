#cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY : all clean run hotload check

cc = gcc -Wall -Wextra
debugflug = -g -Wno-unused-parameter
CFLUG = -s -O3 -Os
LINKFLUG =-Wl,--gc-sections -lcglm -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
LIB = -L./lib
INCLUDE = -I./include

all : build/genmap.out build/redmap.out #build/edit.out

clear :
	rm -r build/*

check : build/genmap.out build/redmap.out
	build/genmap.out
	build/redmap.out the4.btb

# build/edit.out : build/edit.o build/glad.o build/gllib.o build/stb_image.o
# 	$(cc) $(debugflug) $(LINKFLUG) $^ -o $@ $(LIB) $(INCLUDE) $(LINKFLUG)

build/redmap.out : redmap.c
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/genmap.out : genmap.c
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/stb_image.o : stb_image.c
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

