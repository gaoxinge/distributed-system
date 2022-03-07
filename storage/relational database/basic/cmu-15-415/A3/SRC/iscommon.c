#include "defn.g"
#include "comwords.h"

/* returns TRUE (=1) if 'word' is in the list
   of common words
 */

extern int binsearch(char *word, char **array, int n);

int iscommon(char *word) {
    int pos;

    if ((pos = binsearch(word, comwords, NO_COMMON_WORDS)) == ERROR)
        return (FALSE);
    else
        return (TRUE);
}
