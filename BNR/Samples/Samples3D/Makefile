OBJS	= test_SAMPLES_3D.o
SOURCE	= test_SAMPLES_3D.cpp
OUT	= test_SAMPLES_3D
CXX	 = g++
FLAGS	 = -c -O3 -std=c++11

all: $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT) $(LFLAGS)

test_SAMPLES_3D.o: test_SAMPLES_3D.cpp
	$(CXX) $(FLAGS) test_SAMPLES_3D.cpp 

