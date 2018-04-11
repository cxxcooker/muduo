/**
 * 
 */

#include <stdio.h>

int main(int argc, char **argv) {
    printf("executable filename: %s\n", argv[0]);
    printf("from source file: %s\n", __FILE__);
    printf("compiled at datetime: %s %s\n", __DATE__, __TIME__);

    return 0;
}