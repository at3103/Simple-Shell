cc=gcc

src=shell.c

idir=../include
cflag=-I$(idir)
_depends=shell.h 
depends=$(patsubst %,$(idir)/%,$(_depends) )

_obj= a.o
odir=./obj
obj=$(patsubst%,$(odir)/%,$(_obj))

$(odir)/%.o:%.c
	$(cc) -c -o $@ $< $(cflags) 

w4118_sh:$(src) $(obj) $(deps)
	$(cc) -o $@ $^ $(cflags)

clean:
	rm -f $(odir)/*.o w4118_sh *~


