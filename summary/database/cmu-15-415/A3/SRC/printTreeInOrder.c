#include "def.h"

void PrintTreeInOrder(PAGENO pgNum, int level) {
    struct PageHdr *p;
    struct KeyRecord *k;
    struct PageHdr *FetchPage(PAGENO Page); // add this line to avoid seg-fault
    int i;

    p = (struct PageHdr *) FetchPage(pgNum);

    if (IsNonLeaf(p)) {
        for (k = p->KeyListPtr; k != NULL; k = k->Next) {
            PrintTreeInOrder(k->PgNum, level + 1);
            for (i = 0; i < level * 15; i++) {
                printf(" ");
            }
            printf("%s \n", k->StoredKey);
        }
        PrintTreeInOrder(p->PtrToFinalRtgPg, level + 1);
    } else {
        int count = 0;
        for (k = p->KeyListPtr; k != NULL; k = k->Next) {
            count++;
            if (k == p->KeyListPtr) {
                for (i = 0; i < level * 15; i++) {
                    printf(" ");
                }
                printf("%s ", k->StoredKey);
            } else if (k->Next == NULL) {
                printf("... %s ", k->StoredKey);
            }
        }
        printf("(%d) \n", count);
    }
}
