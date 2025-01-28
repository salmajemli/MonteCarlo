OBJS	= ../../parameters.o ../../Simulation.o ../../SetOfParticles.o test_SAMPLES_2D.o
SOURCE	= ../../parameters.cpp ../../Simulation.cpp ../../SetOfParticles.cpp test_SAMPLES_2D.cpp
HEADER	= ../../parameters.hpp ../../Simulation.hpp ../../SetOfParticles.hpp 
OUT	= test_SAMPLES_2D
CXX	 = g++
FLAGS	 = -c -O3 -std=c++11

all: $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT) $(LFLAGS)

parametres.o: parametres.cpp
	$(CXX) $(FLAGS) parametres.cpp 

Simulation.o: Simulation.cpp
	$(CXX) $(FLAGS) Simulation.cpp 

SetOfParticles.o: SetOfParticles.cpp
	$(CXX) $(FLAGS) SetOfParticles.cpp 

test_SAMPLES_2D.o: test_SAMPLES_2D.cpp
	$(CXX) $(FLAGS) test_SAMPLES_2D.cpp 


clean:
	rm -f $(OBJS) $(OUT) Resultats/solution*.txt *.png
clean_res:
	rm -f Resultats/solution*.txt