GCC= gcc
GCCFLAGS= -std=gnu99  -Wall -pedantic 
GCCLIBS= -lm

SOURCES_SERVER= ourServer.c
SOURCES_CLIENT= client.c
SOURCES_CHALLENGES= challenges.c
SOURCES_LIB= lib.c

OBJECT_CHALLENGES=$(SOURCES_CHALLENGES:.c=.o)
OBJECTS_LIB=$(SOURCES_LIB:.c=.o)

SERVER_EXEC= ourServer
CLIENT_EXEC= client

all: $(OBJECT_CHALLENGES) client
		$(GCC) $(GCCFLAGS) $(SOURCES_SERVER) $(SOURCES_CHALLENGES) $(SOURCES_LIB) -I./include -o $(SERVER_EXEC) $(GCCLIBS)

%.o: %.c
		$(GCC) $(GCCFLAGS) -I./include -c $^ $(GCCLIBS)


client:
		$(GCC) -I./include $(SOURCES_CLIENT) $(SOURCES_LIB) -o $(CLIENT_EXEC) $(GCCFLAGS)

clean:
		rm -rf *.o ourServer client ./src/*.o

.PHONY: all clean client