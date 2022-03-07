/*********************************************************************
*                                                                    *
*    This function searches the b-tree for the given word
                key
     and prints the associated postings list.
*                                                                    *
*********************************************************************/

#include "def.h"
extern FILE *fpbtree;
extern int sqCount; /* statistics: # of successf. queries asked */
extern int uqCount; /* # of unsuccessf. queries */

extern int iscommon(char *word);
extern int check_word(char *word);
extern int strtolow(char *s);
extern int getpostings(POSTINGSPTR pptr);
extern POSTINGSPTR treesearch(PAGENO PageNo, char *key);

void search(char *key, int flag) {
    POSTINGSPTR pptr;

    /* Print an error message if strlen(key) > MAXWORDSIZE */
    if (strlen(key) > MAXWORDSIZE) {
        printf("ERROR in \"search\":  Length of key Exceeds Maximum Allowed\n");
        printf(" and key May Be Truncated\n");
    }
    if (iscommon(key)) {
        printf("\"%s\" is a common word - no searching is done\n", key);
        return;
    }
    if (check_word(key) == FALSE) {
        return;
    }
    /* turn to lower case, for uniformity */
    strtolow(key);

    pptr = treesearch(ROOT, key);
    if (pptr == NONEXISTENT) {
        printf("key \"%s\": not found\n", key);
        uqCount++;
    } else {
        if (flag) {
            getpostings(pptr);
            sqCount++;
        } else {
            printf("Found the key!\n");
        }
    }
}
