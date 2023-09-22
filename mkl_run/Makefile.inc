CXX  = icpx  -std=c++11
CC  = icx
AR  = ar rcs 
RANLIB = ranlib
RM  = rm -f
CP  = cp
MV  = mv
LIBEXT  = .a
LIBPREF = lib
MAKE_DIR = mkdir -p

OUTC    = -o

ifeq ($(mode), release)
   CFLAGS   = -O3 -qopenmp
else 
ifeq ($(mode), debug)
   CFLAGS   = -g -O0 -qopenmp
   else 
   CFLAGS   = -O3 -g -qopenmp
endif 
endif

CFLAGS +=  -qmkl=parallel -I../util

OPTC = $(CFLAGS) 

LD_FLAGS = 

