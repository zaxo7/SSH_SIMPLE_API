
CC = g++



all: ssh_session


ssh_session: 
	$(CC) -c src/ssh_session.cpp -o src/ssh_session.o