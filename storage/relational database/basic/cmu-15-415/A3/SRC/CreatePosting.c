/* CreatePosting.c */

#include "def.h"

extern FILE *fppost;
extern int pWriteCount;

extern POSTINGSPTR getrec(long int size);

void CreatePosting(TEXTPTR TextOffset, POSTINGSPTR *pPostOffset) {
    NUMPTRS NumPtrs;
    TEXTPTR SpaceFiller;
    int i;

    NumPtrs = 1;
    SpaceFiller = 0;

    /* get a posting block of minimum size */
    *pPostOffset = getrec(1);

    /* Write the new posting to disk */
    pWriteCount++; /* counts number of disk writes */
    fseek(fppost, (long) *pPostOffset, 0);
    fwrite(&NumPtrs, sizeof(NumPtrs), 1, fppost);
    fwrite(&TextOffset, sizeof(TextOffset), 1, fppost);

    /* fill in any extra space with filler */
    /* this should not be executed if first listsize is 1 */
    for (i = NumPtrs; i < MAXTEXTPTRS; i++)
        fwrite(&SpaceFiller, sizeof(SpaceFiller), 1, fppost);
}
