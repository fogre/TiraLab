/* 
 * File:   main.c
 * Author: fogh
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "./headers/ipTable.h"
#include "./headers/destinationsCreator.h"
#include "./headers/routing.h"

/*function to check if the command line argument is a positive number with given range*/
static int isUnsignedNumber(char number[]){
  //checking for negative numbers or if the first digit is zero
  if(number[0]=='-' || (number[0]=='0')){
      return 0;
  }//checking if the rest are between 0-9 and that the number is under 10 million
  for (int i = 0; number[i] != '\0'; i++){
      if(!isdigit(number[i])){
          return 0;
      }
      if(i > 6){
        return 0;
      }    
  }
  return 1; 
}

/*function to get a next line from stdin. Used for address search */
static int getLine(char *prmpt, char *buff, size_t sz){
    int ch, extra = 0;
    // Get line with buffer overrun protection.
    if(prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    fgets(buff, sz, stdin);
    //Empty line, exit.
    if(buff[0] == '\n'){
        return 5;
    }// If it was too long, there'll be no newline. In that case, we flush to end of line so that excess doesn't affect the next call.
    if(buff[strlen(buff)-1] != '\n') {
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? 0 : 1;
    }
    //Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return 1;
}    
 

int main(int argc, char** argv) {

  int amount = 100000;
  //if command line argument given, validate it
  if(argc > 1){
    if(!isUnsignedNumber(argv[1])){
      printf("Only the first command line argument is taken into account and it should be a positive integer between 100-1200000!\nExiting\n");
      return (EXIT_FAILURE);
    }
    amount = atoi(argv[1]);
    if(amount < 100 || amount > 1200000){
      printf("The number of nodes in the network to be created should be between 100-1200000!\nExiting\n");
      return (EXIT_FAILURE);
    }
  }
  //init network creation:
  printf("> Creating a network with %i nodes...\n", amount);
  srand(time(NULL));
  ipTable * tables = malloc(amount * sizeof *tables);
  if(!tables){
      printf("Allocating tables failed!\n");
      exit(EXIT_FAILURE);
  }//init addresses and first table:
  int addressNetmask = 168;
  int addressMask = 0;
  int addressId = 1;
  tables[0].netmask = addressNetmask;
 	tables[0].identifier = addressId;
 	tables[0].mask = addressMask;
  setupTable(&tables[0]);
  //create network:
  for(int i = 1; i < amount; i++){
      setupTable(&tables[i]);
      setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
      setDestinations(&tables[i],tables, i);
  }
  //init traceRouting
  int net=-1, mask=-1, id=-1, option;
  char addressToLook[5];
  ipTable * destination = NULL;
  //Search for an destination in the network or exit:
  while(option != 5){
   option = 1;
   printf("\n> A network of %i nodes created with addresses between 168.0.1-%u.%u.%u (netmask.submask.identifier)\n", 
         amount, tables[amount-1].netmask, tables[amount-1].mask, tables[amount-1].identifier);
   printf("> Search for a destination in the network by giving the netmask, submask, and indentifier separately.\n");
   printf("> Exit by giving an empty line (press enter)\n\n"); 

   switch(option){

    case 1://ask for netmask and check if it's valid
      option = getLine("> Give the netmask address> ", addressToLook, sizeof(addressToLook));
      if(option == 1){
        if(isUnsignedNumber(addressToLook)){
          net = atoi(addressToLook);
          if(net < tables[0].netmask || net > tables[amount-1].netmask){
            printf("\n\n\nThe given netmask address is not within the created address space!\n");
            break;
          }
        }else{
          printf("\n\n\nInvalid netmask address!\n");
          break;
        }
      }else if(option == 5){  
        break;
      }else{
      printf("\n\n\nNot a valid netmask address!\n"); 
      break;
      }

    case 2://ask for submask and check if it's valid
      option = getLine("> Give the submask address> ", addressToLook, sizeof(addressToLook));
      if(option == 1){
        if(isUnsignedNumber(addressToLook) || ((strlen(addressToLook) == 1) && addressToLook[0]=='0') ){
          mask = atoi(addressToLook);
          if(mask < 0 || mask > 999){
            printf("\n\n\nThe given mask address is not within the created address space.\n");
            break;
          }
        }else{
          printf("\n\n\nInvalid mask address!\n");
          break;
        }
      }else if(option == 5){ 
        option = 1;
        break;
      }else{
      printf("\n\n\nNot a valid mask address!\n");
      break;
      }

    case 3://ask for identifier and check if it's valid
      option = getLine("> Give the identifier address> ", addressToLook, sizeof(addressToLook));
      if(option == 1){
          if(isUnsignedNumber(addressToLook)){
            id = atoi(addressToLook);
            if(id < 1 || id > 999){
              printf("\n\n\nThe given netmask address is not within the created address space.\n");
              break;
            }//search for the given destination:
              printf("\n> Starting tracerouting...\n\n");
              destination = traceRoute(&tables[0], amount, net, mask, id);
              resetSearch(tables, amount);
          }else{
            printf("\n\n\nInvalid identifier address!\n");
            break;
          }
      }else if(option == 5){
        option = 1; 
        break;
      }else{
        printf("\n\n\nNot a valid identifier address!\n");
        break;
      }
   }//end switch(option)   
  }//end while
  destination = NULL;
  freeDestinations(tables, amount);
  free(tables);
  return (EXIT_SUCCESS);
}