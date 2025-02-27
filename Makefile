#cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY : all clean run hotload check

cc = gcc -Wall -Wextra
debugflug = -Wno-unused-parameter
CFLUG = -s -O3 -Os
LINKFLUG =-Wl,--gc-sections -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIB =-lm

all : build/genmap.out build/redmap.out

check : build/genmap.out build/redmap.out
	build/genmap.out
	build/redmap.out the4.btb

build/redmap.out : build/redmap.o build/stb_image.o
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/redmap.o : redmap.c btb.h
	$(cc) -c $(debugflug) $< -o $@

build/genmap.out : build/genmap.o build/stb_image.o
	$(cc) $(debugflug) $^ -o $@ $(LIB)

build/genmap.o : genmap.c btb.h
	$(cc) -c $(debugflug) $< -o $@

build/stb_image.o : stb_image.c
	$(cc) -c $(debugflug) $< -o $@
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
