/* 
 * File:   router.h
 * Author: fogh
 * Functions to find a route in the network. 
 */

#ifndef ROUTER_H
#define	ROUTER_H

/*compares two addresses together and returns true if the other one is smaller. See getNextHop*/
static int addressComparison(int a, int b){
	if(b < a){
		return 1;
	}
	return 0;
}

/*Function checks if the next table is a dead end and if it is the destination. See getNextHop*/
static int checkNextTable(ipTable * nextTable, int submask, int id){
	if(nextTable->lengthOfDestinations > 1){ 
		return 1;
	}else if(nextTable->mask == submask && (nextTable->identifier == id)){
		printf("  deadend found it!!: %i\n", nextTable->identifier);
		return 1;
	}	
	printf("  deadend: %i\n", nextTable->identifier);
	return 0;
}

/*Adds one id to visitedTables and frees the place for the next one. See getNextHop */
static void addTableToVisited(int * visited, int id){
	for(int i = 0; i < 15; i++){
		if(visited[i] == 0 && i < 14){
			visited[i] = id;
			visited[i+1] = 0;
			break;
		}else if(i == 14) {
			visited[i] = id;
			visited[0] = 0;
			break;
		}
	}

}
/*checks if ID is previously visited and returns false if it is. See getNextHop*/
static int notInVisited(int * visited, int id){
	for(int i = 0; i < 15; i++){
		if(visited[i] == id){
			return 0;
		}
	}
	return 1;
}
//valitse aina 0 taulukosta seuraavan kappaleen!!
static ipTable * selectFromVisited(ipTable * table, int * visitedTables){
	for(int k = 0; k < 8; k++){}
}
/*
  @param start: where to start to look for the destination
  @param previouslyVisited: table of previously visited tables
  @param netmask, submask, identifier: address of the searched destination
  Gives the next hop where to look for the address. See traceRoute
*/
static ipTable * getNextHop(ipTable * table, int ** previouslyVisited, int netmask, int submask, int id){
	int currentnet = 1000, currentsub = 1000, currentid = 1000;
	int newnet, newsub, newid;
	ipTable * nextDestination = NULL; 
    for(int j = 0; j < table->lengthOfDestinations; j++){
    	//check if already visited and if its a dead end
    	printf("  current: %u\n", table->destinations[j]->identifier);
   		if(!checkNextTable(table->destinations[j], submask, id) ||
   			!notInVisited(*previouslyVisited, table->destinations[j]->identifier)){
   				continue;
   		}
   		newsub = submask - (table->destinations[j]->mask);
    	newid = id - (table->destinations[j]->identifier);
    	if(addressComparison(currentsub, newsub)){
    			currentsub = newsub;
    			currentid = newid;
    			nextDestination = table->destinations[j];
    	
    	}else if(addressComparison(currentid, newid)){
    			currentid = newid;
    			nextDestination = table->destinations[j];
    			printf("     table set: %u\n", nextDestination->identifier);
    	}
    }
    /*if nextDestination is still null, we can expect that all its destinations have been visited (it has a cycle).
      Thus we need to allocate a new search from previous table*/
    if(!nextDestination){
    	//currently not working properly:
    	nextDestination = table->destinations[0];
    }
    addTableToVisited(*previouslyVisited, table->identifier);
    printf("next destination is: 192.186.%u.%u\n", nextDestination->mask, nextDestination->identifier);
    return nextDestination;
}

/*
  @param start: where to start to look for the destination
  @param previouslyVisited: table of previously visited tables
  @param hopCount: how many hops to destinations should be done before disgarding the search
  @param netmask, submask, identifier: address of the searched destination
  A traceroute function that finds the route to given destination. Returns NULL if the destination is not found (Does not exist).
*/
static ipTable * traceRoute(ipTable * start, int ** previouslyVisited, int hopCount, int netmask, int submask, int identifier){
	ipTable * next = getNextHop(start, previouslyVisited, netmask, submask, identifier);
	if(!next){
		printf("next is null!\n");
		return NULL;
	}else if(hopCount <= 0){
		printf("not found! %i.%i\n", submask, identifier);
		return NULL;
	}else if(next->mask == submask && (next->identifier == identifier)){
		printf("address found! %i.%i\n", submask, identifier);
		return next;
	}else{
		hopCount--;
		next = findRoute(next, previouslyVisited, hopCount, netmask, submask, identifier);
	}
}

#endif	/* ROUTER_H */