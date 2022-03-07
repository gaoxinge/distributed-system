/* UpdatePostingsFile.c */
/*  The function UpdatePostingsFile is passed two values:
    a pointer to an offset in the postings file, and a offset value
    referring to the textfile.  The routines get the record at the
    postings file offset and checks to see if there is enough space for
    another text offset.  If there is empty offset space available in the
    same record, the number of text offsets in the record is incremented
    and re-written to the record and the new text offset is added to the end
    of the record.

    If the current postings list is full, all the pointers are read into
    memory, and the current record is added to a freelist of that size
    record.  A freelist of every size record is kept by keeping the head
    pointers in the first record of the file.

    A new free record of the next largest size, if available, is retrieved
    from the appropriate head pointer at the beginning of the file.  If there
    is no block of the appropriate size, the new record is set up at the
    end of the file.
*/

#include <stdio.h>
#include "def.h"

extern int pWriteCount, pReadCount;
extern FILE *fppost;

extern int isfull(int count);
extern void freerec(POSTINGSPTR pptr, long int size);
extern POSTINGSPTR getrec(long int size);

void UpdatePostingsFile(POSTINGSPTR *pPostOffset, TEXTPTR NewTextOffset) {
    TEXTPTR TextOffset;
    NUMPTRS NumTextOffsets;

    /* goto postings offset */
    fseek(fppost, (long) *pPostOffset, 0);
    /* read in the number of postings pointers */
    fread(&NumTextOffsets, sizeof(NumTextOffsets), 1, fppost);

    /* check if there is space available for another pointer */
    if (!isfull(NumTextOffsets)) {
        /* update number of pointers */
        NumTextOffsets++;
        fseek(fppost, (long) *pPostOffset, 0);
        pWriteCount++;

        fwrite(&NumTextOffsets, sizeof(NumTextOffsets), 1, fppost);
        /* read past all old text pointers */
        fseek(fppost, (long) sizeof(NewTextOffset) * (NumTextOffsets - 1), 1);
        /* write new text pointer */
        fwrite(&NewTextOffset, sizeof(NewTextOffset), 1, fppost);
    } else /* we need to create a new postings record and free old */
    {
        TEXTPTR *TPtrList;
        /* get space to hold list of text pointers */
        TPtrList = (TEXTPTR *) malloc(sizeof(TEXTPTR) * NumTextOffsets);
        ck_malloc(TPtrList, "Textpointer List");
        pReadCount++;
        /* save position in record */
        ftell(fppost);
        /* read in list of text pointers */
        fread(TPtrList, sizeof(TextOffset), NumTextOffsets, fppost);

        /* add the current text pointer record to one of the free lists */
        freerec(*pPostOffset, NumTextOffsets);

        /* get new block of next larger size */
        NumTextOffsets++;
        *pPostOffset = getrec(NumTextOffsets);

        /* goto the new block on the disk */
        pWriteCount++;
        fseek(fppost, (long) *pPostOffset, 0);

        /* write new list of pointers */
        fwrite(&NumTextOffsets, sizeof(NumTextOffsets), 1, fppost);
        fwrite(TPtrList, sizeof(TextOffset), NumTextOffsets - 1, fppost);
        fwrite(&NewTextOffset, sizeof(TextOffset), 1, fppost);
    }
}
