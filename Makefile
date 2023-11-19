CC = g++
CFLAGS = -IC:\mingw64\include\ -LC:\mingw64\lib -w -Wl,-subsystem,windows
LINKER = -lmingw32 -lSDL2main -lSDL2
OUT = -o "life.exe"

compile: build/main.o build/logic.o build/engine.o
	${CC} ${CFLAGS} ${OUT} "build/main.o" "build/engine.o" "build/logic.o" ${LINKER}
	./life.exe

build/engine.o: src/engine.cpp
	${CC} ${CFLAGS} -c "src/engine.cpp" -o "build/engine.o" ${LINKER}
build/logic.o: src/logic.cpp
	${CC} ${CFLAGS} -c "src/logic.cpp" -o "build/logic.o" ${LINKER}
build/main.o: src/main.cpp
	${CC} ${CFLAGS} -c "src/main.cpp" -o "build/main.o" ${LINKER}

clean:
	rm -f build/*.o