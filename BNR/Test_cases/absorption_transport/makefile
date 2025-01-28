OBJS	= ../../../parameters.o ../../../Simulation.o ../../../SetOfParticles.o absorption.o
SOURCE	= ../../../parameters.cpp ../../../Simulation.cpp ../../../SetOfParticles.cpp absorption.cpp
HEADER	= ../../../parameters.hpp ../../../Simulation.hpp ../../../SetOfParticles.hpp 
OUT	= absorption
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

absorption.o: absorption.cpp
	$(CXX) $(FLAGS) absorption.cpp 


clean:
	rm -f $(OBJS) $(OUT) Resultats/solution*.txt *.png
clean_res:
	rm -f Resultats/solution*.txt