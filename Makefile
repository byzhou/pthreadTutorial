FLAGS       := -g -Wall -O3

APPS        := helloworld

all: $(APPS)

%: %.c
    gcc $(FLAGS) -pthread $@.c -o $@

clean:
	rm -rf *.o $(APPS)

