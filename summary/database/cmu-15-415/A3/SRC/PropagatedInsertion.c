/**********************************************************************
*                                                                     *
*     This recursive function traverses through the B-Tree on a       *
*     directed path (beginning at the root and traversing down to     *
*     the leaf page that contains, or should contain the new key.     *
*     As pages are split, the middle keys are propagated up to the    *
*     parent pages for insertion.  In the case where the root has     *
*     been split, the function returns the middle key which is to     *
*     be inserted in the new root, in the form of an "upKey" structure
      The function returns NULL otherwise.
*                                                                     *
*     Note that the variable NewKey points to a possible              *
*     propagated-up middle key and that key is sent to the function   *
*     InsertKey, which may, in turn, return a possible new            *
*     middle key which must be propagated-up to the parent page       *
*     for insertion.  In the abstract, NewKey travels down the        *
*     tree and MiddleKey travels upward.                              *
*                                                                     *
*     This function may be considered the core of the B-Tree          *
*     program.                                                        *
*                                                                     *
**********************************************************************/

#include "def.h"
struct upKey *PropagatedInsertion(PAGENO PageNo, char *Key, TEXTPTR TextOffset, int *isNew) {
    PAGENO ChildPage, FindPageNumOfChild(struct PageHdr * PagePtr,
                                         struct KeyRecord * KeyListTraverser,
                                         char *Key, NUMKEYS NumKeys);
    struct upKey *NewKey, *MiddleKey;

    struct upKey *InsertKeyInLeaf(struct PageHdr * PagePtr, char * Key, TEXTPTR TextOffset, int * isNew),
                 *InsertKeyInNonLeaf(struct PageHdr * PagePtr, struct upKey * MiddleKey, int * isNew);

    struct KeyRecord *KeyListTraverser; /* Pointer to list of keys */
    struct PageHdr *PagePtr;
    struct PageHdr *FetchPage(PAGENO Page);

    PagePtr = FetchPage(PageNo);

    if (IsLeaf(PagePtr)) {
        MiddleKey = InsertKeyInLeaf(PagePtr, Key, TextOffset, isNew);
    } else if (IsNonLeaf(PagePtr)) {
        KeyListTraverser = PagePtr->KeyListPtr;
        ChildPage = FindPageNumOfChild(PagePtr, KeyListTraverser, Key, PagePtr->NumKeys);
        NewKey = PropagatedInsertion(ChildPage, Key, TextOffset, isNew);
        MiddleKey = InsertKeyInNonLeaf(PagePtr, NewKey, isNew);
    } else { /* impossible */
        printf("Prop-Insertion: Illegal PageType:%c", PagePtr->PgTypeID);
        printf("in page# %d - aborting\n", (int) PagePtr->PgNum);
        exit(-2);
    }

    return (MiddleKey);
}
