test: ctap
	gcc -o ./test src/fast_inv_sqrt.c spec/fast_inv_sqrt.c && ./test; rm -f ./test

ctap:
	git submodule update
