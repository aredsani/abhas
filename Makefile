#Makefile

# C++ compiler
CXX	=g++
CC	=$(CXX)

# Include and lib directories
LIB_DIR=.
INC_DIR1= lGL 
INC_DIR2= lGLU
INC_DIR3= lglut
INC_DIR4= lGLEW
INC_SOME= /usr/local/include

# options to pass to the compiler
CXXFLAGS= -Wall -g -$(INC_DIR1) -$(INC_DIR2) -$(INC_DIR3) -$(INC_DIR4) 
CXXFLAGS2= -Wall -g -I$(LIB_DIR) 
CXXFlags3= -Wall -g -I$(LIB_DIR) -I$(INC_SOME)
all: random.cpp texture.cpp shader.cpp LIB_shapes LIB_objLoader 
	$(CXX)  -I. $(CXXFlags3) random.cpp texture.cpp shader.cpp objloader.o shapes.o   $(CXXFLAGS) `pkg-config --cflags opencv` maya.cpp  `pkg-config --libs opencv` -o run
	rm -f *.o

LIB_objLoader: objloader.cpp
	$(CXX) $(CXXFLAGS2) -c objloader.cpp

LIB_shapes: shapes.cpp 
	$(CXX) $(CXXFLAGS2) -c shapes.cpp

LIB_gesture: maya.cpp
	$(CXX) $(CXXFlags3) -c `pkg-config --cflags opencv` maya.cpp  `pkg-config --libs opencv`
clean:
	rm -f *.o run
