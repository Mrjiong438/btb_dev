#cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY : all clean run hotload

cc = gcc -Wall -Wextra
debugflug = -Wno-unused-parameter
object = build/main.o 
object_win = build/winmain.o build/winsnaker.o build/winsnake.o
CFLUG = -s -O3 -Os
LINKFLUG =-Wl,--gc-sections -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIB = -I ./raylib-5.5_linux_amd64/include -L ./raylib-5.5_linux_amd64/lib
LIB_WIN = -I ./raylib-5.5_linux_amd64/include -L ./raylib-5.5_linux_amd64/lib
LINKFLUG_WIN =-Wl,--gc-sections -lraylib -lgdi32 -lwinmm

all : build/genmap.out build/redmap.out

build/redmap.out : build/redmap.o
	$(cc) $(debugflug) $< -o $@

build/redmap.o : redmap.c btb.h
	$(cc) -c $(debugflug) $< -o $@

build/genmap.out : build/genmap.o
	$(cc) $(debugflug) $< -o $@

build/genmap.o : genmap.c btb.h
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
