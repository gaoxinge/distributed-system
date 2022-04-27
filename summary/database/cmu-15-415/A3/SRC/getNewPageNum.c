/*
   It returns the page-number of the next page
   in the btree file
 */

#include "def.h"
extern FILE *fpbtree;

PAGENO getNewPageNum(void) {
    PAGENO new;
    long ffsize(FILE * fp);

    new = (PAGENO) ffsize(fpbtree) / PAGESIZE + 1;
    return (new);
}
