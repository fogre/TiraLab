/*
  Test methods for routing.c
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
#include "../src/headers/routing.h"

/*setup method for some of the tests*/
static int setup(void **state){

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

/*Sets 1000 times 1000 node size network and tries to find a path to the last node
  The destination table shound't be null, and it should be the last node*/
static void set1000destinationsAndFindRouteToLastTable(){

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


/*Sets 100 times 100 node size network and tries to find a path to a random and last node
  The destination table shound't be null and the found table should be the same as the searched table.*/
static void set100destinationsAndFindRouteToLastAndRandomTable(){
	int i;
	for(i = 0; i < 100; i++){
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
   		int random = rand() % amount;
		ipTable * destination = traceRoute(&tables[0], amount, tables[random].netmask, tables[random].mask, tables[random].identifier);
		printf("ma %i\n", i);	
		assert_true(destination != NULL);
		assert_true(destination == &tables[random]);
		resetSearch(tables, amount);
		destination = traceRoute(&tables[0], amount, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
	    printf("ma %i\n", i);	
		assert_true(destination != NULL);
		assert_true(destination == &tables[amount-1]);
		destination = NULL;
		free(destination);
		freeDestinations(tables, amount);
		free(tables);
		}

}	


/*Sets 100 times 1000000 node size network and tries to find a path to a random and last node
  The destination table shound't be null and the found table should be the same as the searched table*/
static void set1000000destinationsAndFindRouteToLastAndRandomTable(){
	int i;
	for(i = 0; i < 50; i++){
		int amount = 1200000;    
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
		ipTable * destination = NULL;
   		int random = rand() % amount;
		destination = traceRoute(&tables[0], amount+5, tables[random].netmask, tables[random].mask, tables[random].identifier);
		printf("ma random! %i\n", i);
		/*if(!destination){
		  for(int o = 0; o < amount; o++){
		  	printf("TABLE %i\n", o);
	    	printDestinations(&tables[o]);
	    	printf("\n");
	      }
	    }	*/
		assert_true(destination != NULL);
		assert_true(destination == &tables[random]);
		resetSearch(tables, amount);
		for(int f = 0; f < amount; f++){
			assert_int_equal(tables[f].visited, 0);
		}
		destination = traceRoute(&tables[0], amount+5, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
	    printf("ma last! %i\n", i);
	   /* if(!destination){
		  for(int o = 0; o < amount; o++){
		  	printf("TABLE %i\n", o);
	    	printDestinations(&tables[o]);
	    	printf("\n");
	      }
	    }*/
		assert_true(destination != NULL);
		assert_true(destination == &tables[amount-1]);
		destination = NULL;
		free(destination);
		freeDestinations(tables, amount);
		free(tables);
		}

}	



int main(void) {
	srand(time(NULL));	
    const struct CMUnitTest tests[] = {
    	cmocka_unit_test_setup_teardown(testCheckIfRightAddress, setup, teardown),
    	cmocka_unit_test_setup_teardown(testCheckNextTable, setup, teardown),
    	cmocka_unit_test(set1000destinationsAndFindRouteToLastTable),
        cmocka_unit_test(set2000destinationsAndFindRouteToRandomTable),
        cmocka_unit_test(set100destinationsAndFindRouteToLastAndRandomTable),
        cmocka_unit_test(set1000000destinationsAndFindRouteToLastAndRandomTable),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
