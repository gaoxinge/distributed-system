#include "def.h"

extern PAGENO treesearch_page(PAGENO PageNo, char *key);
extern POSTINGSPTR treesearch(PAGENO PageNo, char *key);
extern int FindInsertionPosition(struct KeyRecord *KeyListTraverser, char *Key,
				 int *Found, NUMKEYS NumKeys, int Count);
extern PAGENO FindPageNumOfChild(struct PageHdr *PagePtr,
                                 struct KeyRecord *KeyListTraverser, char *Key,
                                 NUMKEYS NumKeys);
extern struct PageHdr *FetchPage(PAGENO Page);
extern int FreePage(struct PageHdr *PagePtr);
extern int strtolow(char *s);
extern int CompareKeys(char *Key, char *Word);
extern NUMKEYS subtreeKeyCount(PAGENO pgNum);

NUMKEYS countKeyInLeftRange(PAGENO PageNo, char *key, int inRange) {
    struct PageHdr *PagePtr = FetchPage(PageNo);

    if (IsLeaf(PagePtr)) {
        NUMKEYS TotalCount = PagePtr->NumKeys;
        int Found;
        NUMKEYS Count = FindInsertionPosition(PagePtr->KeyListPtr, key, &Found, TotalCount, 0);

        NUMKEYS result = TotalCount - Count;
        if (Found == TRUE && inRange == TRUE) {
            result += 1;
        }

        FreePage(PagePtr);
        return result;
    }

    PAGENO ChildPage = FindPageNumOfChild(PagePtr, PagePtr->KeyListPtr, key, PagePtr->NumKeys);
    if (PagePtr->PtrToFinalRtgPg == ChildPage) {
        NUMKEYS result = countKeyInLeftRange(ChildPage, key, inRange);
        FreePage(PagePtr);
        return result;
    }

    NUMKEYS result = countKeyInLeftRange(ChildPage, key, inRange) + subtreeKeyCount(PagePtr->PtrToFinalRtgPg);
    int flag = FALSE;
    for (struct KeyRecord *p = PagePtr->KeyListPtr; p != NULL; p = p->Next) {
        if (flag == TRUE) {
            result += subtreeKeyCount(p->PgNum);
        }
        if (p->PgNum == ChildPage) {
            flag = TRUE;
        }
    }
    FreePage(PagePtr);
    return result;
}

NUMKEYS countKeyInRange(char *leftKey, char *rightKey) {
    if (CompareKeys(leftKey, rightKey) == 0) {
        return treesearch(ROOT, leftKey) == NONEXISTENT ? 0 : 1;
    }

    if (CompareKeys(leftKey, rightKey) == 1) {
        return countKeyInLeftRange(ROOT, leftKey, TRUE) - countKeyInLeftRange(ROOT, rightKey, FALSE);
    }

    return 0;
}
