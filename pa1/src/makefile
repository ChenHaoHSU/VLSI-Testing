
EXE       = atpg
CXX       = g++
CHDRS     = $(wildcard *.h)
CSRCS     = $(wildcard *.cpp)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))

CFLAGS    = -std=c++11 -g -Wall
CFLAGS    = -std=c++11 -O3

ECHO      = echo
RM        = rm -rf

$(EXE): $(COBJS)
	@$(ECHO) "[Build Target] $(EXE)"
	@$(CXX) $(CFLAGS) $(COBJS) -lm -o $(EXE)

%.o: %.cpp $(CHDRS)
	@$(ECHO) "[Compile] $<"
	@$(CXX) $(CFLAGS) -c $<

clean:
	@$(RM) $(EXE) *.o