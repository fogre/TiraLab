/*
 * Program effiency tests
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/destinationsCreator.h"
#include "../src/headers/routing.h"

int main(int argc, char** argv) {
  //init
  clock_t startTime = clock();
  clock_t begin = clock();
  srand(time(NULL));
  int amount = 1000000;
  ipTable * tables;
  tables = malloc(amount * sizeof *tables);
  if(!tables){
      printf("Allocating tables failed!\n");
      exit(EXIT_FAILURE);
  }//set addresses and create tables
  int addressNetmask = 168;
  int addressMask = 0;
  int addressId = 1;
  tables[0].netmask = addressNetmask;
  tables[0].identifier = addressId;
  tables[0].mask = addressMask;
  setupTable(&tables[0]);
  for(int i = 1; i < amount; i++){
      setupTable(&tables[i]);
      setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
      setDestinations(&tables[i],tables, i);
  }
  clock_t end = clock();
  double time_of_table_creation = (double)(begin - end) / CLOCKS_PER_SEC;
  

  //count time it takes to find the last table with traceRoute function
  begin = clock();
  ipTable * destination = traceRoute(&tables[0], amount, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
  end = clock();
  double time_of_finding_last_table_traceroute = (double)(begin - end) / CLOCKS_PER_SEC;
  resetSearch(tables, amount);

  //count time it takes to find the random table with traceRoute function
  int random1 = rand() % amount;
  begin = clock();
  destination = traceRoute(&tables[0], amount, tables[random1].netmask, tables[random1].mask, tables[random1].identifier);
  end = clock();
  double time_of_finding_random_table_traceroute1 = (double)(begin - end) / CLOCKS_PER_SEC;
  resetSearch(tables, amount);

  //count time it takes to find the last random with traceRoute function
  int random2 = rand() % amount;
  begin = clock();
  destination = traceRoute(&tables[0], amount, tables[random2].netmask, tables[random2].mask, tables[random2].identifier);
  end = clock();
  double time_of_finding_random_table_traceroute2 = (double)(begin - end) / CLOCKS_PER_SEC;
  


  freeDestinations(tables, amount);
  free(tables);

  clock_t endTime = clock();
  double total_time_spent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("time to create 1000000 tables and set destinations: %fs\n", time_of_table_creation);
  printf("time of finding last table with traceroute: %fs\n", time_of_finding_last_table_traceroute);
  printf("time of finding first random table %i table with traceroute: %fs\n", random1, time_of_finding_random_table_traceroute1);
  printf("time of finding second random table %i table with traceroute: %fs\n", random2, time_of_finding_random_table_traceroute1);
  printf("Total time spent: %fs\n", total_time_spent);

  return (EXIT_SUCCESS);
}

