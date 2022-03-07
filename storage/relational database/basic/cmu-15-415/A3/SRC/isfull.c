/* isfull.c */

#include "def.h"

extern long LISTSIZE[100];

int isfull(int count) {
    int i = 0;
    while (count >= LISTSIZE[i]) {
        if (LISTSIZE[i] == count)
            return (TRUE);
        i++;
    }
    return (FALSE);
}
