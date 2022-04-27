/*getrec.c */

#include "def.h"

extern FILE *fppost;
extern int pWriteCount, pReadCount;
extern long LISTSIZE[100];

/* this function returns a file position pointer a free block equal to
   or greater than the passed size (size).  If there is a block of appropriate
   size in the freelist, it is removed and a pointer to it returned.  If not,
   a dummy block is set up at the end of the file and a pointer to it is
   returned.

   The file pointer cannot be assumed to be in the original position after
   executing this function  */

POSTINGSPTR getrec(long int size) {
    int i = 0, n = 0;
    POSTINGSPTR dummy, head, nextptr, save;
    rewind(fppost);

    /* find index of proper size freelist */
    while (LISTSIZE[i] < size)
        i++;
    /* appropriate size list is now of size LISTSIZE[i] */

    /* read through all freelist heads of smaller size blocks which
       precede the one of appropriate size */
    pReadCount++;
    for (n = 0; n < i; n++)
        fread(&dummy, sizeof(dummy), 1, fppost);

    /* record position of file pointer in case update of head is needed */
    save = ftell(fppost);
    /* read in head of freelist of appropriate size */
    fread(&head, sizeof(head), 1, fppost);

    /* check to see if freelist exists  */
    /* if not return pointer to end of file */
    if (head == -1) {
        /* set up a dummy record at the end of the file and return a pointer
           to it */
        NUMPTRS dummynum = 0;
        TEXTPTR dummyptr = 0;

        gotoeof(fppost);
        save = ftell(fppost);
        /* write out empty record to allocate space at end of file */
        pWriteCount++;
        fwrite(&dummynum, sizeof(dummynum), 1, fppost);
        for (n = 0; n < LISTSIZE[i]; n++)
            fwrite(&dummyptr, sizeof(dummyptr), 1, fppost);
        return (save);
    }

    /* read in pointer to next block in list */
    pReadCount++;
    fseek(fppost, (long) head, 0);
    fread(&nextptr, sizeof(nextptr), 1, fppost);

    /* write the next block in freelist as new head pointer */
    pWriteCount++;
    fseek(fppost, (long) save, 0);
    fwrite(&nextptr, sizeof(nextptr), 1, fppost);
    return (head);
}
