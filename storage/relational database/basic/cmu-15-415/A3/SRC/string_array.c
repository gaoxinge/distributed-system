#include "def.h"

#define WORD_LEN (30)

static int cmp(const void *a, const void *b) {
    return strcmp(*((char **) a), *((char **) b));
}

char **create_string_array(size_t n) {
    assert(n > 0);
    int i;
    char **retval = (char **) malloc(sizeof(char *) * n);
    assert(retval && "cannot malloc");
    for (i = 0; i < n; ++i) {
        retval[i] = (char *) malloc(sizeof(char) * WORD_LEN);
        assert(retval[i] && "cannot malloc");
    }
    return retval;
}

void sort_string_array(char **arr, size_t n) {
    qsort(arr, n, sizeof(char *), &cmp);
}

void free_string_array(char **arr, size_t n) {
    assert(n > 0);
    int i;
    for (i = 0; i < n; ++i) {
        free(arr[i]);
    }
    free(arr);
}
