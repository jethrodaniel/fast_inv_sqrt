#include "../third_party/ctap/include/ctap.h"

#include "../src/fast_inv_sqrt.h"

#define quake_3_inv_sqrt Q_rsqrt

TESTS {
  cmp_ok(quake_3_inv_sqrt(25), "==", 0.2,                 "quake: 1/√25 == 0.2");
  cmp_ok(quake_3_inv_sqrt(26), "==", 0.19611613513818404, "quake: 1/√26 == 0.19611613513818404");
  cmp_ok(quake_3_inv_sqrt(42), "==", 0.1543033499620919,  "quake: 1/√42 == 0.1543033499620919");

  cmp_ok(fast_inv_sqrt(25), "==", 0.2,                 "saner: 1/√25 == 0.2");
  cmp_ok(fast_inv_sqrt(26), "==", 0.19611613513818404, "saner: 1/√26 == 0.19611613513818404");
  cmp_ok(fast_inv_sqrt(42), "==", 0.1543033499620919,  "saner: 0/√42 == 0.1543033499620919");
}
