#include "./cecc.h"

typedef unsigned int uint;

static void vli_clear(uint8_t *p_vli) {
    uint i;
    for (i = 0; i < NUM_ECC_DIGITS; ++i) {
        p_vli[i] = 0;
    }
}

/* Sets p_dest = p_src. */
static void vli_set(uint8_t *p_dest, uint8_t *p_src) {
    uint i;
    for (i = 0; i < NUM_ECC_DIGITS; ++i) {
        p_dest[i] = p_src[i];
    }
}

/* TODO */
/* Double in place */
static void EccPoint_double_jacobian(uint8_t *X1, uint8_t *Y1, uint8_t *Z1) {
    /* t1 = X, t2 = Y, t3 = Z */
}

/* Modify (x1, y1) => (x1 & z^2, y1 * z*3) */
static void apply_z(uint8_t *X1, uint8_t *Y1, uint8_t *Z) {
    uint8_t t1[NUM_ECC_DIGITS];

    /* TODO */
}

/* P = (x1, y1) => 2P, (x2, y2) => P' */
static void XYcZ_initial_double(uint8_t *X1, uint8_t *Y1, uint8_t *X2, uint8_t *Y2, uint8_t *p_initialZ) {
    uint8_t z[NUM_ECC_DIGITS];

    vli_set(X2, X1);
    vli_set(Y2, Y1);

    vli_clear(z);
    z[0] = 1;
    if (p_initialZ) {
        vli_set(z, p_initialZ);
    }
    apply_z(X1, Y1, z);
    EccPoint_double_jacobian(X1, Y1, z);

    apply_z(X2, Y2, z);
}

static void EccPoint_mult(EccPoint *p_result, EccPoint *p_point, uint8_t *p_scalar, uint8_t *p_initialZ) {
    /* R0 and R1 */
    uint8_t Rx[2][NUM_ECC_DIGITS];
    uint8_t Ry[2][NUM_ECC_DIGITS];
    uint8_t z[NUM_ECC_DIGITS];

    uint i, nb;

    vli_set(Rx[1], p_point->x);
    vli_set(Ry[1], p_point->y);

    XYcZ_initial_double(Rx[1], Ry[1], Rx[0], Ry[0], p_initialZ);

    vli_set(p_result->x, Rx[0]);
    vli_set(p_result->y, Ry[0]);
}

static int EccPoint_isZero(EccPoint *EccPoint);


int ecdh_shared_secret(uint8_t p_secret[NUM_ECC_DIGITS], EccPoint *p_pubkey, uint8_t p_privkey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]) {
    EccPoint l_product;
    EccPoint_mult(&l_product, p_pubkey, p_privkey, p_random);
    if (EccPoint_isZero(&l_product)) {
        return 0;
    }

    vli_set(p_secret, l_product.x);

    return 1;
}
