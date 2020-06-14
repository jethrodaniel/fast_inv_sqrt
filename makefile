default: test bench

test: ctap
	gcc -o ./test src/fast_inv_sqrt.c spec/fast_inv_sqrt.c && ./test; rm -f ./test

ctap:
	git submodule update

bench:
	gcc src/fast_inv_sqrt.c benchmark/fast_inv_sqrt.c -o $@
	sudo ./$@; rm $@
