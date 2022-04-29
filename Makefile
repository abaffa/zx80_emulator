INCLUDES= -I ./include
FLAGS = -O3 -std=c++11


#OBJECTS=./build/z80_memory.o ./build/zx80_keyboard.o ./build/zx80_screen.o  ./build/z80.o
OBJECTS=./build/hw_web.o ./build/linkedlist.o ./build/queue_ll.o ./build/tasm_opcode.o ./build/utils.o ./build/zx80_memory.o ./build/zx80_keyboard.o ./build/zx80_screen.o ./build/z80.o

all: ${OBJECTS} 
		gcc ${FLAGS} ${INCLUDES} ./src/main.cpp ${OBJECTS} -L ./lib -lmingw32  -lwsock32 -lstdc++ -o ./bin/main.exe	

web_emul: ${OBJECTS} 
		gcc ${FLAGS} ${INCLUDES} ./src/web_emul.cpp ${OBJECTS} -L ./lib -lmingw32  -lwsock32 -lstdc++ -o ./bin/web_emul.exe	

web_emul_test: ${OBJECTS} 
		gcc ${FLAGS} ${INCLUDES} ./src/web_emul_test.cpp ${OBJECTS} -L ./lib -lmingw32  -lwsock32 -lstdc++ -lSDL2main -lSDL2 -o ./bin/web_emul_test.exe	
		
./build/hw_web.o:src/hw_web.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/hw_web.cpp -c -o ./build/hw_web.o

./build/linkedlist.o:src/linkedlist.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/linkedlist.cpp -c -o ./build/linkedlist.o

./build/queue_ll.o:src/queue_ll.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/queue_ll.cpp -c -o ./build/queue_ll.o

./build/tasm_opcode.o:src/tasm_opcode.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/tasm_opcode.cpp -c -o ./build/tasm_opcode.o

./build/utils.o:src/utils.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/utils.cpp -c -o ./build/utils.o

./build/zx80_memory.o:src/zx80_memory.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/zx80_memory.cpp -c -o ./build/zx80_memory.o

./build/zx80_keyboard.o:src/zx80_keyboard.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/zx80_keyboard.cpp -c -o ./build/zx80_keyboard.o

./build/zx80_screen.o:src/zx80_screen.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/zx80_screen.cpp -c -o ./build/zx80_screen.o

./build/z80.o:src/z80.cpp
	gcc ${FLAGS} ${INCLUDES} ./src/z80.cpp -c -o ./build/z80.o


clean:
	del build\* /q
	del bin\main.exe /q
	del bin\web_emul.exe /q
	del bin\web_emul_test.exe /q
