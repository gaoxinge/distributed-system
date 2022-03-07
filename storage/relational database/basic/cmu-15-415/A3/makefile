BIN=./main
DATA=B-TREE_FILE POSTINGSFILE TEXTFILE
USER=gxg
HANDIN=$(USER)-HW3.tar.gz

all: extract load test

$(BIN):
	cd SRC; make; cp main .. ; cp parms ..

$(DATA): 
	\rm -f $(DATA)
	$(BIN) < import_dict.inp > /dev/null

extract: Datafiles

Datafiles: Datafiles.tar.gz
	tar xvfz Datafiles.tar.gz
	touch Datafiles

load: $(BIN) $(DATA)

test: test_search test_sanity

# make sure your output format is correct
test_sanity_count: load
	$(BIN) < Tests/test_sanity_count.inp > sanity_count.mysol
	@echo ""
	@echo -e "\033[0;34m" test_sanity_count  [test 1/2] "\033[0m"	
	@echo -e "\033[0;34m" $@ should fail, until you fix it "\033[0m"	
	@echo -e "\033[0;34m" ...... The goal is to make sure you are using "\033[0m"
	@echo -e "\033[0;34m" ...... identical output format, so pass me first"\033[0m"
	-@diff sanity_count.mysol Tests/sanity_count.sol; \
	if [ $$? -eq  0 ];\
	then echo -e "\033[0;32m" $@ passed "\033[0m"; \
	else echo -e "\033[0;31m" $@ failed "\033[0m"; fi
	@echo ""

test_sanity_range: load
	@echo ""
	$(BIN) < Tests/test_sanity_range.inp > sanity_range.mysol
	@echo -e "\033[0;34m" test_sanity_range [test 2/2]
	@echo -e "\033[0;34m" $@ should fail, until you fix it "\033[0m"	
	@echo -e "\033[0;34m" ...... The goal is to make sure you are using "\033[0m"
	@echo -e "\033[0;34m" ...... identical output format, so pass me first"\033[0m"
	-@diff sanity_range.mysol Tests/sanity_range.sol; \
	if [ $$? -eq  0 ];\
	then echo -e "\033[0;32m" $@ passed "\033[0m"; \
	else echo -e "\033[0;31m" $@ failed "\033[0m"; fi
	@echo ""

test_sanity: test_sanity_count test_sanity_range

test_search: load
	$(BIN) < Tests/test_search.inp > search.mysol
	@echo ""
	-@diff search.mysol Tests/search.sol; \
	if [ $$? -eq  0 ];\
	then echo -e "\033[0;32m" $@ passed "\033[0m"; \
	else echo -e "\033[0;31m" $@ failed "\033[0m"; fi
	@echo ""


.PHONY: clean spotless handin release

clean:
	\rm -f $(BIN)
	cd SRC; make clean

spotless: clean
	\rm -f $(DATA)
	\rm -rf Datafiles
	cd SRC; make spotless
	\rm -f $(BIN) parms
	\rm -f $(HANDIN)
	\rm -f *.mysol
	\rm -f bulkload*
	\rm -f *~

handin: spotless
	tar czvfh $(HANDIN) \
		--exclude=*.o \
		--exclude=*.out \
		--exclude=.svn \
		DOC/ Datafiles.tar.gz README SRC/ Tests/ makefile import_dict.inp load_dict.sh gen_textfile.py

release: spotless
	tar czvfh btree.tar.gz \
		--exclude=*.o \
		--exclude=*.out \
		--exclude=.svn \
		DOC/ Datafiles.tar.gz README SRC/ Tests/ makefile import_dict.inp load_dict.sh gen_textfile.py
