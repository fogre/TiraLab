#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/destinationsCreator.h"
#include "../src/headers/routing.h"


/*Sets 1000 times 1000 node size network and tries to find a path to the last node
  The destination table shound't be null, and it should be the last node*/
static void set1000destinationsAndFindRouteToLastTable(){
	for(int i = 0; i < 1000; i++){
		int amount = 1000;    
	    ipTable * tables;
	    tables = malloc(amount * sizeof *tables);
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



}