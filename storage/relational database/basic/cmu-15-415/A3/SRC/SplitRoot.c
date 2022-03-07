/************************************************************************
*                                                                       *
*    Prior to execution of this function, the Root has already been     *
*    split by the function SplitPage().  The current Root contains      *
*    the left half of the Root that was split.  This function creates   *
*    a new root (still located as the first page on disk) and installs  *
*    the key that has propagated up to the Root.  The current root is   *
*    installed as the left child of the new Root.                       *
*                                                                       *
************************************************************************/

#include "def.h"

extern void FlushPage(struct PageHdr *PagePtr);
extern NUMKEYS subtreeKeyCountByPage(struct PageHdr *PagePtr);
extern NUMKEYS subtreeKeyCount(PAGENO pgNum);

/* upKeyPtr: Key to be inserted */
void SplitRoot(PAGENO RootPageNum, struct upKey *upKeyPtr) {
    struct PageHdr *PagePtr, /* Pointer to page (Root) being split */
        *NewPagePtr;         /* Pointer to newly created page */
    struct PageHdr *FetchPage(PAGENO Page);
    struct KeyRecord *middleKey; /* holds the node for the key  */
    /* that will be the only key of the new root */
    char *strsave(char *s);
    PAGENO getNewPageNum(void);

    /* allocate space for the *middlekey node  and fill it in */
    middleKey = (struct KeyRecord *) malloc(sizeof(struct KeyRecord));
    ck_malloc(middleKey, "middleKey");
    middleKey->StoredKey = strsave(upKeyPtr->key);
    middleKey->KeyLen = strlen(middleKey->StoredKey);
    middleKey->Next = NULL;

    /* read in root */
    PagePtr = FetchPage(ROOT);

    /* Create the core-image of the new root page  */
    NewPagePtr = (struct PageHdr *) malloc(sizeof(*NewPagePtr));
    ck_malloc(NewPagePtr, "NewPagePtr");
    NewPagePtr->PgTypeID = NonLeafSymbol;
    NewPagePtr->PgNum = ROOT;
    NewPagePtr->PtrToFinalRtgPg = upKeyPtr->right;
    /* points to the second half of old root */

    /* Record the page pointers */
    PagePtr->PgNum = getNewPageNum();
    /* the left part of the old root will be flushed */
    /* at a new position */

    middleKey->PgNum = PagePtr->PgNum;

    /* Install the middle key into the new root */
    NewPagePtr->KeyListPtr = middleKey;

    /* Update SubtreeKeyCount */
    NewPagePtr->SubtreeKeyCount = subtreeKeyCountByPage(PagePtr) + subtreeKeyCount(NewPagePtr->PtrToFinalRtgPg);

    /* - christos -: free the space of the upKey - DONE! */
    free((char *) (upKeyPtr->key));
    free((char *) upKeyPtr);

    FlushPage(NewPagePtr);
    FlushPage(PagePtr);
}
