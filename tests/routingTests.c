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


static int setup(void **state){
	srand(time(NULL));	
	int amount = 100;    
    ipTable * tables;
    tables = malloc(amount * sizeof *tables);
    assert_non_null(tables);
    int addressMask = 0;
    int addressId = 1;
   	tables[0].identifier = addressId;
   	tables[0].mask = addressMask;
    setupTable(&tables[0]);
    //create tables:
    for(int i = 1; i < amount; i++){
        setupTable(&tables[i]);
        setAddress(&addressMask, &addressId, &tables[i]);
        setDestinations(&tables[i],tables, i);
    }
    *state = tables;
    return 0;
}

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
	assert_int_equal(checkIfRightAddress(&set[random],mask,id), 1);
	assert_int_equal(checkIfRightAddress(&set[random-1],mask,id), 0);
}

/*if second param int is > first int and >= 0, the method should return 1 and otherwise 0*/
static void testAddressComparison(){
	assert_int_equal(addressComparison(5, 3), 1);
	assert_int_equal(addressComparison(3, 5), 0);
	assert_int_equal(addressComparison(1, -1), 0);
}
/*checkNextTable should return the right int compared to the value of the tables visited integer*/
static void testCheckNextTable(void ** state){
	ipTable * set = *state;
	assert_non_null(set);
	set[20].visited = 3;
	set[50].visited = 1;
	set[83].visited = 2;
	assert_int_equal(checkNextTable(&set[20],999, 999), 0);
	assert_int_equal(checkNextTable(&set[50],999, 999), 1);
	assert_int_equal(checkNextTable(&set[83],999, 999), 2);
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

/*Sets 1000 times 1000 node size network and tries to find a path to the last node*/
static void set1000destinationsAndFindRouteToLastTable(){
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		int amount = 1000;    
	    ipTable * tables;
	    tables = malloc(amount * sizeof *tables);
	    assert_non_null(tables);
	    int addressMask = 0;
	    int addressId = 1;
	   	tables[0].identifier = addressId;
	   	tables[0].mask = addressMask;
	    setupTable(&tables[0]);
	    //create tables:
	    for(int i = 1; i < amount; i++){
	        setupTable(&tables[i]);
	        setAddress(&addressMask, &addressId, &tables[i]);
	        setDestinations(&tables[i],tables, i);
	    }
		ipTable * destination = traceRoute(&tables[0], 1000, 168, tables[amount-1].mask, tables[amount-1].identifier);
		printf("ma %i\n", i);
		assert_true(destination != NULL);
		freeDestinations(tables, amount);
		free(tables);
	}	
}	
/*Sets 1000 times 2000 node size network and tries to find a path to a random node*/
static void set2000destinationsAndFindRouteToRandomTable(){
	srand(time(NULL));
	for(int i = 0; i < 1000; i++){
		int amount = 2000;    
	    ipTable * tables;
	    tables = malloc(amount * sizeof *tables);
	    assert_non_null(tables);
	    int addressMask = 0;
	    int addressId = 1;
	   	tables[0].identifier = addressId;
	   	tables[0].mask = addressMask;
	    setupTable(&tables[0]);
	    //create tables:
	    for(int i = 1; i < amount; i++){
	        setupTable(&tables[i]);
	        setAddress(&addressMask, &addressId, &tables[i]);
	        setDestinations(&tables[i],tables, i);
	    }
	    int random = rand() % 1000;
		ipTable * destination = traceRoute(&tables[0], amount, 168, tables[random].mask, tables[random].identifier);
		printf("ma %i\n", i);
		int o;
		for(o = 0; o < random+10; o++){
			if(tables[o].mask == tables[random].mask && (tables[o].identifier == tables[random].identifier)){
				printf("it exists! index = %i random=%i\n", o, random);
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


int main(void) {
    const struct CMUnitTest tests[] = {
    	cmocka_unit_test_setup_teardown(testCheckIfRightAddress, setup, teardown),
    	cmocka_unit_test(testAddressComparison),
    	cmocka_unit_test_setup_teardown(testCheckNextTable, setup, teardown),
    	//cmocka_unit_test_setup_teardown(testGetNextHop, setup, teardown),
    	cmocka_unit_test(set1000destinationsAndFindRouteToLastTable),
        cmocka_unit_test(set2000destinationsAndFindRouteToRandomTable),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
