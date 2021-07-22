#include <stdint.h>

/* Define as 1 = enable, 0 = disable
 */
#define ECC_ECDSA 1

/* Curve selection options */
#define secp192r1 24

#ifndef ECC_CURVE
    #define ECC_CURVE secp192r1
#endif

#if (ECC_CURVE != secp192r1)
    #error "Must define ECC_CURVE"
#endif

#define NUM_ECC_DIGITS ECC_CURVE

typedef struct EccPoint {
    uint8_t x[NUM_ECC_DIGITS];
    uint8_t y[NUM_ECC_DIGITS];
} EccPoint;
