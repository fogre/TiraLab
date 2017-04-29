/* 
 * File:   routing.h
 * Author: fogh
 * Functions to find a route in the network. 
 */

#ifndef ROUTING_H
#define	ROUTING_H


//Function to check if the address is the destination
static int checkIfRightAddress(ipTable * table,int maskB,int idB){
	if(table->mask == maskB && table->identifier == idB){
	   return 1;
	}
	return 0;    
}

/*Compares two ints together and returns true, if b is smaller and bigger than zero. 
  Used to choose next address. See getNextHop*/
static int addressComparison(int a, int b){
	if(b <= a && (b >= 0)){
		return 1;
	}
	return 0;
}

/*Function checks if the next table is visited, a dead end or if it is the right destination. See getNextHop*/
static int checkNextTable(ipTable * nextTable, int mask,int id){	
	if(nextTable->visited == 3){
		return 0;
	}else if(nextTable->visited == 1){
		return 1;
	}else if(nextTable->visited == 2){ 
		return 2;
	}else if(addressComparison(mask, nextTable->mask) && nextTable->lengthOfDestinations > 1){
		return 4;
	}else if(checkIfRightAddress(nextTable, mask, id)){
		return 4;
	}//nextTable is a dead end
	nextTable->visited=3;	
	return 0;
}
/*
  @param table: table where to look the next hop
  @param int net, mask, id: address of the searched destination
  Int indexOfLastVisited: index of the biggest once visited destination 
  Int indexOfLastDead: index of the biggest twice visited table (which is a dead end)
  Gives the next hop where to look for the address. See traceRoute
*/
static ipTable * getNextHop(ipTable * table, int net, int mask, int id){
	int checker, indexOflastVisited=-1, indexOfLastDead = -1;
	ipTable * nextDestination = NULL; 
	for(int j = 0; j < table->lengthOfDestinations; j++){
		checker = checkNextTable(table->destinations[j], mask, id);
		if(!checker){
			continue;
		}else if(checker == 1){
			indexOflastVisited = j;
			continue;
		}else if(checker == 2){
			indexOfLastDead = j;
			continue;
		}//unvisited child found, return if it is the right address:
    	nextDestination = table->destinations[j];
    	if(checkIfRightAddress(nextDestination, mask, id)){
    		return nextDestination;
    	}
	}/*if nextDestination is still null, tables all destinations have been visited (there is a cycle).*/
	if(!nextDestination && (indexOflastVisited >=0)){
		table->visited=2;//set table is visited twice
		return table->destinations[indexOflastVisited];
	}/*the table and its childs are a dead ends, head to once previously visited table:*/
	if(!nextDestination){
		table->visited=3;//set table is a dead end
		if(indexOfLastDead == -1){
			return table->destinations[0];
		}
		return table->destinations[indexOfLastDead];
   	}/*unvisited child found, set table to visited once and return unvisited child:*/
   	table->visited=1;//set table is visited once
   	return nextDestination;
}
/*
  @param start: where to start to look for the destination
  @param hopCount: how many hops to destinations should be done before disgarding the search
  @param netmask, submask, identifier: address of the searched destination
  A traceroute function that finds the route to given destination. Returns NULL if the destination is not found ( = does not exist).
*/
static ipTable * traceRoute(ipTable* start, int hopCount, int netmask, int submask, int identifier){
	ipTable * next = start;
	for(int h = 0; h < hopCount; h++){
		next = getNextHop(next, netmask, submask, identifier);
		if(!next){//Break in case something goes wrong
			printf("next is null!\n");
			return NULL;
		}if(checkIfRightAddress(next, submask, identifier)){
			printf("address found! %i.%i   | hopcount: %i\n", submask, identifier, h+1);
			return next;
		}
		printf("next destination is: 192.186.%u.%u\n", next->mask, next->identifier);
	}
	printf("not found! %i.%i | hopcount: %i\n", submask, identifier, hopCount);
	return NULL;
}


#endif	/* ROUTING_H */