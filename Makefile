#cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY : all clean run hotload check

cc = gcc -Wall -Wextra
debugflug = -g -Wno-unused-parameter
CFLUG = -s -O3 -Os
LINKFLUG =-Wl,--gc-sections -lcglm -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
LIB = -L./lib
INCLUDE = -I./include

all : build/genmap.out build/redmap.out build/edit.out

clear :
	rm -r build/*

check : build/genmap.out build/redmap.out
	build/genmap.out
	build/redmap.out the4.btb

build/edit.out : build/edit.o build/glad.o build/gllib.o build/stb_image.o
	$(cc) $(debugflug) $(LINKFLUG) $^ -o $@ $(LIB) $(INCLUDE) $(LINKFLUG)

build/edit.o : edit.c
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

build/redmap.out : build/redmap.o
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/redmap.o : redmap.c include/btb.h
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

build/genmap.out : build/genmap.o
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/genmap.o : genmap.c include/btb.h
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

build/stb_image.o : stb_image.c
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

build/hotload.o : hotload.c
	$(cc) -c $(debugflug) $< -o $@ $(INCLUDE)

build/glad.o : glad.c
	gcc -c $< -o $@ $(INCLUDE)

build/gllib.o : gllib.c include/gllib.h
	gcc -c $< -o $@ $(INCLUDE)
# run : ./build/output.out build/*.so
# 	./build/output.out
# hotload : build/*.so
# clean :
# 	rm ./build/*

# build/output.out : build/main.o build/hotload.o
# 	$(cc) $(debugflug) -g main.c hotload.c -o ./build/output.out $(LINKFLUG)
# # build/outputs.out : main.c hotload.c build/room.so rooms/room.h
# # 	$(cc) $(debugflug) -g main.c hotload.c -o ./build/output.out $(LINKFLUG)

# build/main.o : main.c main.h
# 	$(cc) $(debugflug) -g -c $< -o $@ $(LINKFLUG)
# build/hotload.o : hotload.c main.h
# 	$(cc) $(debugflug) -g -c $< -o $@ $(LINKFLUG)

# # build/room.so : rooms/room.c
# # 	$(cc) $(debugflug) -fPIC -shared rooms/room.c -o build/room.so $(LINKFLUG)
# build/*.so : rooms/*.c
# 	$(cc) $(debugflug) -fPIC -shared $< -o $@ $(LINKFLUG)
