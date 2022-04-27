#include "defn.g"

/* It returns TRUE if the string 'word' contains only alphanumerics
 */

int check_word(char *word) {
    unsigned int a = 0;

    for (a = 0; word[a] != EOS; a++)
        if (!isalpha(word[a])) {
            printf("illegal word:|%s|\n", word);
            return (FALSE);
        }
    return (TRUE);
}
