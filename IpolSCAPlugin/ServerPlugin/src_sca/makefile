# Copyright 2010 Jose-Luis Lisani <joseluis.lisani@uib.es>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.
# 
# Modified October 2011 by Catalina Sbert

CSRC	= io_png.c   auxiliary_lib.c poisson_lca_lib.c
CXXSRC= parser.cpp  poisson_lca.cpp 

# all source code
SRC	= $(CXXSRC) $(CSRC) 

# C and C++ objects
COBJ	= $(CSRC:.c=.o)
CXXOBJ  = $(CXXSRC:.cpp=.o)
# all objects
OBJ	= $(CXXOBJ) $(COBJ) 

# binary target
BIN	= poisson_lca

default	: $(BIN)

# C optimization flags
COPT	= -O3 -ftree-vectorize -funroll-loops

CXXOPT= $(COPT)

# C compilation flags
CFLAGS	= $(COPT) -Wall -Wextra -Werror \
	-Wno-write-strings -ansi 
	
CXXFLAGS	= $(CXXOPT) -Wall -Wextra  \
	-Wno-write-strings -Wno-deprecated -ansi -fopenmp

# link flags
LDFLAGS	= -lfftw3 -lpng -lm -fopenmp



# partial compilation of C source code
%.o: %.c %.h
	$(CC) -c -o $@  $< $(CFLAGS) -I/opt/local/include/ -I/usr/local/include/   
# partial compilation of C++ source code
%.o: %.cpp %.h
	$(CXX) -c -o $@  $< $(CXXFLAGS) -I/opt/local/include/ -I/usr/local/include/ 


# link all the object code



$(BIN)	: $(OBJ) $(CXXOBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) -L/opt/local/lib/ -L/usr/local/lib/



.PHONY	: clean distclean
clean	:
	$(RM) $(OBJ)
distclean	: clean
	$(RM) $(BIN)
