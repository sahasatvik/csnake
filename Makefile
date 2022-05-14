CC=gcc
CFLAGS=-Wall
MAIN=csnake.c
TARGET=csnake
OBJS=keys.o \
     screen.o \
     entities.o

all : $(TARGET)

$(TARGET) : $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(OBJS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

keys.o: entities.o screen.o

entities.o: screen.o

clean :
	rm $(TARGET) $(OBJS)
