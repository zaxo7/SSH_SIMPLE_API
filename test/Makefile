
CFLAGS += -I../src

all: clean connection_test runtests


connection_test: 
	$(CC) connection_test.cpp $(CFLAGS) -o connection_test $(LDFLAGS)


clean:
	rm -rf connection_test

runtests:
	./connection_test