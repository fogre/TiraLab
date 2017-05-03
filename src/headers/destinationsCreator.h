/* 
 * File:   destinationsCreator.h
 * Author: fogh
 *
 * Functions for setting ipTables destinations
 */

#ifndef DESTINATIONSCREATOR_H
#define	DESTINATIONSCREATOR_H
#include "ipTable.h"


/*Function to append a single destination for ipTable.
  See selectRandomDestinations and setDestinations
*/
void setSingleDestination(ipTable * table, ipTable * dest);

/*
  @param table: IpTable to set the destinations
  @param createdTables: Previously created tables
  @param numberOfCreated: Number of created tables
  @param numberToLink: Defines how many previously created tables are taken into account.
  Function sets 1-5 previously created ipTables to tables destinations. See setDestinations
*/
void selectRandomDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated, int numberToLink);

/*
  @param table: IpTable to set the destinations
  @param createdTables: Previously created tables
  @param numberOfCreated: Number of created tables
  Function sets random amount between 1-5 to tables destinations
*/
void setDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated);

#endif	/* DESTINATIONSCREATOR_H */