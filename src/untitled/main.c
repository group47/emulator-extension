#include <stdio.h>
#include <stdlib.h>

int main() {
    char** dummy = NULL;
    printf("%ld\n", strtol("-232", dummy, 10));
    return 0;
}