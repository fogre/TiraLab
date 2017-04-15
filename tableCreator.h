/* 
 * File:   tableCreator.h
 * Author: fogh
 *
 * Creates and array of specific sized IP tables. This is used to create the
 * network
 */
#include "ipTable.h"
#include "randomAddressGenerator.h"

#ifndef TABLECREATOR_H
#define	TABLECREATOR_H


/*Function to create the array of ipTable structures with randomly given IP
  addresses*/
static void createTables(unsigned int amount, ipTable * ipTables){
    
    ipTables = malloc(amount * sizeof *ipTables);
    /* Setting up the default variables for the addresses and first table 
     * 192.168.0.1*/
    int defaultMask = 0;
    int defaultId = 1;
    ipTables[0].identifier = defaultId;
    ipTables[0].mask = defaultMask;
    int * maskAddress = &defaultMask;
    int * idAddress = &defaultId;
    //create tables:
    int i;
    for(i = 1; i < amount; i++){
        setAddress(maskAddress, idAddress, &ipTables[i]);
        //printf("%d th address is: %d . %d\n", i, ipTables[i].mask, ipTables[i].identifier);
    }
}

#endif	/* TABLECREATOR_H */

