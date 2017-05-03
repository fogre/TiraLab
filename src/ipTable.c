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

//function resets the ipTables visited field to 0 for new search
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
//print tables destinations
void printDestinations(ipTable * table){
    printf("%lu Destinations for 192.168.%u.%u:\n",table->lengthOfDestinations, table->mask, table->identifier);
    for(int j = 0; j < table->lengthOfDestinations; j++){
        printf("    %u.%u\n", table->destinations[j]->mask, table->destinations[j]->identifier);
    }
}

