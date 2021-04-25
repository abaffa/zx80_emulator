INCLUDES= -I ./include
FLAGS = -O3
#FLAGS2 = -g

OBJECTS=./build/z80_memory.o ./build/zx80_keyboard.o ./build/zx80_screen.o  ./build/z80.o

all: ${OBJECTS} 
	gcc ${FLAGS} ${INCLUDES} ./src/test.c ${OBJECTS} -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o ./bin/test.exe	

main: ${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o ./bin/main.exe	

main2: ${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main2.c ${OBJECTS} -L ./lib -lmingw32 -o ./bin/main2.exe	

./build/z80_memory.o:src/z80_memory.c
	gcc ${FLAGS} ${INCLUDES} ./src/z80_memory.c -c -o ./build/z80_memory.o
	
./build/zx80_keyboard.o:src/zx80_keyboard.c
	gcc ${FLAGS} ${INCLUDES} ./src/zx80_keyboard.c -c -o ./build/zx80_keyboard.o

./build/zx80_screen.o:src/zx80_screen.c
	gcc ${FLAGS} ${INCLUDES} ./src/zx80_screen.c -c -o ./build/zx80_screen.o	
	
./build/z80.o:src/z80.c
	gcc ${FLAGS} ${INCLUDES} ./src/z80.c -c -o ./build/z80.o

clean:
	del build\* /q
	del bin\main.exe /q
	del bin\main2.exe /q
	del bin\test.exe /q