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
#include "./headers/router.h"


int main(int argc, char** argv) {

	srand(time(NULL));
	int amount = 200;    
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
    int idl = tables[amount-1].identifier;
    int subl = tables[amount-1].mask;
   	for(int x = 0; x < amount; x++){
   		printDestinations(&tables[x]);
   	}
    int * visited = malloc(15* sizeof(int));
    for(int x = 0; x < 15; x++){
      visited[x] = 0;
    }
    ipTable * destination = traceRoute(&tables[0], &visited, 2000, 168, subl, idl);
    printf("address: %i\n", idl);

    for(int z = 0; z < 15; z++){
     printf("visited: %i\n", visited[z]);
    }

    free(tables);
    
    return (EXIT_SUCCESS);
}

