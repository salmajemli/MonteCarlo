OBJS	= ../../../parameters.o ../../../Simulation.o ../../../SetOfParticles.o advection.o
SOURCE	= ../../../parameters.cpp ../../../Simulation.cpp ../../../SetOfParticles.cpp advection.cpp
HEADER	= ../../../parameters.hpp ../../../Simulation.hpp ../../../SetOfParticles.hpp 
OUT	= advection
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

advection.o: advection.cpp
	$(CXX) $(FLAGS) advection.cpp 


clean:
	rm -f $(OBJS) $(OUT) Resultats/solution*.txt *.png
clean_res:
	rm -f Resultats/solution*.txt