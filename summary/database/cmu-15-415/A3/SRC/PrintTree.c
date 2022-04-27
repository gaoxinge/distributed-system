/************************************************************************
*                                                                      *
*     This function prints the pages of the B-Tree, page by page,      *
*     beginning with the Root.  The pages have been stored and are     *
*     printed in an ordered manner, i.e., 1 < 2 < ... < n.             *
*                                                                      *
************************************************************************/

#include "def.h"
extern FILE *fpbtree;

void printPage(PAGENO i, FILE *fpb);
extern long int ffsize(FILE *fp);

void PrintTree(void) {
    PAGENO i;

    fpbtree = fopen("B-TREE_FILE", "r");

    /* print the pages of the tree */
    printf("Here is the B-Tree By Page (starting with the root):\n\n");

    for (i = 1; feof(fpbtree) == 0; i++) {
        printPage(i, fpbtree);
    }
    fclose(fpbtree);
}

void printPage(PAGENO i, FILE *fpb) {
    POSTINGSPTR PostOffset;
    NUMKEYS NumKeys;
    NUMKEYS SubtreeKeyCount;
    KEYLEN KeyLen;
    NUMBYTES NumBytes;
    PAGENO PtrToNxtLfPg, PtrToFinalRtgPg, PgNum;
    int j;
    char key[MAXWORDSIZE], Ch;

    if (i < 1) {
        printf("page numbers start from 1 and on\n");
        return;
    }

    if (ffsize(fpb) <= (i - 1) * PAGESIZE) { /* illegal page number */
        printf("page numbers start from 1 and not exceed the last one \n");
        return;
    }

    fseek(fpb, (long) (i - 1) * PAGESIZE, 0);
    fread(&Ch, sizeof(Ch), 1, fpb);
    if (feof(fpb) != 0)
        exit(0);
    printf("Leafstatus:%c\n", Ch);
    fread(&PgNum, sizeof(PgNum), 1, fpb);
    printf("Page#:%d\n", (int) PgNum);
    if (Ch == LeafSymbol) {
        fread(&PtrToNxtLfPg, sizeof(PtrToNxtLfPg), 1, fpb);
        printf("PtrtoNextLeafPage:%d\n", (int) PtrToNxtLfPg);
    }
    fread(&NumBytes, sizeof(NumBytes), 1, fpb);
    printf("Number of bytes occcupied:%d\n", NumBytes);
    fread(&NumKeys, sizeof(NumKeys), 1, fpb);
    printf("Number of keys:%d\n", NumKeys);
    fread(&SubtreeKeyCount, sizeof(SubtreeKeyCount), 1, fpb);
    printf("Number of keys in subtree:%d\n", SubtreeKeyCount);
    if (Ch == NonLeafSymbol) {
        fread(&PtrToFinalRtgPg, sizeof(PtrToFinalRtgPg), 1, fpb);
        printf("PtrToFinalRtgPg%d\n", (int) PtrToFinalRtgPg);
    }
    for (j = 0; j < NumKeys; j++) {
        if (Ch == NonLeafSymbol) {
            fread(&PgNum, sizeof(PgNum), 1, fpbtree);
            printf("NextPage:%d, ", (int) PgNum);
            fread(&KeyLen, sizeof(KeyLen), 1, fpbtree);
            fread(key, sizeof(char), KeyLen, fpbtree);
            (*(key + KeyLen)) = '\0';
            printf("key:%s, ", key);
            printf("length:%d\n", KeyLen);
        }
        if (Ch == LeafSymbol) {
            fread(&KeyLen, sizeof(KeyLen), 1, fpbtree);
            printf("Keylength:%d, ", KeyLen);
            fread(key, sizeof(char), KeyLen, fpbtree);
            (*(key + KeyLen)) = '\0';
            printf("key:%s, ", key);
            fread(&PostOffset, sizeof(PostOffset), 1, fpbtree);
            printf("Postings offset:%d\n", (int) PostOffset);
        }
    }
    printf("\n");
}
