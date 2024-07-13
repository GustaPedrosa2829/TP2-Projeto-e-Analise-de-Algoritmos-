# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Nome do executável
TARGET = tp2

all: $(TARGET)

$(TARGET): tp2.o tp2fun.o
	$(CC) $(CFLAGS) -o $(TARGET) tp2.o tp2fun.o

tp2.o: tp2.c
	$(CC) $(CFLAGS) -c tp2.c

tp2fun.o: tp2fun.c
	$(CC) $(CFLAGS) -c tp2fun.c

clean:
	rm -f *.o $(TARGET)
