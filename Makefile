
export CC = g++
export RANLIB = ranlib
export AR = ar

export CFLAGS = -Wall
export LDFLAGS

all: library tests


library:
	$(MAKE) -C src

tests:
	$(MAKE) -C test