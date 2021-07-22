#include "../cecc.h"

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int randfd;

void vli_print(uint8_t *p_vli) {
    unsigned i;
    for (i = 0; i < NUM_ECC_DIGITS - 1; ++i) {
        printf("0x%02X, ", (unsigned)p_vli[i]);
    }
    printf("0x%02X", (unsigned)p_vli[i]);
}

void getRandomBytes(void *p_dest, unsigned p_size) {
    if (read(randfd, p_dest, p_size) != (int)p_size) {
        printf("Failed to get random bytes.\n");
    }
}

int main(int argc, char **argv) {
    unsigned l_num = 1;
    unsigned i;

    if (argc > 1) {
        l_num = strtoul(argv[1], NULL, 10);
    }

    randfd = open("/dev/urandom", O_RDONLY);
    if (randfd == -1) {
        printf("No access to urandom\n");
        return -1;
    }

    uint8_t l_private[NUM_ECC_DIGITS];

    for (i = 0; i < l_num; ++i) {
        printf("uint8_t private_%u[NUM_ECC_DIGITS] = {", i);
        vli_print(l_private);
        printf("};\n");
    }

    return 0;
}
