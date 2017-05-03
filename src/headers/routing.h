/* 
 * File:   routing.h
 * Author: fogh
 * Functions to find a route in the network. 
 */

#ifndef ROUTING_H
#define	ROUTING_H

#include "ipTable.h"

//Function to check if the address is the searched destination
int checkIfRightAddress(ipTable * table, int netB, int maskB,int idB);

/*Function checks if the next table is visited, a dead end or if it is the right destination. See getNextHop*/
int checkNextTable(ipTable * nextTable, int netmask, int mask,int id);
/*
  @param table: table where to look the next hop
  @param int net, mask, id: address of the searched destination
  Gives the next hop where to look for the address and returns if the right one is found.
*/
ipTable * getNextHop(ipTable * table, int net, int mask, int id);
/*
  @param start: where to start to look for the destination
  @param hopCount: how many hops to destinations should be done before disgarding the search
  @param netmask, submask, identifier: address of the searched destination
  A traceroute function that finds the route to given destination. Returns NULL if the destination is not found ( = does not exist).
*/
ipTable * traceRoute(ipTable* start, int hopCount, int netmask, int submask, int identifier);

#endif	/* ROUTING_H */