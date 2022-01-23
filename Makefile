CPP=g++
objects = Main.o Solver.o

out: $(objects)
	$(CPP) $(objects)

$(objects): %.o: %.cpp