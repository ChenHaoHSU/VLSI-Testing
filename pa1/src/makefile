
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
	@$(ECHO) "[Build] $(EXE)"
	@$(CXX) $(CFLAGS) $(COBJS) -lm -o $(EXE)

%.o: %.cpp $(CHDRS)
	@$(ECHO) "[Compile] $<"
	@$(CXX) $(CFLAGS) -c $<

clean:
	@$(RM) $(EXE) *.o

direct:
	@$(ECHO) "[Compile] All"
	@$(CXX) $(CFLAGS) $(COBJS:.o=.cpp) -o $(EXE)
	@$(ECHO) "[Build] $(EXE) ..."