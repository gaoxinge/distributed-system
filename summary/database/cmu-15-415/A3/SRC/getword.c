#include "def.h"

/* It goes into the file *'fp',
   extracts the next word
   and puts it into the string 'word'.
   It leaves the file pointing to the next character after the word
   that was read.
   Returns
   EOF		if there are no alnum's from the specified position
                up to the EOF.
   ERROR	In case of trouble.
   TRUE		In normal cases.
   DOCSTART	when the TAG character is encountered
                (when scanning a collection of documents)
 */

int getword(FILE *fp, char *word) {
    long wstart; /* the position of the first byte of the word */
    long wend;   /* same for the last byte. */
    int c;

    ck_file(fp, "textfile in getword");

    while (!isalpha(c = getc(fp))) /* skip non-alpha's */
    {
        if (c == EOF) {
            return (EOF);
        }
        if (c == TAG) { /* start-of-document in an archive is encountered */
            /* This check is used only when building an index */
            /*   on an archive (= collection of documents) */
            word[0] = EOS;
            return (DOCSTART);
        }
    }

    wstart = ftell(fp) - 1;       /* fp points to the second character
                                     of the word */
    while (isalpha(c = getc(fp))) /* absorb the rest of the word */
        ;

    if (c != EOF)
        ungetc(c, fp); /* push back the non-alnum character */
    /* In case of EOF, we do not need    */
    /* to call ungetc, because 'fp' points */
    /* to the EOF character,             */
    /* which is exactly the character    */
    /* after the word.                   */

    wend = ftell(fp) - 1; /* fp points to the char. after the word */
    /* even if this character is the EOF char. */

    fseek(fp, (long) wstart, 0);
    fread(word, sizeof(char), wend - wstart + 1, fp);
    word[wend - wstart + 1] = EOS;

#ifdef DEBUG

    printf("getword: start=%ld, end=%ld\n", wstart, wend);
    printf("	word: >|%s|<\n", word);
#endif

    return TRUE;
}
