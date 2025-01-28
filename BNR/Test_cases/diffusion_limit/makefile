OBJS	= ../../../parameters.o ../../../Simulation.o ../../../SetOfParticles.o diffusion.o
SOURCE	= ../../../parameters.cpp ../../../Simulation.cpp ../../../SetOfParticles.cpp diffusion.cpp
HEADER	= ../../../parameters.hpp ../../../Simulation.hpp ../../../SetOfParticles.hpp 
OUT	= diffusion
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

diffusion.o: diffusion.cpp
	$(CXX) $(FLAGS) diffusion.cpp 


clean:
	rm -f $(OBJS) $(OUT) Resultats/solution*.txt *.png
clean_res:
	rm -f Resultats/solution*.txt