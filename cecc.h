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

/*
  ecc_gen_keys()
  generate public/private key pair
  - use a new cryptographycaly secure random number

  - inputs:
      p_random - the random number to use to generate the keypair

  - outputs:
      p_pubkey - will be filled in with the point representing the public key.
      p_privkey - will be filled in with the private key.
 */
int ecc_gen_keys(EccPoint *p_pubkey, uint8_t p_privkey[NUM_ECC_DIGITS], uint8_t p_random[NUM_ECC_DIGITS]);

/*
  ecc_is_valid_pubkey
  determine whether or not a given point is on the chosen elliptic curve

  - inputs:
      p_pubkey - the poin to check.
 */
int ecc_is_valid_pubkey(EccPoint *p_pubkey);
