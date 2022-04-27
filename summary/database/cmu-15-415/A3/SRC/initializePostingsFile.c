/* initializePostingsFile.c */

#include "def.h"
extern FILE *fppost;

/* the function writes a list of 100 pointers to the beginning of the postings
   file.  These pointers are later used as heads for 100 freelists of
   increasing size.  The value of (-1) is written to indicate that a null list
*/

void initializePostingsFile(void) {
    int i;
    POSTINGSPTR EmptyList = -1;

    printf("Initializing Postings File...\n");
    for (i = 0; i < 100; i++)
        fwrite(&EmptyList, sizeof(EmptyList), 1, fppost);
}
