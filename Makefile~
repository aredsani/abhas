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


# options to pass to the compiler
CXXFLAGS= -Wall -g -$(INC_DIR1) -$(INC_DIR2) -$(INC_DIR3) -$(INC_DIR4) 
CXXFLAGS2= -Wall -g -I$(LIB_DIR) 

all: random.cpp texture.cpp LIB_shapes LIB_objLoader 
	$(CXX) $(CXXFLAGS) -I.  random.cpp texture.cpp objloader.o shapes.o -o run
	rm -f *.o

LIB_objLoader: objloader.cpp
	$(CXX) $(CXXFLAGS2) -c objloader.cpp

LIB_shapes: shapes.cpp 
	$(CXX) $(CXXFLAGS2) -c shapes.cpp

clean:
	rm -f *.o run
