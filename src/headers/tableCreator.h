/* 
 * File:   tableCreator.h
 * Author: fogh
 *
 * Creates and array of specific sized IP tables. This is used to create the
 * network
 */
#include "ipTable.h"
#include "randomAddressGenerator.h"
#include "destinationsCreator.h"

#ifndef TABLECREATOR_H
#define	TABLECREATOR_H

/*
  @param amount: number of iptables to be created
  @param ipTables: array of ipTable structures
  Function to create the array of ipTable structures with randomly given IP
  addresses*/
static void createTables(size_t amount, ipTable ** ipTables){
   /*
    ipTables = malloc(amount * sizeof *ipTables);
    if(!ipTables){
        printf("Allocating ipTables failed! Exiting 1!\n");
        exit(EXIT_FAILURE);
    }
    /* Setting up the default variables for the addresses and first table 
     * 192.168.0.1*/
    int addressMask = 0;
    int addressId = 1;
    ipTables[0]->identifier = addressId;
    ipTables[0]->mask = addressMask;
    setupTable(ipTables[0]);
    //create tables:
    for(int i = 1; i < amount; i++){
        printf("%i\n", i);
        setupTable(ipTables[0]);
        setAddress(&addressMask, &addressId, ipTables[i]);
        setDestinations(ipTables[i], *ipTables, i);
    }
}

#endif	/* TABLECREATOR_H */

