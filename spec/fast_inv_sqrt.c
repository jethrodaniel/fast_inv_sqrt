#include "../third_party/ctap/include/ctap.h"

#include "../src/fast_inv_sqrt.h"

#define quake_3_inv_sqrt Q_rsqrt

TESTS {
  cmp_ok(quake_3_inv_sqrt(25), "==", 0.2, "1/√25 == 0.2");
}
