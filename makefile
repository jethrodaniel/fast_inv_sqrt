CTAP_MAKE = $(MAKE) -C third_party/ctap

# ctap:
	# cd third_party/ctap && git submodule update && autoreconf -vi && ./configure && make; cd -

test: # ctap
	gcc -o .spec fast_inv_sqrt_spec.c && ./.spec

clean:
	rm -f .spec *.o
	# $(CTAP_MAKE) clean
