CC = gcc
CFLAGS =
DEPS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o 
	$(CC) -o main main.o

clean:
	-rm -f *.o
	-rm -f main