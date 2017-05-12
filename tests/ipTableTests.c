/*
 * Tests for ipTable.c/h
 * The tests use Cmocka
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/headers/ipTable.h"


static int setup(void **state){
    ipTable *tables = malloc(7 * sizeof *tables);
    assert_non_null(tables);
    *state = tables;
    return 0;
}

static int teardown(void **state){
    ipTable * set = *state;
    free(set);
    return 0;
}

/*The tables are set up, and all of the tables visited should be 0,
  lengthofdestinations should be 0 and destinations NULL*/
static void testSetTable(void **state){
	ipTable * set = *state;
	for(int z = 0; z < 7; z ++){
		setupTable(&set[z]);
	}
	for(int u = 0; u < 7; u++){
	    assert_int_equal(set[u].visited, 0);
	    assert_int_equal(set[u].lengthOfDestinations, 0);
	    assert_true(set[u].destinations == NULL);
	}
	set = NULL;
	free(set);
}

/*The tables are all set to dead ends, resetSearch is called
  and the visited fields should be 0 again*/
static void testResetSearch(void **state){
	ipTable * set = *state;
	for(int z = 0; z < 7; z ++){
		set[z].visited = 3;
	}
	resetSearch(set, 7);
	for(int h = 0; h < 7; h ++){
		assert_int_equal(set[h].visited, 0);
	}
	set = NULL;
	free(set);
}

/*An ipTable is created and a random address is given into it. The given address 
  should be same as the result that comes from the genereteAddress function*/
static void generatedAddressIsGivenToIpTable(){
    int nm = 168;
    int m = 1;
    int i = 992;
    int * mask = &m;
    int * id = &i;
    int * nmask = &nm;
    struct ipTableTag table;
    setAddress(nmask, mask, id, &table);
    assert_int_equal(*mask, table.mask);
    assert_int_equal(*id, table.identifier);
}


int main(void) {
    const struct CMUnitTest tests[] = {
    	cmocka_unit_test(testSetTable),
    	cmocka_unit_test(testResetSearch),
        cmocka_unit_test(generatedAddressIsGivenToIpTable),
    };

    return cmocka_run_group_tests(tests, setup, teardown);
}