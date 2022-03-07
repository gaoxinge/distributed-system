#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* allocates enough space and copies the
   string 's', returning the pointer to the copy
 */
char *strsave(char *s) {
    char *new;

    new = malloc(strlen(s) + 1);
    strcpy(new, s);
    return (new);
}
