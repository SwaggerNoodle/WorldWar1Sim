PROGRAM=WorldWar1Sim.exe 
SERVER=WorldWar1Sim_Server.exe
OBJECTS=main.o network.o 
S_OBJECTS=server.o
CLIENT_LIBS=-lws2_32 -luser32 -lgdi32 -mwindows
SERVER_LIBS=-lws2_32

all: $(PROGRAM) $(SERVER)

$(PROGRAM): $(OBJECTS)
	gcc -Wall -o $(PROGRAM) $(OBJECTS) $(CLIENT_LIBS)

$(SERVER): $(S_OBJECTS)
	gcc -Wall -o $(SERVER) $(S_OBJECTS) $(SERVER_LIBS)


network.o: network.c network.h
	gcc -Wall -c network.c

server.o: server.c
	gcc -Wall -c server.c

main.o: main.c network.h
	gcc -Wall -c main.c




cleanAll:
	rm -f $(OBJECTS) $(S_OBJECTS) $(PROGRAM) $(SERVER)

cleanClient:
	rm -f $(OBJECTS) $(PROGRAM)
	
cleanServer:
	rm -f $(S_OBJECTS) $(SERVER)

