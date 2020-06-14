# sudo apt-get install gcc-multilib
CFLAGS=-m32

default: test

test64:
	$(MAKE) CFLAGS=-m64 test
bench64:
	$(MAKE) CFLAGS=-m64 bench

test: ctap
	gcc $(CFLAGS) -o ./test src/fast_inv_sqrt.c spec/fast_inv_sqrt.c && ./test; rm -f ./test

ctap:
	git submodule update

bench:
	gcc $(CFLAGS) src/fast_inv_sqrt.c benchmark/fast_inv_sqrt.c -o $@
	sudo ./$@; rm $@
