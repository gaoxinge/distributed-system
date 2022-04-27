/* returns the size of a file, in bytes */

#include <stdio.h>

long ffsize(FILE *fp) {
    long pos; /* current position, to return to */
    long sz;

    pos = ftell(fp);
    fseek(fp, (long) 0, 2);
    sz = ftell(fp);
    fseek(fp, (long) pos, 0);
    return (sz);
}
