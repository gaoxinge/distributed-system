/* freerec.c */

#include "def.h"

extern FILE *fppost;
extern long LISTSIZE[100];
extern int pWriteCount, pReadCount; /* see stats.c */

/* this function adds the block at the passed postings pointer (pptr) to the
   freelist of the size (size).

   The file pointer cannot be assumed to be in the original position after
   executing this function.  */

void freerec(POSTINGSPTR pptr, long int size) {
    int i = 0, n = 0;
    POSTINGSPTR dummy, head, save;

    rewind(fppost);
    /* find index of proper freelist */
    while (LISTSIZE[i] < size)
        i++;
    /* appropriate size list is now of size LISTSIZE[i] */

    /* read through all freelist heads of smaller size to just before
       appropriate head */
    pReadCount++;
    for (n = 0; n < i; n++)
        fread(&dummy, sizeof(dummy), 1, fppost);

    /* record position of file pointer */
    save = ftell(fppost);

    /* read in old freelist head */
    fread(&head, sizeof(head), 1, fppost);
    /* move file pointer back one to write new head */
    pWriteCount++;
    fseek(fppost, (long) save, 0);
    /* write passed pointer (pptr) as head of freelist */
    fwrite(&pptr, sizeof(pptr), 1, fppost);

    /* now update next pointer of new block */
    pWriteCount++;
    fseek(fppost, (long) pptr, 0);
    fwrite(&head, sizeof(head), 1, fppost);
}
