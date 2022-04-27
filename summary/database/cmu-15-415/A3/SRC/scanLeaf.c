/*
    Applies function "f" to every key in page "p"
 */
#include "def.h"

typedef void (*RecordVisitor)(struct KeyRecord *);

void scanLeaf(struct PageHdr *p, RecordVisitor f) {
    struct KeyRecord *keyptr;

    /* traverse all keys in this page */
    keyptr = p->KeyListPtr;
    while (keyptr != NULL) {
        f(keyptr);
        keyptr = keyptr->Next;
    }
}
