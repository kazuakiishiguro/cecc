#include "./cecc.h"

typedef unsigned int uint;


static void EccPoint_mult(EccPoint *p_result, EccPoint *p_point, uint8_t *p_scalar, uint8_t *p_initialZ);
static int EccPoint_isZero(EccPoint *EccPoint);

/* Sets p_dest = p_src. */
static void vli_set(uint8_t *p_dest, uint8_t *p_src) {
    uint i;
    for (i = 0; i < NUM_ECC_DIGITS; ++i) {
        p_dest[i] = p_src[i];
    }
}

int ecdh_shared_secret(uint8_t p_secret[NUM_ECC_DIGITS], EccPoint *p_pubkey, uint8_t p_privkey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]) {
    EccPoint l_product;
    EccPoint_mult(&l_product, p_pubkey, p_privkey, p_random);
    if (EccPoint_isZero(&l_product)) {
        return 0;
    }

    vli_set(p_secret, l_product.x);

    return 1;
}
