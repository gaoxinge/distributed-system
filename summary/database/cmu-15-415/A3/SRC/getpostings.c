/*  getposting.c */

/* Modified by Frank Andrasco

****************************************************************************
This function retrieves all the textfile pointers from the postings file
starting at the postingsfile offset passed in pptr.  This routine always
requires only one disk read, since all postings pointers are stored
contiguously.

****************************************************************************/

#include "def.h"
extern FILE *fppost;
extern FILE *fptext; /* to be deleted, -christos- */

extern int pReadCount;

extern void pr_msg(long int start, FILE *fp);

void getpostings(POSTINGSPTR pptr) {

    NUMPTRS NumTextOffsets;
    TEXTPTR TextOffset;
    int i;
    int docCount; /* counter, for the qualifying documents */

    docCount = 0;
    pReadCount++; /* counts disk reads */
    fseek(fppost, (long) pptr, 0);
    fread(&NumTextOffsets, sizeof(NumTextOffsets), 1, fppost);

    for (i = 0; i < NumTextOffsets; i++) {
        fread(&TextOffset, sizeof(TextOffset), 1, fppost);
        /* printf (" %d", TextOffset); */
        printf("-------document #%d-----\n", ++docCount);
        pr_msg(TextOffset, fptext);
    }

    printf("\n");
}
