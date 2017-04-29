/* 
 * File:   main.c
 * Author: fogh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "./headers/ipTable.h"
#include "./headers/routing.h"
#include "./headers/destinationsCreator.h"


int main(int argc, char** argv) {

  srand(time(NULL));
  int amount = 52000;    
  ipTable * tables;

  tables = malloc(amount * sizeof *tables);
  if(!tables){
      printf("Allocating tables failed!\n");
      exit(EXIT_FAILURE);
  }
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
  int random = rand() % amount;
  int idl = tables[random].identifier;
  int subl = tables[random].mask;
  ipTable * destination = traceRoute(&tables[0], amount, 168, tables[amount-1].mask, tables[amount-1].identifier);
  freeDestinations(tables, amount);
  free(tables);
  
  return (EXIT_SUCCESS);
}

