/* 
 * File:   ipTable.h
 * Author: fogh
 *
 *Header file for ipTable struct and its methods. Ip tables are the units 
 * which are used for routing in the graph. For now th
 */

#include "ipTableRoutingCell.h"

#ifndef IPTABLE_H
#define	IPTABLE_H

/* Forward declaration */
struct ipTableTag;
//Defining the ipTable structure
typedef struct ipTableTag{
    
    //Address is "192.168.mask.identifier"
    unsigned int mask;
    unsigned int identifier;
    //length of destinations array
    size_t lengthOfDestinations;
    //pointer array to reachable destinations
    struct ipTableTag **destinations;
    
}ipTable;

//function ot setup the table in tableCreator.h
static void setupTable(ipTable * table){
	table->lengthOfDestinations=0;
	table->destinations = NULL;
}

static void printDestinations(ipTable * table){
    printf("%lu Destinations for 192.168.%u.%u:\n",table->lengthOfDestinations, table->mask, table->identifier);
    for(int j = 0; j < table->lengthOfDestinations; j++){
        printf("    %u.%u\n", table->destinations[j]->mask, table->destinations[j]->identifier);
    }
}

static void printDestinationsT(ipTable table){
    printf("%lu Destinations for 192.168.%u.%u:\n",table.lengthOfDestinations, table.mask, table.identifier);
    for(int j = 0; j < table.lengthOfDestinations; j++){
        printf("    %u.%u\n", table.destinations[j]->mask, table.destinations[j]->identifier);
    }
}    


#endif	

