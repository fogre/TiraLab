/*
  Test methods for routing.h
  The testing uses CMocka.
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <time.h>
#include <cmocka.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/destinationsCreator.h"
#include "../src/headers/randomAddressGenerator.h"
#include "../src/headers/routing.h"

/*setup method for some of the tests*/
static int setup(void **state){
	srand(time(NULL));	
	int amount = 100;    
    ipTable * tables;
    tables = malloc(amount * sizeof *tables);
    assert_non_null(tables);
	int addressNetmask = 168;
	int addressMask = 0;
	int addressId = 1;
	tables[0].netmask = addressNetmask;
	tables[0].identifier = addressId;
	tables[0].mask = addressMask;
	setupTable(&tables[0]);
	//create tables:
	for(int i = 1; i < amount; i++){
		setupTable(&tables[i]);
		setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
		setDestinations(&tables[i],tables, i);
	}
    *state = tables;
    return 0;
}
/*teardown for some of the tests*/
static int teardown(void **state){
    ipTable * set = *state;
    freeDestinations(set, 100);
    free(set);
    return 0;
}

/*if right address given, the checkIfRightAddress returns 1, otherwise 0*/
static void testCheckIfRightAddress(void ** state){
	ipTable * set = *state;
	assert_non_null(set);
	int random = rand() % 100;
	//int net = set[random].netmask;
	int mask = set[random].mask;
	int id = set[random].identifier;
	assert_int_equal(checkIfRightAddress(&set[random],168, mask,id), 1);
	assert_int_equal(checkIfRightAddress(&set[random-1],168, mask,id), 0);
}

/*if second param int is > first int and >= 0, the method should return 1 and otherwise 0
static void testmaskAddressComparison(){
	assert_int_equal(maskAddressComparison(5, 3), 1);
	assert_int_equal(maskAddressComparison(3, 5), 0);
	assert_int_equal(maskAddressComparison(1, 0), 1);
}*/
/*checkNextTable should return the right int compared to the value of the tables visited integer*/
static void testCheckNextTable(void ** state){
	ipTable * set = *state;
	assert_non_null(set);
	set[20].visited = 3;
	set[50].visited = 1;
	set[83].visited = 2;
	assert_int_equal(checkNextTable(&set[20],999, 999, 999), 0);
	assert_int_equal(checkNextTable(&set[50],999, 999, 999), 1);
	assert_int_equal(checkNextTable(&set[83],999, 999, 999), 2);
}

/*This method gets tested in below:
static void testGetNextHop(void ** state){
	ipTable * set = *state;
	assert_non_null(set);
	int random = rand() % 100;
	ipTable * table = &set[random];
	int size = table->lengthOfDestinations;
	assert_true(getNextHop(table, 168, 999, 999) == table->destinations[size-1]);
}*/

/*Sets 1000 times 1000 node size network and tries to find a path to the last node
  The destination table shound't be null, and it should be the last node*/
static void set1000destinationsAndFindRouteToLastTable(){
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		int amount = 1000;    
	    ipTable * tables;
	    tables = malloc(amount * sizeof *tables);
	    assert_non_null(tables);
		int addressNetmask = 168;
		int addressMask = 0;
		int addressId = 1;
		tables[0].netmask = addressNetmask;
		tables[0].identifier = addressId;
		tables[0].mask = addressMask;
		setupTable(&tables[0]);
		//create tables:
		for(int i = 1; i < amount; i++){
			setupTable(&tables[i]);
			setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
			setDestinations(&tables[i],tables, i);
		}
		ipTable * destination = traceRoute(&tables[0], 1000, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
		assert_true(destination != NULL);
		assert_true(destination == &tables[amount-1]);
		freeDestinations(tables, amount);
		free(tables);
	}	
}	
/*Sets 1000 times 2000 node size network and tries to find a path to a random node
  The destination table shound't be null, the found table should be the same as the searched table and the index should be the right one*/
static void set2000destinationsAndFindRouteToRandomTable(){
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		int amount = 2000;    
	    ipTable * tables;
	    tables = malloc(amount * sizeof *tables);
	    assert_non_null(tables);
		int addressNetmask = 168;
		int addressMask = 0;
		int addressId = 1;
		tables[0].netmask = addressNetmask;
		tables[0].identifier = addressId;
		tables[0].mask = addressMask;
		setupTable(&tables[0]);
		//create tables:
		for(int i = 1; i < amount; i++){
			setupTable(&tables[i]);
			setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
			setDestinations(&tables[i],tables, i);
		}
	    int random = rand() % amount;
		ipTable * destination = traceRoute(&tables[0], amount, tables[random].netmask, tables[random].mask, tables[random].identifier);
		printf("ma %i\n", i);
		int o;
		for(o = 0; o < random+10; o++){
			if(tables[o].mask == tables[random].mask && (tables[o].identifier == tables[random].identifier)){
				break;
			}
		}
		assert_int_equal(random, o);
		assert_true(destination != NULL);
		assert_true(destination == &tables[random]);
		freeDestinations(tables, amount);
		free(tables);
	}	
}	


/*Sets 1000 times 2000 node size network and tries to find a path to a random node
  The destination table shound't be null, the found table should be the same as the searched table and the index should be the right one*/
static void set80000destinationsAndFindRouteToRandomAndLastTable(){
	srand(time(NULL));
	int amount = 80000;    
    ipTable * tables;
    tables = malloc(amount * sizeof *tables);
    assert_non_null(tables);
	int addressNetmask = 168;
	int addressMask = 0;
	int addressId = 1;
	tables[0].netmask = addressNetmask;
	tables[0].identifier = addressId;
	tables[0].mask = addressMask;
	setupTable(&tables[0]);
	//create tables:
	for(int i = 1; i < amount; i++){
		setupTable(&tables[i]);
		setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
		setDestinations(&tables[i],tables, i);
	}
    int random = rand() % amount;
	ipTable * destination = traceRoute(&tables[0], amount, tables[random].netmask, tables[random].mask, tables[random].identifier);
	assert_true(destination != NULL);
	assert_true(destination == &tables[random]);
	resetSearch(tables, amount);
	destination = traceRoute(&tables[0], amount, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
	assert_true(destination != NULL);
	assert_true(destination == &tables[amount-1]);
	freeDestinations(tables, amount);
	free(tables);
}	



int main(void) {
    const struct CMUnitTest tests[] = {
    	cmocka_unit_test_setup_teardown(testCheckIfRightAddress, setup, teardown),
    	//cmocka_unit_test(testmaskAddressComparison),
    	cmocka_unit_test_setup_teardown(testCheckNextTable, setup, teardown),
    	cmocka_unit_test(set1000destinationsAndFindRouteToLastTable),
        cmocka_unit_test(set2000destinationsAndFindRouteToRandomTable),
        cmocka_unit_test(set80000destinationsAndFindRouteToRandomAndLastTable),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
