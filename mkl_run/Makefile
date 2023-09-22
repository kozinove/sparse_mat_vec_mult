
include ./Makefile.inc

OBJS  = main.o MatMV.o


default: build

build: mkl_mv

mkl_mv: $(OBJS)
		$(CC) $(OPTC) -o$@ $? -L../util -lutil
	
.c.o:
		$(CC) $(OPTC) -c $*.c $(OUTC)$*.o

clean:
		$(RM) ./*.o 
		$(RM) ./mkl_mv 
