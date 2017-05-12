/* 
 * File:   ipTable.h
 * Author: fogh
 *
 * Object file ipTable struct and its methods. Ip tables are the units 
 * which are used for routing in the graph.
 */


#include <stdio.h>
#include <stdlib.h>
#include "./headers/ipTable.h"
#include "./headers/randomAddressGenerator.h"
#include "./headers/destinationsCreator.h"

//function to setup the table
void setupTable(ipTable * table){
    table->visited=0;
	table->lengthOfDestinations=0;
	table->destinations = NULL;
}

//Function that sets the randomly generated address to IpTable struct. See randomAddressGenerator.h
void setAddress(int * netmask, int * mask, int * id, ipTable * table){
    randomAddressGenerator(netmask, mask, id);
    table->netmask = *netmask;
    table->mask = *mask;
    table->identifier = *id;
}

//function resets the ipTables visited field to 0 for a new search
void resetSearch(ipTable * tables, int amount){
        for(int i = 0; i < amount; i++){
            tables[i].visited = 0;
    }
}

//free tables destinations
void freeDestinations(ipTable * tables, int size){
    for(int i = 0; i < size; i++){
        free(tables[i].destinations);
    }

}

/*function creates a network of amount nodes.
  The destinations are set by setDestinations function located in destinationsCreator.c*/
void createNetwork(ipTable ** tbls, int amount){
    ipTable * tables = *tbls;
    int addressNetmask = 168;
    int addressMask = 0;
    int addressId = 1;
    tables[0].netmask = addressNetmask;
    tables[0].identifier = addressId;
    tables[0].mask = addressMask;
    setupTable(&tables[0]);
    //create network:
    for(int i = 1; i < amount; i++){
        setupTable(&tables[i]);
        setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
        setDestinations(&tables[i],tables, i);
    }
    tables = NULL;
    free(tables);
}


//print tables destinations, used only for debugging
void printDestinations(ipTable * table){
    printf("%lu Destinations for 192.168.%u.%u:\n",table->lengthOfDestinations, table->mask, table->identifier);
    for(int j = 0; j < table->lengthOfDestinations; j++){
        printf("    %u.%u\n", table->destinations[j]->mask, table->destinations[j]->identifier);
    }
}
