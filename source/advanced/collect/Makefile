NAME = collect

SRC = $(NAME).cpp

C74SUPPORT = ../../c74support
SRC += $(C74SUPPORT)/max-includes/common/commonsyms.c

CC = g++

CFLAGS = -c -DWIN_VERSION -DWIN_EXT_VERSION -I$(C74SUPPORT)/max-includes -mno-cygwin
LDFLAGS = -shared -L$(C74SUPPORT)/max-includes -lMaxAPI -static-libgcc -mno-cygwin

# using -static-libgcc in the above line means that throwing exceptions across DLL boundaries won't work,
# but it also means that we don't depend on the libgcc dll

Debug: 
	$(CC) $(CFLAGS) -g $(SRC)
	$(CC) -o $(NAME).mxe $(NAME).o commonsyms.o $(LDFLAGS) 

Release: 
	$(CC) $(CFLAGS) $(SRC)
	$(CC) -o $(NAME).mxe $(NAME).o commonsyms.o $(LDFLAGS) 
	
clean:
	rm -f *.o
	rm -f $(NAME).mxe
