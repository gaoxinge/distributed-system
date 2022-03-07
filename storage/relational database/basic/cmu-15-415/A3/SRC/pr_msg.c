#include "defn.g"

/* prints a message from the (text) file,
      'fp'
   starting at
      'start'
    with the TAG character.
 */

void pr_msg(long int start, FILE *fp) {
    int c;
    fseek(fp, (long) start, 0);
    c = getc(fp);
    if (c != TAG) {
        printf("pr_msg: WARNING -");
        printf("document does not start with TAG at %ld\n", start);
    }
    while (((c = getc(fp)) != TAG) && (c != EOF)) {
        putchar(c);
    }
}
