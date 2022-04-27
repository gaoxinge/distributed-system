/***************************************************************************
*                                                                          *
*   This function inserts a key into a leaf page, after a Posting has      *
*   been created.  In the case where a key is already stored in the        *
*   B-Tree, the Posting record is updated.                                 *
    If the page overflows, it
       splits it,
       flushes the two new pages and
       return the value of the middle key in a structure "upKey"
    Otherwise, it just flushes back the old page and returns NULL
*                                                                          *
***************************************************************************/

#include "def.h"

extern int UpdatePostingsFile(POSTINGSPTR *pPostOffset, TEXTPTR NewTextOffset);
extern int FreePage(struct PageHdr *PagePtr);
extern int FlushPage(struct PageHdr *PagePtr);
extern int CreatePosting(TEXTPTR TextOffset, POSTINGSPTR *pPostOffset);
extern int fillIn(struct PageHdr *PagePtr);

struct upKey *InsertKeyInLeaf(struct PageHdr *PagePtr, char *Key, TEXTPTR TextOffset, int *isNew) {
    struct KeyRecord *KeyListTraverser, /*                              */
        *KeyListTrailer,                /* Pointers to the list of keys */
        *NewKeyNode;

    int InsertionPosition, /* Position for insertion */
        Count, Found, i;
    POSTINGSPTR PostOffset;
    struct upKey *MiddleKey, *SplitPage(struct PageHdr * PagePtr);
    int FindInsertionPosition(struct KeyRecord * KeyListTraverser, char *Key,
                              int *Found, NUMKEYS NumKeys, int Count);
    char *strsave(char *s);

    Count = 0;

    /* Find insertion position */
    KeyListTraverser = PagePtr->KeyListPtr;
    InsertionPosition = FindInsertionPosition(KeyListTraverser, Key, &Found,
                                              PagePtr->NumKeys, Count);

    /* Key is already in the B-Tree */
    if (Found == TRUE) {
        POSTINGSPTR oldpointer;
        /* printf ("Key = %s\n", Key);
        printf ("  Text Offsets are:\n");  */
        for (i = 0; i < InsertionPosition - 1; i++)
            KeyListTraverser = KeyListTraverser->Next;
        /* change made here by Frank Andrasco
           since postings pointer may change, pointer must be passed by
           reference
           instead of by value  */

        oldpointer = KeyListTraverser->Posting;
        UpdatePostingsFile(&KeyListTraverser->Posting, TextOffset);

        /* check to see if posting value changed, if so rewrite to disk */
        if (KeyListTraverser->Posting == oldpointer)
            FreePage(PagePtr);
        else
            FlushPage(PagePtr);

        *isNew = FALSE;
        return (NULL);
    }

    /* Key must be inserted in B-Tree */
    CreatePosting(TextOffset, &PostOffset);
    /* Traverse the list of keys to insertion position */
    KeyListTraverser = PagePtr->KeyListPtr;
    for (i = 0; i < InsertionPosition; i++) {
        KeyListTrailer = KeyListTraverser;
        KeyListTraverser = KeyListTraverser->Next;
    }

    /* Create a new node for the new key and insert key informtion */
    NewKeyNode = (struct KeyRecord *) malloc(sizeof(*NewKeyNode));
    ck_malloc(NewKeyNode, "NewKeyNode");
    NewKeyNode->KeyLen = strlen(Key);
    NewKeyNode->StoredKey = strsave(Key);
    NewKeyNode->Posting = PostOffset;

    /* Insert new key in list */
    if (InsertionPosition == 0) {
        PagePtr->KeyListPtr = NewKeyNode;
    } else
        KeyListTrailer->Next = NewKeyNode;
    /* Link new key to keys that lexicographically follow it */
    NewKeyNode->Next = KeyListTraverser;

    /* Update page header information */
    fillIn(PagePtr);
    *isNew = TRUE;

    /* split page, if necessary, and flush */
    if (PagePtr->NumBytes <= PAGESIZE) {
        PagePtr->SubtreeKeyCount += 1;
        FlushPage(PagePtr);
        return (NULL);
    } else {
        MiddleKey = SplitPage(PagePtr);
        return (MiddleKey);
    }
}
