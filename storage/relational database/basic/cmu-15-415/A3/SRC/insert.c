/* inserts the file 'fname' in the database,
   PREFIXING it with a TAG (ctrl-V)
 */

#include <stdio.h>
#include "def.h"
#include "defn.g"

extern FILE *fpbtree, *fppost, *fptext;
FILE *fpinp;

extern int inithash(void);
extern int iscommon(char *word);
extern int strtolow(char *s);
extern int inhash(char *word);
extern int InsertTree(char *Key, TEXTPTR TextOffset);
extern int hfree(void);

void insert(char *fname) {
    char word[MAXWORDSIZE];
    TEXTPTR StartNewText; /* Offset to newly concatenated document */
    int getword(FILE * fp, char *word), hgetnext(char *word);
    int c;

    if ((fpinp = fopen(fname, "r")) == NULL) {
        printf("Error: Cannot Open Input Word File: %s\n", fname);
        return;
    }

    /* Concatenate the new text file to the file "TEXTFILE"
       and place file pointer at the start of the new text file */
    gotoeof(fptext);
    StartNewText = ftell(fptext);
    putc(TAG, fptext); /* prefix with the document separator */
    while ((c = getc(fpinp)) != EOF) {
        putc(c, fptext);
    }

    fseek(fptext, (long) StartNewText, 0);

    /* eliminate dupl. words by hashing into a h.table */
    /* also, randomizes them somehow */
    rewind(fpinp);
    inithash(); /* initialize the hash table */
    while (getword(fpinp, word) != EOF) {
        if (!iscommon(word)) {
            strtolow(word); /* turn to lower case only */
            inhash(word);
        }
    }
#ifdef DEBUG
    hprint(); /* just for testing */
#endif

    while (hgetnext(word) != EOH)
        InsertTree(word, StartNewText);

    hfree(); /* empties the hash table */

    fclose(fpinp);
}
