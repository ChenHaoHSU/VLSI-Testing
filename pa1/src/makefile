
CFLAGS    = -std=c++11 -g
CFLAGS    = -std=c++11 -O3

EXE       = atpg
CXX       = g++
CHDRS     = $(wildcard *.h)
CSRCS     = $(wildcard *.cpp)
COBJS     = $(addsuffix .o, $(basename $(CSRCS)))
RM        = rm -rf

$(EXE) : $(COBJS)
	@echo ">> Building $(EXE) ..."
	@$(CXX) $(CFLAGS) $(COBJS) -lm -o $(EXE)
%.o : %.cpp $(CHDRS)
	@echo "> Compiling $< ..."
	@$(CXX) $(CFLAGS) -c $<
clean:
	@$(RM) $(EXE) *.o
direct:
	@echo "> Compiling all ..."
	@$(CXX) $(CFLAGS) $(COBJS:.o=.cpp) -o $(EXE)
	@echo ">> Building $(EXE) ..."