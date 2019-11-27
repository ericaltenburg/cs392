# Eric Altenburg
# I pledge my honor that I have abided by the Stevens Honor System.

C = gcc
OBJS = cs392_fprintf.o
HDRS = cs392_fprintf.h

libcs392_io.so : cs392_fprintf.o
	$(C) -shared -o libcs392_io.so $(OBJS)

cs392_fprintf.o : cs392_fprintf.c $(HDRS)
	$(C) -fPIC -c -g cs392_fprintf.c
