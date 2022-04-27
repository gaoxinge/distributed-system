/*********************************************************************
*                                                                    *
*    This recursive function searches a nonleaf page to find the     *
*    page number (child page) where the key should be stored.  The   *
*    new key is compared with the keys within the B-Tree page.  If   *
*    the new key is lexicograhically less than or equal to a stored  *
*    key, the page number of the child page is returned.  If all     *
*    keys within the page have been searched and the new key is      *
*    lexicographically more than the last key, the page number of    *
*    the rightmost child is returned.                                *
*                                                                    *
*********************************************************************/

#include "def.h"

PAGENO FindPageNumOfChild(struct PageHdr *PagePtr,
                          struct KeyRecord *KeyListTraverser, char *Key,
                          NUMKEYS NumKeys)

/* A pointer to the list of keys */

/* Possible new key */
{
    /* Auxiliary Definitions */
    int Result;
    char *Word; /* Key stored in B-Tree */
    int CompareKeys(char *Key, char *Word);

    /* Compare the possible new key with key stored in B-Tree */
    Word = KeyListTraverser->StoredKey;
    (*(Word + KeyListTraverser->KeyLen)) = '\0';
    Result = CompareKeys(Key, Word);

    NumKeys = NumKeys - 1;

    if (NumKeys > 0) {
        if (Result == 2) { /* New key > stored key:  keep searching */
            KeyListTraverser = KeyListTraverser->Next;
            return (
                FindPageNumOfChild(PagePtr, KeyListTraverser, Key, NumKeys));
        } else                                /* New key <= stored key */
            return (KeyListTraverser->PgNum); /* return left child */
    } else /* This is the last key in this page */
    {
        if ((Result == 1) || (Result == 0))    /* New key <= stored key */
            return (KeyListTraverser->PgNum);  /* return left child */
        else                                   /* New key > stored key */
            return (PagePtr->PtrToFinalRtgPg); /* return rightmost child */
    }
}
