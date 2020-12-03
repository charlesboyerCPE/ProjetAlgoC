CC ?= gcc

COBJS ?= client.o bmp.o couleur.o validateur.o
SOBJS ?= serveur.o
UOBJS ?= tests.o bmp.o couleur.o validateur.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client
TESTS = tests

all: $(SERVER) $(CLIENT) $(TESTS)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS) -lm
$(TESTS): $(UOBJS)
	$(CC) -o $(TESTS) $(UOBJS) -lm

.c.o: 
	$(CC) -c $*.c -lm


