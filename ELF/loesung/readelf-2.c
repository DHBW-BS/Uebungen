#include <stdio.h>

#define FILENAME "hello"

int main(int argc, char **argv) {
    FILE *fd;
    unsigned char buffer[64];

    fd = fopen(FILENAME, "r");

    fread(buffer, 1, 64, fd);

    for (int i=0; i< 64; i++) {
        if (i%16 == 0) {
            printf("%08x  ", i);
        }
        printf("%02x", buffer[i]);
        if (i%16 == 15) {
            printf("\n");
        } else if (i%8 == 7) {
            printf("  ");
        } else {
            printf(" ");
        }
    }

    fclose(fd);

    return 0;
}