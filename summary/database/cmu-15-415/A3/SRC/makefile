CC=gcc
CFLAGS=-g -Wall -Werror

SRC=main.c PrintTree.c CompareKeys.c\
	CreatePosting.c FetchPage.c InsertKeyInLeaf.c InsertTree.c\
	UpdatePostingsFile.c PropagatedInsertion.c \
	SplitPage.c FindInsertionPosition.c InsertKeyInNonLeaf.c\
	FlushPage.c FreePage.c CreateRoot.c FindNumPagesInTree.c\
	FindPageNumOfChild.c SplitRoot.c \
	treesearch.c search.c searchLeaf.c getpostings.c \
	setparms.c dbopen.c dbclose.c insert.c \
	hashtab.c getNewPageNum.c fillIn.c \
	scanTree.c scanLeaf.c printKey.c  printOcc.c\
	getrec.c freerec.c initializePostingsFile.c isfull.c \
	postStats.c printTreeInOrder.c deleteKey.c strdist.c \
	stats.c string_array.c \
	subtreeKeyCount.c countKeyInRange.c orderedInsert.c

GENUTILSRC=strsave.c ffsize.c strtolow.c
SRC1=getword.c iscommon.c binsearch.c check_word.c pr_msg.c
ALLSRC=$(SRC) $(SRC1) $(GENUTILSRC)
ALLDFN=def.h defn.g comwords.h

OBJ=$(patsubst %.c,%.o,$(SRC))
GENUTILOBJ=$(patsubst %.c,%.o,$(GENUTILSRC))
OBJ1=$(patsubst %.c,%.o,$(SRC1))
ALLOBJ=$(OBJ) $(OBJ1) $(GENUTILOBJ)

main: $(ALLOBJ)
	${CC} $(CFLAGS) $(ALLOBJ) -lm -o main

$(OBJ): def.h

$(OBJ) $(OBJ1): defn.g

printout: *.h *.g *.c 
	pr $? | qpr 
	touch printout

spotless: cleanup cleanupo
	\rm -f main

cleanupo:
	\rm -f *.o
	\rm -f *~

clean: cleanupo

cleanup:
	\rm -f TEXTFILE POSTINGSFILE B-TREE_FILE

version: $(ALLSRC) def.h comwords.h defn.g makefile README.version parms main DOC
	tar cvf version $(ALLSRC) def.h comwords.h defn.g makefile README.version parms main DOC

all.tar: $(ALLSRC) def.h comwords.h defn.g makefile parms DOC/* test.inp
	tar cvfh all.tar $(ALLSRC) def.h comwords.h  defn.g  test.inp \
	makefile parms DOC

test.out: main test.inp parms
	cat test.inp | main > test.out

checkin:
	ci -l $(REV) $(ALLSRC) $(ALLDFN) makefile parms 

checkout:
	co -l $(REV) $(ALLSRC) $(ALLDFN) makefile parms 
