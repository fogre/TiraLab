/* 
 * File:   tableCreator.h
 * Author: fogh
 *
 * Creates and array of specific sized IP tables. This is used to create the
 * network
 */
#include <math.h>
#include "ipTable.h"

#ifndef TABLECREATOR_H
#define	TABLECREATOR_H


/*Function to create the array of ipTable structures with randomly given IP
  addresses*/
void createTables(unsigned int amount, ipTable * ipTables){
    
    ipTables = malloc(amount * sizeof *ipTables);
    int i;
    for(i = 0; i < amount; i++){
        //function to create
        ipTables[i].ipAddress = "192.168.000.00";
        printf("%s\n", ipTables[i].ipAddress);
    }
}


//Function to create random address paces
void createAddress(int submask, int indentifier ){
    
    
}


#endif	/* TABLECREATOR_H */

