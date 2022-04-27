
/*************************************************************************
*                                                                        *
*    This function inserts a key into a nonleaf page.  In the case       *
*    where the nonleaf page contains zero keys (the root), the first     *
*    key is inserted into the root and the only leaf page becomes        *
*    the rightmost child.                                                *
     It returns NULL, or a pointer to the key ("upKey") structure
     to be propagated upstairs.
*                                                                        *
*************************************************************************/

#include "def.h"

extern int FreePage(struct PageHdr *PagePtr);
extern int FlushPage(struct PageHdr *PagePtr);
extern int fillIn(struct PageHdr *PagePtr);

struct upKey *InsertKeyInNonLeaf(struct PageHdr *PagePtr, struct upKey *MiddleKey, int *isNew)
/* Key to be inserted in this non-leaf page */
{
    struct KeyRecord *KeyListTraverser, /*                              */
        *KeyListTrailer,                /* Pointers to the list of keys */
        *MiddleKeyCopy;                 /* KeyRecord structure, to contain */
    /* the MiddleKey */
    int Count, Found, InsertionPosition, i;
    int FindInsertionPosition(struct KeyRecord * KeyListTraverser, char *Key,
                              int *Found, NUMKEYS NumKeys, int Count);
    char *Word; /* Key stored in B-Tree */
    struct upKey *newUpKey, *SplitPage(struct PageHdr * PagePtr);
    char *strsave(char *s);

    if (MiddleKey == NULL) { /* just free the page-image */
        if (*isNew == TRUE) {
            PagePtr->SubtreeKeyCount += 1;
            FlushPage(PagePtr);
        } else {
            FreePage(PagePtr);
        }
        return (NULL);
    }

    /* build an appropriate KeyRecord node for the inserted key */
    MiddleKeyCopy = (struct KeyRecord *) malloc(sizeof(struct KeyRecord));
    MiddleKeyCopy->PgNum = MiddleKey->left;
    MiddleKeyCopy->KeyLen = strlen(MiddleKey->key);
    MiddleKeyCopy->StoredKey = strsave(MiddleKey->key);

    /* Root page currently has zero keys:  this key will be first insertion */
    /* NOTE: maybe this "if" block is redundant, if "FindInsertionPosition" */
    /*       works with a empty list!: -christos- */
    if (PagePtr->NumKeys == 0) {
        PagePtr->PtrToFinalRtgPg = MiddleKey->right;
        PagePtr->KeyListPtr = MiddleKeyCopy;
        MiddleKeyCopy->Next = NULL;
        if (*isNew == TRUE) {
            PagePtr->SubtreeKeyCount += 1;
        }
        FlushPage(PagePtr); /* it fills in the # of bytes & # of keys */
        return (NULL);
    }

    /* Find insertion position for key */
    /* -christos- : make it a procedure, say, inList() */
    Word = MiddleKeyCopy->StoredKey;
    Count = 0;
    KeyListTraverser = PagePtr->KeyListPtr;
    InsertionPosition = FindInsertionPosition(KeyListTraverser, Word, &Found,
                                              PagePtr->NumKeys, Count);

    /* Traverse list of keys to insertion postion */
    KeyListTraverser = PagePtr->KeyListPtr;
    for (i = 0; i < InsertionPosition; i++) {
        KeyListTrailer = KeyListTraverser;
        KeyListTraverser = KeyListTraverser->Next;
    }

    /* Insert the key */
    if (InsertionPosition == 0) /* This will be first key in list */
        PagePtr->KeyListPtr = MiddleKeyCopy;
    else
        KeyListTrailer->Next = MiddleKeyCopy;

    /* Link key to keys that lexicographically follow it */
    MiddleKeyCopy->Next = KeyListTraverser;

    /* Update the page header and, possibly, the pagepointer of the next key */
    if ((MiddleKeyCopy->Next) == NULL) { /* ie., it is last */
        PagePtr->PtrToFinalRtgPg = MiddleKey->right;
    } else {
        (MiddleKeyCopy->Next)->PgNum = MiddleKey->right;
    }
    fillIn(PagePtr); /* # bytes & # keys */

    free(MiddleKey->key);
    free((char *) MiddleKey);

    /* split, if it overflows, and flush */
    if (PagePtr->NumBytes <= PAGESIZE) {
        if (*isNew == TRUE) {
            PagePtr->SubtreeKeyCount += 1;
        }
        FlushPage(PagePtr);
        return (NULL);
    } else {
        newUpKey = SplitPage(PagePtr);
        return (newUpKey);
    }
}
