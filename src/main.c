/* 
 * File:   main.c
 * Author: fogh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "./headers/tableCreator.h"
#include "./headers/ipTable.h"


int main(int argc, char** argv) {

	srand(time(NULL));
	int amount = 55;    
    ipTable * tables;
    int index = 5;

    tables = malloc(amount * sizeof *tables);
    if(!tables){
        printf("Allocating tables failed!\n");
        exit(EXIT_FAILURE);
    }
	//createTables(amount, &tables);
    /* Setting up the default variables for the addresses and first table 
     * 192.168.0.1*/
    
    int addressMask = 0;
    int addressId = 1;
   	tables[0].identifier = addressId;
   	tables[0].mask = addressMask;
    setupTable(&tables[0]);
    //create tables:
    for(int i = 1; i < amount; i++){
        setupTable(&tables[i]);
        setAddress(&addressMask, &addressId, &tables[i]);
        setDestinations(&tables[i],tables, i);
    }

   	for(int x = 0; x < amount; x++){
   		//printf("asd\n");
   		printDestinations(&tables[x]);
   	}
    
    free(tables);
    
    return (EXIT_SUCCESS);
}

