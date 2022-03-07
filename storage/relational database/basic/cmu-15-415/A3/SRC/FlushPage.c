
/*************************************************************************
*                                                                        *
*    This function writes a page to disk and then calls function         *
*    FreePage to free the storage space that was allocated to the       *
*    dynamic data structures.                                            *
*                                                                        *
*    The size of the page, PAGESIZE, is locked-in when the page is       *
*    written to disk.  This is handled by the padding of character       *
*    zero's, e.g., if PAGESIZE = x and the number of bytes that are      *
*    stored in the page is NumBytes = n, there will be (x - n)           *
*    character byte zero's written to disk.                              *
*                                                                        *
*************************************************************************/

#include "def.h"
extern FILE *fpbtree;
extern int btWriteCount; /* counts the number of b-tree page writes */

extern int fillIn(struct PageHdr *PagePtr);
extern void FreePage(struct PageHdr *PagePtr);

void FlushPage(struct PageHdr *PagePtr) {
    struct KeyRecord *KeyListTraverser; /* A pointer to the list of keys */
    int i;
    char Ch;

    fillIn(PagePtr); /* calculates the # of bytes and # of keys */
    if (PagePtr->NumBytes > PAGESIZE) {
        printf("FlushPage: page %d too big: %d bytes\n", (int) PagePtr->PgNum,
               (int) PagePtr->NumBytes);
        printf("execution aborted\n");
        exit(-2);
    }

    fseek(fpbtree, (long) (PagePtr->PgNum) * PAGESIZE - PAGESIZE, 0);
#ifdef DEBUG

    printf("FlushPage starting: ftell()=%ld for page # %d\n", ftell(fpbtree),
           (int) (PagePtr->PgNum));
#endif

    /* Write the page header to disk */
    fwrite(&PagePtr->PgTypeID, sizeof(PagePtr->PgTypeID), 1, fpbtree);
    fwrite(&PagePtr->PgNum, sizeof(PagePtr->PgNum), 1, fpbtree);
    if (IsLeaf(PagePtr))
        fwrite(&PagePtr->PgNumOfNxtLfPg, sizeof(PagePtr->PgNumOfNxtLfPg), 1,
               fpbtree);
    fwrite(&PagePtr->NumBytes, sizeof(PagePtr->NumBytes), 1, fpbtree);
    fwrite(&PagePtr->NumKeys, sizeof(PagePtr->NumKeys), 1, fpbtree);
    fwrite(&PagePtr->SubtreeKeyCount, sizeof(PagePtr->SubtreeKeyCount), 1, fpbtree);
    if (IsNonLeaf(PagePtr))
        fwrite(&PagePtr->PtrToFinalRtgPg, sizeof(PagePtr->PtrToFinalRtgPg), 1,
               fpbtree);

    /* Write the keys to disk */
    for (KeyListTraverser = PagePtr->KeyListPtr; KeyListTraverser != NULL;
         KeyListTraverser = KeyListTraverser->Next) {
        if (IsNonLeaf(PagePtr))
            fwrite(&KeyListTraverser->PgNum, sizeof(KeyListTraverser->PgNum), 1,
                   fpbtree);
        fwrite(&KeyListTraverser->KeyLen, sizeof(KeyListTraverser->KeyLen), 1,
               fpbtree);
        fwrite(KeyListTraverser->StoredKey, sizeof(char),
               KeyListTraverser->KeyLen, fpbtree);
        if (IsLeaf(PagePtr))
            fwrite(&KeyListTraverser->Posting,
                   sizeof(KeyListTraverser->Posting), 1, fpbtree);
    }

    /* Lock-in full page size */
    Ch = '0';
    for (i = PagePtr->NumBytes; i < PAGESIZE; i++)
        fwrite(&Ch, sizeof(Ch), 1, fpbtree);

#ifdef DEBUG

    printf("FlushPage ending: ftell()=%ld for page # %d\n", ftell(fpbtree),
           (int) (PagePtr->PgNum));
#endif

    fflush(fpbtree); /* make sure the page is written back */

    /* Free core storage allocated for page header and keys */
    FreePage(PagePtr);

    btWriteCount++;
}
