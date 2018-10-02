
CFLAGS    = -std=c++11 -g
CFLAGS    = -std=c++11 -O3

EXE       = atpg
CXX       = g++
CHDRS     = $(wildcard *.h)
CSRCS     = $(wildcard *.cpp)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))

ECHO      = echo
RM        = rm -rf

$(EXE): $(COBJS)
	@$(ECHO) ">> Building $(EXE) ..."
	@$(CXX) $(CFLAGS) $(COBJS) -lm -o $(EXE)

%.o: %.cpp $(CHDRS)
	@$(ECHO) "> Compiling $< ..."
	@$(CXX) $(CFLAGS) -c $<

clean:
	@$(RM) $(EXE) *.o

direct:
	@$(ECHO) "> Compiling all ..."
	@$(CXX) $(CFLAGS) $(COBJS:.o=.cpp) -o $(EXE)
	@$(ECHO) ">> Building $(EXE) ..."