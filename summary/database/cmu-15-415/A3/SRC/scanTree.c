/*
     Scans all the entries of the B-tree, applying
     the function "f" for each entry
 */

#include "def.h"

extern FILE *fpbtree;

typedef void (*RecordVisitor)(struct KeyRecord *);

extern int FreePage(struct PageHdr *PagePtr);
extern void scanLeaf(struct PageHdr *p, RecordVisitor f);

void scanTree(RecordVisitor f) {
    struct PageHdr *FetchPage(PAGENO Page), *p, *tempp;

    p = FetchPage(ROOT);

    while (IsNonLeaf(p)) { /* follow leftmost ptr */
        tempp = p;
        p = FetchPage((tempp->KeyListPtr)->PgNum);
        FreePage(tempp);
    }

    /* now "p" should point to the alphabetically first page */
    scanLeaf(p, f);
    while ((p->PgNumOfNxtLfPg) != NULLPAGENO) { /* get next valid page */
        tempp = p;
        p = FetchPage(tempp->PgNumOfNxtLfPg);
        FreePage(tempp);
        scanLeaf(p, f); /* and process it */
    }
}
