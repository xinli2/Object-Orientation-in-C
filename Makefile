
CC=gcc
#CFLAGS=-Wall -O3 -std=gnu99
CFLAGS=-Wall -g -std=gnu99



all: testcases mergeSort

testcases:  test_dblList_01_allocFree
testcases: test_dblList_02_addAfter



# see http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html 
#
# Also, note the new gcc syntax.  We're combining .c files and .o
# files on the same line.

mergeSort: mergeSort.c encapsulatedListStr.h encapsulatedListStr.o
	$(CC) $^ -o $@

test_dblList_01_allocFree: test_dblList_01_allocFree.c dblListInt.c
	$(CC) $^ -o $@

test_dblList_02_addAfter: test_dblList_02_addAfter.c dblListInt.c
	$(CC) $^ -o $@

# 'make' allows you to write little rules which define the target/dependency
# relationships, but which do not actually add any new build rules.

dblListInt.o: dblListInt.c dblListInt.h
encapsulatedListStr.o: encapsulatedListStr.c encapsulatedListStr.h



clean:
	-rm *.o test_dblList_01_allocFree test_dblList_02_addAfter mergeSort
