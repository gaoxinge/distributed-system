#include "def.h"

extern FILE *fppost;
extern long LISTSIZE[100];
extern double GF;

/* this function scans the free lists and prints
   the number of free records for each  record-size.
 */

int getcount(int i);

void postStats(void) {
    int i = 0, n = 0;
    int totempty;

    rewind(fppost);
    totempty = 0;
    for (i = 0; i < 20; i++) {
        printf("size:%ld ", LISTSIZE[i]);
        n = getcount(i);
        printf(" count:%d\n", n);
        totempty += LISTSIZE[i] * n;
    }
    printf("ExtFragm: %d empty slots, 4(?) bytes each\n", totempty);
    printf("growth factor:%g\n", GF);
}

int getcount(int i) {
    int n = 0;
    POSTINGSPTR nextptr;

    fseek(fppost, (long) i * sizeof(POSTINGSPTR), 0);
    fread(&nextptr, sizeof(nextptr), 1, fppost);
    while (nextptr != (-1)) {
        n++;
        fseek(fppost, (long) nextptr, 0);
        fread(&nextptr, sizeof(nextptr), 1, fppost);
    }
    return (n);
}
