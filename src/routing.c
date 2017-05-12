/* 
 * File:   routing.c
 * Author: fogh
 * Functions to find a route in the network. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "./headers/routing.h"

//Function to check if the address is the searched destination
int checkIfRightAddress(ipTable * table, int netB, int maskB,int idB){
	if(table->netmask == netB && table->mask == maskB && table->identifier == idB){
	   return 1;
	}
	return 0;    
}

/*Function checks if the next table is visited, under the searched value, 
  a dead end or in that case if it is the right destination. See getNextHop*/
int checkNextTable(ipTable * nextTable, int netmask, int mask,int id){	
	if(nextTable->visited == 3){
		return 0;
	}else if(nextTable->visited == 1){
		return 1;
	}else if(nextTable->visited == 2){ 
		return 2;
	}else if(nextTable->netmask < netmask && (nextTable->lengthOfDestinations > 1)){
		return 4;	
	}else if(nextTable->mask < mask && (nextTable->lengthOfDestinations > 1)){
		return 4;
	}else if(nextTable->mask == mask && (nextTable->identifier <= id) && (nextTable->lengthOfDestinations > 1)){
		return 4;
	}else if(checkIfRightAddress(nextTable, netmask, mask, id)){
		return 4;
	}//nextTable is a dead end
	nextTable->visited=3;	
	return 0;
}
/*
  @param table: table where to look the next hop
  @param int net, mask, id: address of the searched destination
  Int indexOfLastVisited: index of the biggest once visited destination 
  Int indexOfLastDead: index of the biggest twice visited table (which is a dead end, but sometimes we have to go back)
  Gives the next hop where to look for the address and returns if the right one is found.
  The algorithm moves hungrily forward until it ends up with a table where the netmask or mask is bigger than the one looked, 
  and then heads back if necessary. See traceRoute
*/
ipTable * getNextHop(ipTable * table, int net, int mask, int id){
	int checker, indexOflastVisited=-1, indexOfLastDead = -1, amountOfUnvisited=0;
	ipTable * nextDestination = NULL; 
	for(int j = 0; j < table->lengthOfDestinations; j++){
		checker = checkNextTable(table->destinations[j], net , mask, id);
		if(!checker){
			continue;
		}else if(checker == 1){
			indexOflastVisited = j;
			continue;
		}else if(checker == 2){
			indexOfLastDead = j;
			continue;
		}//unvisited "child" found, check if it is the destination:
		amountOfUnvisited++;
    	nextDestination = table->destinations[j];
    	if(checkIfRightAddress(nextDestination, net, mask, id)){
    		return nextDestination;
    	}
	}/*if nextDestination is still null, tables all destinations have been visited (there is a cycle).*/
	if(!nextDestination && (indexOflastVisited >=0)){
		table->visited=2;//set table is visited twice
		if(table)
		free(nextDestination);
		return table->destinations[indexOflastVisited];
	}/*the table is a dead end, head back to a twice previously visited table:*/
	if(!nextDestination){
		table->visited=3;//set table is a dead end
		if(indexOfLastDead == -1){
			free(nextDestination);
			return table->destinations[0];
		}
		free(nextDestination);
		return table->destinations[indexOfLastDead];
   	}/*unvisited child found.
 	  Set visited to 1 or 2 if it has only one unvisited child and return the unvisited child:*/

    table->visited=1;
   	return nextDestination;
}
/*
  @param start: where to start to look for the destination
  @param hopCount: how many hops to destinations should be done before disgarding the search
  @param netmask, submask, identifier: address of the searched destination
  A traceroute function that finds the route to given destination. Returns NULL if the destination is not found ( = does not exist).
*/
ipTable * traceRoute(ipTable* start, int hopCount, int netmask, int submask, int identifier){
	ipTable * next = start;
	for(int h = 0; h < hopCount; h++){
		next = getNextHop(next, netmask, submask, identifier);
		if(!next){//Break in case something goes wrong
			printf("next is null!\n");
			free(next);
			return NULL;
		}if(checkIfRightAddress(next, netmask, submask, identifier)){
			printf("address found! %i.%i.%i   | hopcount: %i\n", netmask, submask, identifier, h+1);
			return next;
		}
		printf("next destination is: %u.%u.%u\n",next->netmask, next->mask, next->identifier);
	}
	next = NULL;
	free(next);
	printf("not found (the address doesent exist)! %i.%i.%i | hopcount: %i\n",netmask, submask, identifier, hopCount);
	return NULL;
}