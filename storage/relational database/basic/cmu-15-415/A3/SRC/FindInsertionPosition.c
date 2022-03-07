/**********************************************************************
*                                                                     *
*    This recursive function searches a list of keys to find the      *
*    position where the new key should be inserted.  The new key is   *
*    compared with the keys stored in the B-Tree until (1) a match is *
*    found, (2) the new key is lexicographically less than the stored *
*    key, (3) the last stored key is encountered and conditions (1)   *
*    or (2) have not been met.  The function returns, for the above   *
*    cases:  Case (1) -- the position of the matched key, Case (2) -- *
*    the position immediately preceding the current key being         *
*    compared, or Case (3) -- the position of the last key.           *
*                                                                     *
*    Note that the variable Count starts out with value zero and      *
*    increments with each recursive call.                             *
*                                                                     *
*    The variable KeyListTraverser is a pointer that traverses        *
*    the list of keys.                                                *
*                                                                     *
**********************************************************************/

#include "def.h"

/* KeyListTraverser: Pointer to the list of keys */
/* Key: The new possible key */
/* Found: report result */
int FindInsertionPosition(struct KeyRecord *KeyListTraverser, char *Key,
                          int *Found, NUMKEYS NumKeys, int Count) {
    int Result;
    int CompareKeys(char *Key, char *Word);

    /* -christos- the next block probably provides for
    insertion in empty list (useful for insertion in root
    for the first time! */

    if (NumKeys == 0) {
        *Found = FALSE;
        return (Count);
    }

    /* Compare the the possible new key with the key stored in B-Tree */
    Result = CompareKeys(Key, KeyListTraverser->StoredKey);

    NumKeys = NumKeys - 1;
    Count = Count + 1;

    if (Result == 0) /* Match found */
    {
        *Found = TRUE;
        return (Count); /* Location of matched key */
    } else              /* No match yet */
        *Found = FALSE;

    if (NumKeys > 0) {
        if (Result == 1)        /* New key < stored key */
            return (Count - 1); /* Location before stored key */
        else                    /* New key > stored key: keep searching */
        {
            KeyListTraverser = KeyListTraverser->Next;
            return (FindInsertionPosition(KeyListTraverser, Key, Found, NumKeys,
                                          Count));
        }
    } else /* this is the last key in the list -- search must terminate */
    {
        if (Result == 1)        /* New key < stored key */
            return (Count - 1); /* Location before stored key */
        else
            return (Count); /* New key will be the last key */
    }
}
