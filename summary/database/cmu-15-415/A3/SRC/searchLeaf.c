/*
    searches the leaf at the node stored at the page with number
        PageNo
    for the
        key.
    It returns the offset from the postings file, or NONEXISTENT,
      if not found
 */

#include "def.h"

POSTINGSPTR searchLeaf(struct PageHdr *PagePtr, char *key) {

    struct KeyRecord *KeyListTraverser;
    int InsertionPosition; /* Position for insertion */
    int FindInsertionPosition(struct KeyRecord * KeyListTraverser, char *Key,
                              int *Found, NUMKEYS NumKeys, int Count);
    int Count, Found, i;

    Count = 0;

    /* Find insertion position */
    KeyListTraverser = PagePtr->KeyListPtr;
    InsertionPosition = FindInsertionPosition(KeyListTraverser, key, &Found,
                                              PagePtr->NumKeys, Count);

    /* key is already in the B-Tree */
    if (Found == TRUE) {
        for (i = 0; i < InsertionPosition - 1; i++)
            KeyListTraverser = KeyListTraverser->Next;
        printf("found in %s\n", KeyListTraverser->StoredKey);
        return (KeyListTraverser->Posting);
    } else {
        return (NONEXISTENT);
    }
}
