#

CFLAGS = -std=c++11 -g 

FILES = atpg.o tpgmain.o input.o level.o sim.o podem.o test.o init_flist.o faultsim.o display.o

atpg : $(FILES) 
	g++ $(CFLAGS) $(FILES) -lm -o atpg

atpg.o : atpg.h
	g++ $(CFLAGS) -c atpg.cpp
tpgmain.o : atpg.h tpgmain.cpp
	g++ $(CFLAGS) -c tpgmain.cpp
input.o : atpg.h
	g++ $(CFLAGS) -c input.cpp
level.o : atpg.h
	g++ $(CFLAGS) -c level.cpp
sim.o : atpg.h logic_tbl.h
	g++ $(CFLAGS) -c sim.cpp
podem.o : atpg.h
	g++ $(CFLAGS) -c podem.cpp
init_flist.o : atpg.h
	g++ $(CFLAGS) -c init_flist.cpp
faultsim.o : atpg.h
	g++ $(CFLAGS) -c faultsim.cpp
test.o : atpg.h
	g++ $(CFLAGS) -c test.cpp
display.o : atpg.h
	g++ $(CFLAGS) -c display.cpp
clean:
	rm *.o
direct:
	g++ $(CFLAGS)$(FILES:.o=.cpp) -o atpg
