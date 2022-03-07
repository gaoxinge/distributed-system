
/* closes the three files (btree, postings & text files) */

#include <stdio.h>
#include "def.h"

extern FILE *fppost, *fpbtree, *fptext;

void dbclose(void) {
    fclose(fppost);
    fclose(fpbtree);
    fclose(fptext);
}
