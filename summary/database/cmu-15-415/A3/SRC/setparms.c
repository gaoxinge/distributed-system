#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int PAGESIZE;
int MAXTEXTPTRS;
double GF;

extern long LISTSIZE[100];

void setparms(void) {
    FILE *fp;
    double gf; /* growth factor */
    int i;

    fp = fopen("parms", "r");
    if (fp == NULL) {
        printf("file parms not found\n");
        exit(-1);
    }

    fscanf(fp, "%d %lf", &PAGESIZE, &gf);
    fclose(fp);
    MAXTEXTPTRS = 1; /* to be deleted?*/
    GF = gf;
    assert(gf >= 1.5);
    for (i = 0; i < 100; i++) {
        LISTSIZE[i] = (long) ceil(pow(gf, (double) i));
#ifdef DEBUG

        printf("ls[%d]=%ld\n", i, LISTSIZE[i]);
#endif
    }
}
