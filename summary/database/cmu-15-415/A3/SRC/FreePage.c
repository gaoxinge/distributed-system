/************************************************************************
*                                                                       *
*    This function frees the space that was dynamimcally secured to     *
*    hold a disk page.                                                  *
*                                                                       *
************************************************************************/

#include "def.h"

void FreePage(struct PageHdr *PagePtr) {
    struct KeyRecord *nextVictim, /* Pointer to the list of keys */
        *currentVictim;           /* Pointer to the list of keys */

    /* Free the keys */
    nextVictim = PagePtr->KeyListPtr;
    while (nextVictim != NULL) {
        currentVictim = nextVictim;
        nextVictim = nextVictim->Next;
        free((char *) currentVictim->StoredKey);
        free((char *) currentVictim);
    }

    /* Free the page header */
    free((char *) PagePtr);
}
