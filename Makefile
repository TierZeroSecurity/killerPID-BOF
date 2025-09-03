BOFNAME := killerPID-BOF
CC_x64 := x86_64-w64-mingw32-gcc
CC_x86 := i686-w64-mingw32-gcc
CC_x86_STRIP := i686-w64-mingw32-strip
CC_x64_STRIP := x86_64-w64-mingw32-strip

all:
	$(CC_x64) -o $(BOFNAME).x64.o -c entry.c
	$(CC_x86) -o $(BOFNAME).x86.o -c entry.c
	$(CC_x64_STRIP) --strip-unneeded $(BOFNAME).x64.o
	$(CC_x86_STRIP) --strip-unneeded $(BOFNAME).x86.o

clean:
	rm $(BOFNAME).*.o
