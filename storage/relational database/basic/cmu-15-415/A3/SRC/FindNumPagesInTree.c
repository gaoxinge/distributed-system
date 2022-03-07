/**************************************************************************
 returns the number of pages currently in the B-tree
**************************************************************************/

#include "def.h"
extern FILE *fpbtree;

PAGENO FindNumPagesInTree(void) {
    PAGENO num;
    long ffsize(FILE * fp);

    num = (PAGENO) ffsize(fpbtree) / PAGESIZE;
    return (num);
}
