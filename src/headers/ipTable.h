/* 
 * File:   ipTable.h
 * Author: fogh
 *
 *Header file for ipTable struct and its methods. Ip tables are the units 
 * which are used for routing in the graph. For now th
 */
#include "randomAddressGenerator.h"

#ifndef IPTABLE_H
#define	IPTABLE_H

/* Forward declaration */
struct ipTableTag;
//Defining the ipTable structure
typedef struct ipTableTag{
    
    //Address is "192.netmask.mask.identifier"
    unsigned int netmask;
    unsigned int mask;
    unsigned int identifier;
    //length of destinations array
    size_t lengthOfDestinations;
    //pointer array to reachable destinations
    struct ipTableTag **destinations;
    //char "integer" used for routing purposes. 0=unvisited, 1 = visited once, 2 = visited twice, 3 = deadend;
    char visited;
    
}ipTable;

//function ot setup the table in tableCreator.h
static void setupTable(ipTable * table){
    table->netmask=168;
    table->visited=0;
	table->lengthOfDestinations=0;
	table->destinations = NULL;
}

//Function that sets the randomly generated address to IpTable struct. See randomAddressGenerator.h
static void setAddress(int * mask, int * id, ipTable * table){
    randomAddressGenerator(mask, id);
    table->mask = *mask;
    table->identifier = *id;
}

//free tables destinations
static void freeDestinations(ipTable * tables, int size){
    for(int i = 0; i < size; i++){
        free(tables[i].destinations);
    }

}
//print tables destinations
static void printDestinations(ipTable * table){
    printf("%lu Destinations for 192.168.%u.%u:\n",table->lengthOfDestinations, table->mask, table->identifier);
    for(int j = 0; j < table->lengthOfDestinations; j++){
        printf("    %u.%u\n", table->destinations[j]->mask, table->destinations[j]->identifier);
    }
}

#endif	

