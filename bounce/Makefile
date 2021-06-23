all: RawBounce Bounce

RawBounce: raw_bounce.c
	gcc -o RawBounce -g raw_bounce.c
Bounce: bounce.c
	gcc bounce.c -g -o Bounce
clean:
	rm *.o
