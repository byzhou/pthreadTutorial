FLAGS       := -g -Wall -O3

APPS        := helloworld

all: run

%: %.c
	~/colorgcc $(FLAGS) -pthread $@.c -o $@

run: $(APPS)
	./helloworld read.txt write.txt

clean:
	rm -rf *.o $(APPS)

