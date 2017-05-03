/* 
 * File:   ipTable.h
 * Author: fogh
 *
 *Header file for ipTable struct and its methods. Ip tables are the units 
 * which are used for routing in the graph.
 */

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

//function to setup the table
void setupTable(ipTable * table);
//Function that sets the randomly generated address to IpTable struct. See randomAddressGenerator.h
void setAddress(int * netmask, int * mask, int * id, ipTable * table);
//function resets the ipTables visited field to 0 for new search
void resetSearch(ipTable * tables, int amount);

//free tables destinations
void freeDestinations(ipTable * tables, int size);
//print tables destinations
void printDestinations(ipTable * table);

#endif	

