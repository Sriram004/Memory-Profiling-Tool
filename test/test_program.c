#include <stdlib.h>
#include <string.h>

int main() {
    char *a = malloc(100);
    char *b = calloc(10, 20);
    a = realloc(a, 200);
    free(b);
    // Forgot to free 'a' to test leak
    return 0;
}
