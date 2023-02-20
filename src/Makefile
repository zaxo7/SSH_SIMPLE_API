

all: libsshSimpleAPI.a clean


ssh_session.o: 
	$(CC) $(CFLAGS) -c ssh_session.cpp -o ssh_session.o

ssh_channel.o:
	$(CC) $(CFLAGS) -c ssh_channel.cpp -o ssh_channel.o

libsshSimpleAPI.a: ssh_session.o ssh_channel.o
	$(AR) -rc ../lib/libsshSimpleAPI.a *.o
	$(RANLIB) ../lib/libsshSimpleAPI.a

clean:
	rm -rf *.o