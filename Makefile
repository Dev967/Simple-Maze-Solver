CPP=g++
objects = Main.o Solver.o

all: $(objects)
	$(CPP) $(objects)

$(objects): %.o: %.cpp
