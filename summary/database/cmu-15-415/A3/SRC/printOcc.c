/*
    prints the key, along with the number
    of occurrencies (ie., # of documents
    that contain it)

modified for contiguious postings file  by Frank Andrasco

 */

#include "def.h"
extern FILE *fppost;

void printOcc(struct KeyRecord *p) {
    POSTINGSPTR pptr;
    NUMPTRS NumTextOffsets;

    pptr = p->Posting;
    fseek(fppost, (long) pptr, 0);
    fread(&NumTextOffsets, sizeof(NumTextOffsets), 1, fppost);

    printf("%s:%d\n", p->StoredKey, (int) NumTextOffsets);
}
