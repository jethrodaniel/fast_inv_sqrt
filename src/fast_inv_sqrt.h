// #include <limits.h>
// #include <assert.h>
//
// // `float` should be 32 bits, as per the IEEE 754 specification.
// //
// // From https://stackoverflow.com/a/18705626/7132678
// assert(CHAR_BIT * sizeof(float) == 32)

#include <stdint.h>

float Q_rsqrt(float number);
float fast_inv_sqrt(float number);
