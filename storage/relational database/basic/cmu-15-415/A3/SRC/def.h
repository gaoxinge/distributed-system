/*****************************************************************************
*                                                                            *
*    This is the definition file for the B-Tree program.  It contains        *
*    declarations for all functions utilized; program macros and             *
*    constants; a few necessary globals; typedef declarations; and           *
*    structure definitions.                                                  *
*                                                                            *
*    Consult the Programmer's Manual ("Pgmrs.Man") for the program           *
*    description.                                                            *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include "defn.g"
#include <stdlib.h>   
#include <string.h>
#include <assert.h>

extern int PAGESIZE;	/* Size of page (in bytes) to be stored on disk  */
extern int MAXTEXTPTRS;	/* POSTINGSFILE stores so many ptrs,
			   then goes to overflow */

#define MAXWORDSIZE (100) /* Maximum size of any key */
#define ROOT (1)          /* The root is always stored as first page on disk */
#define FIRSTLEAFPG (2)   /* The page number of first (orginal) leaf page */
#define LeafSymbol ('L')     /* To differentiate a Leaf page */  
#define NonLeafSymbol ('N')  /* To differentiate a Nonleaf page */
#define IsLeaf(x)     (LeafSymbol == (x)->PgTypeID)
#define IsNonLeaf(x)  (NonLeafSymbol == (x)->PgTypeID)
#define TRUE		(1)
#define FALSE		(0)
#define EOH		(-1)	/* end of the hash table */
#define NULLPAGENO	(-3)	/* null page pointer */
#define NONEXISTENT	(-2)

typedef long PAGENO;
typedef long TEXTPTR;
typedef long POSTINGSPTR;
typedef int  KEYLEN;
typedef int  NUMKEYS;
typedef int  NUMBYTES; 
typedef long  NUMPTRS;     /* needed to make contiguous postings easier */

#define gotoeof(x)	fseek((x), (long) 0, 2);

/* The following structure is utilized for holding a page of the B-Tree.
   It is used for both Leaf and NonLeaf pages.  The pages are differentiated
   by the first byte which contains 'L' if it is a Leaf page or 'N' if it
   is a NonLeaf page.  All Leaf pages contain the field 'PgNumOfNxtLfPg'
   which is a pointer (page number) to the next logical leaf page.  All
   NonLeaf pages contain the field 'PtrToFinalRtgPg' which is a pointer
   (page number) to the rightmost child.                                   */  

struct PageHdr {
     char              PgTypeID;         /* 'N' for NonLeaf, 'L' for Leaf */
     PAGENO           PgNum;            
     PAGENO           PgNumOfNxtLfPg;   /* FOR LEAF PAGES ONLY */
     NUMBYTES          NumBytes;
     NUMKEYS           NumKeys;          
     NUMKEYS            SubtreeKeyCount; /* THIS IS YOUR TASK :) */
     struct KeyRecord *KeyListPtr;
     PAGENO           PtrToFinalRtgPg;  /* FOR NONLEAF PAGES ONLY */ 
};


/* The following structure is used to hold the keys which are 
   stored in the B-Tree page.  It is used for both Leaf and NonLeaf keys.
   If the page is a NonLeaf page, the key will be accompanied by the
   field 'PgNum' which is a pointer (page number) to a left child page
   that contains keys which are lexicographically less than the the key
   in this page.  If the page is a Leaf page, the key will be accompanied
   by the field 'Posting' which is a pointer (offset) into the 
   POSTINGSFILE (which contains the offsets into the Text file).       */

struct KeyRecord {
     PAGENO           PgNum;             /* FOR NONLEAF PAGES ONLY */
     KEYLEN            KeyLen; 
     char             *StoredKey;
     POSTINGSPTR       Posting;           /* FOR LEAF PAGES ONLY */
     struct KeyRecord *Next;
};

/* 'upKey' should be used to hold the key to be moved upwards
    upon splitting */
struct upKey {
	PAGENO		left;	/* left page, with keys <= */
	PAGENO		right;	/* right page, with keys > */
	char *		key;
};
