/* modified by christos, Sept. 2009,
 * - to check for input buffer overflows
 * - to check for page-numbers out of range in printPage()
 * */

/* main driver for btree-based text retreival system
 * modified by Frank Andrasco 1990
*/

#include "def.h"
#include <time.h>

/* modified by Sanjay, Oct 2000, Commented
 * out options "b","d"; added new option T
 * for inorder traversal
 * */

/* modified by christos, Nov. 23 '91 */
/* this array containts the (growing) sizes of the
 * postings records */

long LISTSIZE[100];

extern FILE *fpbtree, *fppost, *fptext;
extern void print_and_reset_stats();
extern int setparms(void);
extern int dbopen(void);
extern void scanTree(void (*f)(struct KeyRecord *));
extern int insert(char *fname);
extern int search(char *key, int flag);
extern int printPage(PAGENO i, FILE *fpb);
extern void PrintTreeInOrder(PAGENO pgNum, int level);
extern int dbclose(void);
extern void printKey(struct KeyRecord *p);
extern void printOcc(struct KeyRecord *p);

extern PAGENO FindNumPagesInTree(void);
extern int iscommon(char *word);
extern int check_word(char *word);
extern void reset_stats();

extern void orderedInsert(char *fname);
extern NUMKEYS subtreeKeyCount(PAGENO pgNum);
extern NUMKEYS countKeyInRange(char *leftKey, char *rightKey);

extern int fetchPageCnt;

int main(int argc, char **argv) {
    char word[MAXWORDSIZE];
    char leftword[MAXWORDSIZE];
    char rightword[MAXWORDSIZE];
    char cmd[MAXWORDSIZE];   /* string to hold a command */
    char fname[MAXWORDSIZE]; /* name of input file */
    PAGENO i;
    int goOn;

    setparms(); /* reads the pagesize and the number of ptrs/postigs_record */
    dbopen();   /* opens or creates the three files (btree, postings, text) */

    goOn = TRUE;
    while (goOn) {
        printf("\n\t*** These are your commands .........\n");
        printf("\t\"C\" to scan the tree\n");
        printf("\t\"i\" to insert\n");
        printf("\t\"o\" to insert in file-specified key order\n");
        printf("\t\"p\" to print a btree page\n");
        printf("\t\"s\" to search, and print the key\n");
        printf("\t\"S\" to search, and print the key, posting list pairs\n");
        printf("\t\"T\" to print the btree in inorder format\n");
        printf("\t\"#\" to print and reset stats\n");
	printf("\t\"n\" to count the number of pages in the btree\n");

	printf("\t\"c\" to count the number of keys in the subtree of a page\n");
	printf("\t\"r\" to count the number of keys in a key range\n");

        printf("\t\"x\" to exit\n");
        /* printf("\"d\" to display statistics, \"c\" to clear them,\n"); */
        scanf("%s", cmd);
        assert(strlen(cmd) < MAXWORDSIZE);
        switch (cmd[0]) {
        case 'C':
            printf("\n*** Scanning... \n");
            scanTree(&printOcc);
            break;
        case 'i':
            printf("\tgive input file name: ");
            scanf("%s", fname);
            assert(strlen(fname) < MAXWORDSIZE);
            printf("\n*** Inserting %s\n", fname);
            insert(fname);

	    print_and_reset_stats();
            break;

        case 'o':
            printf("\tgive input file name: ");
            scanf("%s", fname);
            assert(strlen(fname) < MAXWORDSIZE);
            printf("\n*** Inserting (ordered) %s\n", fname);
	    orderedInsert(fname);
            break;

        case 's':
            printf("enter search-word: ");
            scanf("%s", word);
            assert(strlen(word) < MAXWORDSIZE);
            printf("\n*** Searching for word %s \n", word);
            search(word, FALSE);
            break;
        case 'S':
            printf("enter search-word: ");
            scanf("%s", word);
            assert(strlen(word) < MAXWORDSIZE);
            printf("\n*** Searching for word %s \n", word);
            search(word, TRUE);
            break;
        case 'p':
            printf("pagenumber=?\n");
            scanf("%s", cmd);
            assert(strlen(cmd) < MAXWORDSIZE);
            i = (PAGENO) atoi(cmd);
            printPage(i, fpbtree);
            break;
        case 'T':
            printf("\n*** Printing tree in order .........\n");
            PrintTreeInOrder(ROOT, 0);
            break;
        case '#':
	    print_and_reset_stats();
            break;

        case 'n':
            printf("\nNumber of pages in the btree = %d\n", (int)FindNumPagesInTree());
            break;

        case 'c':
            printf("pagenumber=?\n");
            scanf("%s", cmd);
            assert(strlen(cmd) < MAXWORDSIZE);
            i = (PAGENO) atoi(cmd);
	    if (i < 1 || i > (int)FindNumPagesInTree()) {
	      printf("Error: illegal page number!\n");
	      break;
	    }
            NUMKEYS numKeys = subtreeKeyCount(i);
	    printf("%d\n", numKeys);
	    //print_and_reset_stats();
            break;

	case 'r':
	    reset_stats();
            printf("enter left-bound word: ");
            scanf("%s", leftword);
            assert(strlen(leftword) < MAXWORDSIZE);
	    assert(!iscommon(leftword));
	    assert(check_word(leftword));
            printf("enter right-bound word: ");
            scanf("%s", rightword);
            assert(strlen(rightword) < MAXWORDSIZE);
	    assert(!iscommon(rightword));
	    assert(check_word(rightword));
            printf("\n*** Counting # words in [%s, %s]\n", leftword, rightword);
	    printf("%d\n", (int)countKeyInRange(leftword, rightword));
	    // print_and_reset_stats();
	    break;

        case 'x':
            printf("\n*** Exiting .........\n");
            goOn = FALSE;
            break;
        default:
            printf("\n*** Illegal command \"%s\"\n", cmd);
            break;
        }
    }

    dbclose();
    return (0);
}
