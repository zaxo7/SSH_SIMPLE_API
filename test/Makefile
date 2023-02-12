

all: clean connection_test runtests


connection_test: 
	$(CC) connection_test.cpp -o connection_test -L../lib -lsshSimpleAPI -lssh


clean:
	rm -rf connection_test

runtests:
	./connection_test