#include "def.h"

/*
 * implements a stats counter.
 *
 * there is also a simple reset function that shall be called before a
 * series of operations in order to measure the overall overhead.
 */

int btWriteCount = 0; /* number of writes on B-tree */
int btReadCount = 0;  /* number of reads on B-tree */
int pWriteCount = 0;  /* number of writes on postings */
int pReadCount = 0;   /* number of reads on postings */
int iCount = 0;       /* number of inserted words */
int sqCount = 0;      /* number of successful queries */
int uqCount = 0;      /* number of unsucc. queries */

void print_and_reset_stats() {
    printf("# of reads on B-tree: %d\n", btReadCount);
    btReadCount = 0;
}

void reset_stats() {
    btReadCount = 0;
}
