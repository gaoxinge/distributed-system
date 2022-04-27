/***********************************************************************
*                                                                      *
*    This function compares the possible new key with a key stored     *
*    in the B-Tree.  The function returns the value '0' if the keys    *
*    match, '1' if the new key is lexicographically less than the      *
*    stored key, and '2' if the new key is lexicographically more      *
*    than the stored key.                                              *
*                                                                      *
***********************************************************************/

#include "def.h"
#include <stdio.h>

/* Key:  Possible New Key */
/* Word: The Key Stored in the B-Tree */
int CompareKeys(char *Key, char *Word) {

    int m = max(strlen(Key), strlen(Word));

    int i = 0;
    for (i = 0; i < m; i++) {
        if (i >= strlen(Key)) {
            return (1);
        } else if (i >= strlen(Word)) {
            return (2);
        } else if (Key[i] < Word[i]) {
            return (1);
        } else if (Key[i] > Word[i]) {
            return (2);
        }
    }
    return (0);
}
