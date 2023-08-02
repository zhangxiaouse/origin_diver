INCLUDES=

LIBLINKS=

SOURCES=                               \
	camera/camera.cpp                    \
	event/*.cpp                          \
	state/notshoot/idle.cpp              \
	state/notshoot/notshooting.cpp       \
	state/notshoot/configuring.cpp       \
	state/shoot/shooting.cpp             \
	state/shoot/focusing.cpp             \
	state/shoot/focused.cpp              \
	state/shoot/storing.cpp              \

EXE=run


all: clean build

build:
	mkdir -p bin
	g++ -g -o $(EXE) $(INCLUDES) $(SOURCES) $(LIBLINKS)

clean:
	rm -f $(EXE)

test:
	./$(EXE)