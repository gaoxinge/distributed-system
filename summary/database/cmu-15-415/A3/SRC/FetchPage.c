/****************************************************************************
*                                                                           *
*     The function FetchPage reads a page from disk using the formula       *
*     PageNum * PAGESIZE - PAGESIZE, e.g., if the PageNum = 3 and           *
*     PAGESIZE = 1024, the B-Tree file will be accessed starting at         *
*     offset 2048, wherein the first page would be stored at offset 0,      *
*     and the second page at offset 1024.                                   *
*                                                                           *
*     FetchPage installs the page in the following structures:              *
*                                                                           *
*     The dynamically allocated page header structure:                      *
*                                                                           *
*         struct PageHdr {                                                  *
*            char            PgTypeID;        (To differentiate between     *
*                                               Leaf or NonLeaf pages)      *
*            PAGENO         PgNum;           (Page number within the       *
*                                               B-Tree)                     *
*            PAGENO         PgNumOfNxtLfPg;  (Page number of next logical  *
*                                               leaf page (LEAF PAGES ONLY))*
*            NUMBYES         NumBytes;        (Number of bytes stored       *
*                                               within page)                *
*            NUMKEYS         NumKeys;         (Number of keys stored        *
*                                               within page)                *
*            struct KeyRecord *KeyListPtr;    (Pointer to the list of keys  *
*                                               and their relative data)    *
*            PAGENO         PtrToFinalRtgPg; (Page number of righmost      *
*                                               child (NONLEAF PAGES ONLY)) *
*         }                                                                 *
*                                                                           *
*     The dynamically allocated key structure:                              *
*                                                                           *
*         struct KeyRecord {                                                *
*            PAGENO         PgNum;           (Page number of child page    *
*                                               containing keys lexico-     *
*                                               graphically less than       *
*                                               stored key (NONLEAF PAGES   *
*                                               ONLY))                      *
*            KEYLEN          KeyLen;          (The length (in bytes) of     *
*                                               the stored key)             *
*            KEYLEN bytes   *StoredKey;       (A pointer to the dynamically *
*                                               allocated storage for the   *
*                                               key containing up to        *
*                                               MAXWORDSIZE characters)     *
*            POSTINGSPTR     Posting;         (Offset of Postings record    *
*                                               (LEAF PAGES ONLY))          *
*            struct KeyRecord *Next;          (Pointer to the next logical  *
*                                               KeyRecord structure)        *
*         }                                                                 *
*                                                                           *
*                                                                           *
****************************************************************************/

#include "def.h"

extern FILE *fpbtree;
extern int btReadCount; /* counts the number of b-tree page reads */

struct PageHdr *FetchPage(PAGENO Page)
/* Page number of page to be fetched */
{
    struct PageHdr *PagePtr;
    struct KeyRecord *KeyNode,
        *KeyListTraverser; /* To traverse the list of keys */

    int i;
    PAGENO FindNumPagesInTree(void);

    /* check validity of "Page" */
    if ((Page < 1) || (Page > FindNumPagesInTree())) {
        printf("FetchPage: Pagenum %d out of range (%d,%d)\n", (int) Page,
               (int) ROOT, (int) FindNumPagesInTree());
        /*	exit(-1); */
    }

    /* Read in the page header */
    PagePtr = (struct PageHdr *) malloc(sizeof(*PagePtr));
    ck_malloc(PagePtr, "PagePtr");
    fseek(fpbtree, (long) Page * PAGESIZE - PAGESIZE, 0);

    fread(&PagePtr->PgTypeID, sizeof(char), 1, fpbtree);
    fread(&PagePtr->PgNum, sizeof(PagePtr->PgNum), 1, fpbtree);
    if ((PagePtr->PgNum) != Page) {
        printf("FetchPage: corrupted Page %d\n", (int) Page);
        exit(-1);
    }

    if (IsLeaf(PagePtr))
        fread(&PagePtr->PgNumOfNxtLfPg, sizeof(PagePtr->PgNumOfNxtLfPg), 1,
              fpbtree);
    fread(&PagePtr->NumBytes, sizeof(PagePtr->NumBytes), 1, fpbtree);
    fread(&PagePtr->NumKeys, sizeof(PagePtr->NumKeys), 1, fpbtree);
    fread(&PagePtr->SubtreeKeyCount, sizeof(PagePtr->SubtreeKeyCount), 1, fpbtree);
    PagePtr->KeyListPtr = NULL;
    if (IsNonLeaf(PagePtr))
        fread(&PagePtr->PtrToFinalRtgPg, sizeof(PagePtr->PtrToFinalRtgPg), 1,
              fpbtree);

    /* Read in the keys */
    KeyListTraverser = NULL;
    for (i = 0; i < PagePtr->NumKeys; i++) {
        KeyNode = (struct KeyRecord *) malloc(sizeof(*KeyNode));
        ck_malloc(KeyNode, "KeyNode");
        if (IsNonLeaf(PagePtr))
            fread(&KeyNode->PgNum, sizeof(KeyNode->PgNum), 1, fpbtree);
        fread(&KeyNode->KeyLen, sizeof(KeyNode->KeyLen), 1, fpbtree);
        KeyNode->StoredKey = (char *) malloc((KeyNode->KeyLen) + 1);
        ck_malloc(KeyNode->StoredKey, "KeyNode->StoredKey in FetchPage()");
        fread(KeyNode->StoredKey, sizeof(char), KeyNode->KeyLen, fpbtree);
        (*(KeyNode->StoredKey + KeyNode->KeyLen)) =
            '\0'; /* string terminator */
        if (IsLeaf(PagePtr))
            fread(&KeyNode->Posting, sizeof(KeyNode->Posting), 1, fpbtree);
        if (KeyListTraverser == NULL) {
            KeyListTraverser = KeyNode;
            PagePtr->KeyListPtr = KeyNode;
        } else {
            KeyListTraverser->Next = KeyNode;
            KeyListTraverser = KeyListTraverser->Next;
        }
    }
    if (PagePtr->NumKeys != 0)
        KeyListTraverser->Next = NULL;

    btReadCount++;
    return (PagePtr);
}
