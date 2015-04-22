NAME = mydll
C74SUPPORT = ../../c74support

CC_32 = /usr/bin/clang++ -arch i386
CC_64 = /usr/bin/clang++ -arch x86_64

#########################################

SRC32 = $(NAME).i386.o 
SRC64 = $(NAME).x64.o

#########################################

INCLUDES = -I./
INCLUDES += -I$(C74SUPPORT)/max-includes
INCLUDE_FILES := $(wildcard INCLUDES/*.h)

#########################################

OPTIMIZATION_DEBUG = -O0
OPTIMIZATION_RELEASE = -O3

OPTIONS = -shared -msse3 -gdwarf-2
WARNINGS = -Wall -Wno-unknown-pragmas -Wno-trigraphs
#DEFINES = -DTT_PLATFORM_MAC

#########################################

CFLAGS = $(OPTIONS) $(DEFINES) $(INCLUDES) $(WARNINGS)
CFLAGS += -include$(C74SUPPORT)/max-includes/macho-prefix.pch
LDFLAGS = $(OPTIONS) $(DEFINES) $(LIBS) $(WARNINGS)
C74SYMS = -Wl,-U,_post,-U,_object_post
LDFLAGS += $(C74SYMS)

# @loader_path will point to e.g. MyPackage/externals/dllcounter.mxo/Contents/MacOS
# We want it to find our dylib in the support folder of the package
LDFLAGS += -install_name "@loader_path/../../../../support/$(NAME).dylib" 


#########################################

Debug: OPTIMIZATION_FLAGS = $(OPTIMIZATION_DEBUG)
Debug: createdirs lipo

Release: OPTIMIZATION_FLAGS = $(OPTIMIZATION_RELEASE)
Release: createdirs lipo

createdirs:
	mkdir -p build
	mkdir -p ../../../support

%.i386.o: %.cpp ${INCLUDE_FILES}
	$(CC_32) $(CFLAGS) $(OPTIMIZATION_FLAGS) -c $< -o $@
%.x64.o: %.cpp ${INCLUDE_FILES}
	$(CC_64) $(CFLAGS) $(OPTIMIZATION_FLAGS) -c $< -o $@

link: i386 x64 | $(SRC32) $(SRC64)

i386: $(SRC32)
	$(CC_32) $(LDFLAGS) $(OPTIMIZATION_FLAGS) -o build/$(NAME)-i386.dylib $(SRC32)

x64: $(SRC64)
	$(CC_64) $(LDFLAGS) $(OPTIMIZATION_FLAGS) -o build/$(NAME)-x86_64.dylib $(SRC64)

lipo: | link
	lipo build/$(NAME)-i386.dylib build/$(NAME)-x86_64.dylib -create -output build/$(NAME).dylib
	cp build/$(NAME).dylib ../../../support

clean:
	rm -f $(SRC32) $(SRC64)
	rm -rf build
