OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=ring
BIN2=disc
BIN3=surprise
BIN4=chess
SRCS1=ring.cpp gl_framework.cpp shader_util.cpp stb_image.cpp
SRCS2=disc.cpp gl_framework.cpp shader_util.cpp stb_image.cpp
SRCS3=surprise.cpp gl_framework.cpp shader_util.cpp stb_image.cpp
SRCS4=chess.cpp gl_framework.cpp shader_util.cpp stb_image.cpp
INCLUDES=gl_framework.hpp shader_util.hpp stb_image.h

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)

$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)

$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN1) $(BIN2) $(BIN3) $(BIN4) 
