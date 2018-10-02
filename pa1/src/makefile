#
EXE       = atpg

CXX       = g++

CFLAGS    = -std=c++11 -g
CFLAGS    = -std=c++11 -O3

CHDRS     = $(wildcard *.h)
CSRCS     = $(wildcard *.cpp)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))

RM        = rm

$(EXE) : $(COBJS) 
	$(CXX) $(CFLAGS) $(COBJS) -lm -o $(EXE)
%.o : %.cpp $(CHDRS)
	$(CXX) $(CFLAGS) -c $<
clean:
	$(RM) *.o
direct:
	$(CXX) $(CFLAGS) $(COBJS:.o=.cpp) -o $(EXE)