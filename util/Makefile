include ./Makefile.inc

OBJS  = MatMV.o readFile.o mmio.o


default: build

build: $(LIBPREF)util$(PLAT)$(LIBEXT)

$(LIBPREF)util$(PLAT)$(LIBEXT): $(OBJS)
		$(AR)$@ $?
		$(RANLIB) $@
	
.c.o:
		$(CC) $(OPTC) -c $*.c $(OUTC)$*.o

clean:
		$(RM) ./*.o 
		$(RM) ./*.a 
