/* This file contains routines that manage a hash table
   with separate chaining
   Much of the code is from the C book, p. 135
 */

#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "def.h"
#define HASHSIZE 100

struct nlist {/* basic table entry */
    char *key;
    struct nlist *next;
};
static struct nlist *hashtab[HASHSIZE];

/* inserts a word in the hash table */

int hash(char *word);

void inhash(char *word) {
    struct nlist *np;
    /* char *malloc(); */
    int val;

    val = hash(word);
    np = hashtab[val];
    while ((np != NULL)) {
        if (strcmp(np->key, word) == 0) { /* found */
            return;                       /* do nothing */
        } else {
            np = np->next;
        }
    }

    /* if this line is reached, the word has not been found;
       insert it at the beginning of the chain */
    np = (struct nlist *) malloc(sizeof(struct nlist));
    ck_malloc(np, "np in inhash()");

    np->key = malloc(strlen(word) + 1);
    strcpy(np->key, word);
    ck_malloc(np->key, "np->key in inhash()");
    np->next = hashtab[val];
    hashtab[val] = np;
}

/* gives the next word in the hash table,
   returning EOH if that's the end */
static int position = -1;
static struct nlist *np = (struct nlist *) NULL; /* np runs over all the
 nodes */
int hgetnext(char *word) {
    if (np != (struct nlist *) NULL) {
        strcpy((char *) word, (char *) (np->key));
        np = np->next;
        return (TRUE);
    } else {
        position++; /* examine next slot */
        /* skip empty slots */
        while ((hashtab[position] == NULL) && (position < HASHSIZE)) {
            position++;
        }

        if (position == HASHSIZE) {
            position = -1; /* reset for the future */
            np = NULL;
            return (EOH);
        } else {
            np = hashtab[position];
            strcpy((char *) word, np->key);
            np = np->next;
            return (TRUE);
        }
    }
}

void inithash(void) {
    int i;

    for (i = 0; i < HASHSIZE; i++) {
        hashtab[i] = NULL;
    }
}

void hprint(void) { /* prints the hash table, for debugging */
    int i;
    struct nlist *np;

    for (i = 0; i < HASHSIZE; i++) {
        if ((np = hashtab[i]) != NULL) {
            printf("slot %d: ", i);
            for (; np != NULL; np = np->next) {
                printf("%s ", np->key);
            }
            printf("\n");
        }
    }
}

/* frees the space of the hash table */
void hfree(void) {
    int i;
    struct nlist *np, *npnext;

    for (i = 0; i < HASHSIZE; i++) {
        if ((np = hashtab[i]) != NULL) {
#ifdef DEBUG
            printf("freeing slot %d: ", i);
#endif

            while (np != NULL) {
#ifdef DEBUG
                printf(" %s ", np->key);
#endif

                free((char *) np->key);

                npnext = np->next;
                free((char *) np);
                np = npnext;
            }
            hashtab[i] = NULL; /* reset it, for the future */
#ifdef DEBUG

            printf("\n");
#endif
        }
    }
}

/* hashing function */
int hash(char *word) {
    int val;
    int i;

    for (val = 0, i = 0; word[i] != '\0'; i++) {
        val += word[i];
    }
    return (val % HASHSIZE);
}
