
/********************************************************************
*                                                                   *
*    This function creates and writes to disk the original root     *
*    of the newly created B-Tree.  Initially, the root will         *
*    contain zero keys and no rightmost child.                      *
*                                                                   *
*                                                                   *
********************************************************************/

#include "def.h"

extern FILE *fpbtree;

extern void FlushPage(struct PageHdr *PagePtr);

void CreateRoot(void) {
    struct PageHdr *PagePtr;

    /* Install the header of new page */
    PagePtr = (struct PageHdr *) malloc(sizeof(struct PageHdr));
    ck_malloc(PagePtr, "PagePtr");
    PagePtr->PgTypeID = LeafSymbol;
    PagePtr->PgNum = ROOT;
    PagePtr->PgNumOfNxtLfPg = NULLPAGENO;
    PagePtr->KeyListPtr = NULL; /* no keys yet */

    FlushPage(PagePtr); /* fills in #bytes & #keys */
}
