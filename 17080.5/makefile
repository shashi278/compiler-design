CC=cc
CFLAGS=-I.
DEPS = lex.h parser.h stack.h
OBJFILES = lex.o parser.o stack.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -Wall -o $@ $< $(CFLAGS)

a.out: $(OBJFILES)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm a.out $(OBJFILES)