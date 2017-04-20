/* 
 * File:   destinationsCreator.h
 * Author: fogh
 *
 * Functions for setting ipTables destinations
 */

#ifndef DESTINATIONSCREATOR_H
#define	DESTINATIONSCREATOR_H

/*Function to append a single destination for ipTable.
  See selectRandomDestinations and setDestinations
*/
static void setSingleDestination(ipTable * table, ipTable * dest){
	int index = table->lengthOfDestinations;
	table->destinations = realloc(table->destinations, (index+1) * sizeof(ipTable *));
	if(!table->destinations){
		printf("Reallocating destinations failed! Exiting 1!\n");
		exit(EXIT_FAILURE);
	}
	table->destinations[index] = dest;
	table->lengthOfDestinations = index+1;
}

/*
  @param table: IpTable to set the destinations
  @param createdTables: Previously created tables
  @param numberOfCreated: Number of created tables
  @param numberToLink: Defines how many previously created tables are taken into account.
  Function sets 1-4 previously created ipTables to tables destinations. See setDestinations
*/
static void selectRandomDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated, int numberToLink){
	int random;
	int numberOfLinks = 0;
	int base = numberOfCreated-numberToLink;
	for(int j = 0; j < numberToLink; j++){
		random = rand() % 10+1;
		if(random > 7){
			setSingleDestination(table, &createdTables[base+j]);
			setSingleDestination(&createdTables[base+j], table);
			numberOfLinks++;
		}
		if(numberOfLinks > 3){
			break;
		}
	}
	//in case after the for there aren't any destinations set, we set one
	if(numberOfLinks == 0){
		random = rand() % numberToLink+1;
		setSingleDestination(table, &createdTables[base+random-1]);
		setSingleDestination(&createdTables[base+random-1], table);
	}
}

/*
  @param table: IpTable to set the destinations
  @param createdTables: Previously created tables
  @param numberOfCreated: Number of created tables
  Function sets random amount between 1-4 ipRoutingTableCells to tables destinations
*/
static void setDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated){
	int numberToLink = 5;
	//If there are fewer than numberToLink tables created, we need to limit the link amount 
	if(numberOfCreated <= numberToLink){
		selectRandomDestinations(table, createdTables, numberOfCreated, numberOfCreated);
	}else{
		//numberOfCreated more than numberToLink tables:
		selectRandomDestinations(table, createdTables, numberOfCreated, numberToLink);
	}
}

#endif	/* DESTINATIONSCREATOR_H */