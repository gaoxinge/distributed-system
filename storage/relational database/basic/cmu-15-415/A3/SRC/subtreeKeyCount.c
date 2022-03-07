#include "def.h"

extern struct PageHdr *FetchPage(PAGENO Page);
extern int FreePage(struct PageHdr *PagePtr);

NUMKEYS subtreeKeyCountByPage(struct PageHdr *PagePtr) {
    return PagePtr->SubtreeKeyCount;
}

NUMKEYS subtreeKeyCount(PAGENO pgNum) {
    struct PageHdr *PagePtr = FetchPage(pgNum);
    NUMKEYS result = subtreeKeyCountByPage(PagePtr);
    FreePage(PagePtr);
    return result;
}

NUMKEYS subtreeKeyCountFromChildByPage(struct PageHdr *PagePtr) {
    if (IsLeaf(PagePtr)) {
        NUMKEYS result = 0;
        for (struct KeyRecord *p = PagePtr->KeyListPtr; p != NULL; p = p->Next) {
            result++;
        }
        return result;
    }

    NUMKEYS result = 0;
    for (struct KeyRecord *p = PagePtr->KeyListPtr; p != NULL; p = p->Next) {
        result += subtreeKeyCount(p->PgNum);
    }
    result += subtreeKeyCount(PagePtr->PtrToFinalRtgPg);
    return result;
}

NUMKEYS subtreeKeyCountFromChild(PAGENO pgNum) {
    struct PageHdr *PagePtr = FetchPage(pgNum);
    NUMKEYS result = subtreeKeyCountFromChildByPage(PagePtr);
    FreePage(PagePtr);
    return result;
}
