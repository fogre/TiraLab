/*
  The program sets 20 times a network of 10, 100, 1000, 10000, 100000 and million nodes.
  Then it searches path to amount/4, amount/2 and to last table and
  calculates hop count for each.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/destinationsCreator.h"
#include "../src/headers/routing.h"

int main(int argc, char** argv) {
 
  
  int hopCountOneFourth, hopCountMiddle, hopCountLast;
  //These could be an array but.... works like this as well :D
  double hundredFirst=0, hundredMiddle=0, hundredLast=0;
  double thousandFirst=0, thousandMiddle=0, thousandLast=0;
  double tThousandFirst=0, tThousandMiddle=0, tThousandLast=0;
  double hThousandFirst=0, hThousandMiddle=0, hThousandLast=0;
  double millionFirst=0, millionMiddle=0, millionLast=0;
  double hTime = 0, thTime=0, tthTime=0, hthTime=0, mTime=0;
  int amount, h, index;

  srand(time(NULL));

  for(int z = 0; z < 20; z++){
   amount = 100;
   while(amount <= 1000000){
   	printf("counting amount %i on iteration %i...\n", amount, z+1);
   	//init tables
   	clock_t begin = clock();
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
	//Search first address: This is a copy of traceroute function. 
	//We need to have a copy so we can get the hop count, and for now im too lazy to code otherwise :/  
	ipTable * next = &tables[0];
	index = (int) amount/4;
	for(h = 0; h < amount; h++){
		next = getNextHop(next, tables[index].netmask, tables[index].mask, tables[index].identifier);
		if(!next){//Break in case something goes wrong
			printf("next is null!\n");
			return (EXIT_FAILURE);
		}if(checkIfRightAddress(next, tables[index].netmask, tables[index].mask, tables[index].identifier)){
			hopCountOneFourth = h;
			break;
		}
	}
	if(h >= amount){
		printf("Failure! %i %i\n", index,h);
		return (EXIT_FAILURE);
	}
	resetSearch(tables, amount);

	//search middle address
	next = &tables[0];
	index = (int) amount/2;
	for(h = 0; h < amount; h++){
		next = getNextHop(next, tables[index].netmask, tables[index].mask, tables[index].identifier);
		if(!next){//Break in case something goes wrong
			printf("next is null!\n");
			return (EXIT_FAILURE);
		}if(checkIfRightAddress(next, tables[index].netmask, tables[index].mask, tables[index].identifier)){
			hopCountMiddle = h;
			break;
		}
	}
	if(h >= amount){
		printf("Failure! %i %i\n", index,h);
		return (EXIT_FAILURE);
	}
	resetSearch(tables, amount);

	//search last address
	next = &tables[0];
	index = amount-1;
	for(h = 0; h < amount; h++){
		next = getNextHop(next, tables[index].netmask, tables[index].mask, tables[index].identifier);
		if(!next){//Break in case something goes wrong
			printf("next is null!\n");
			return (EXIT_FAILURE);
		}if(checkIfRightAddress(next, tables[index].netmask, tables[index].mask, tables[index].identifier)){
			hopCountLast = h;
			break;
		}
	}
	if(h >= amount){
		printf("Failure! %i %i\n", index,h);
		return (EXIT_FAILURE);
	}

	next = NULL;
	free(next);
	freeDestinations(tables, amount);
	free(tables);
	//add to average count:
	switch(amount){

		case 100:
		  hundredFirst += hopCountOneFourth;
		  hundredMiddle += hopCountMiddle;
		  hundredLast += hopCountLast;
		  hTime += (double)(begin - end) / CLOCKS_PER_SEC;
		  break;

		case 1000:
		  thousandFirst += hopCountOneFourth;
		  thousandMiddle += hopCountMiddle;
		  thousandLast += hopCountLast;
		  thTime += (double)(begin - end) / CLOCKS_PER_SEC;
		  break;

		case 10000:
		  tThousandFirst += hopCountOneFourth;
		  tThousandMiddle += hopCountMiddle;
		  tThousandLast += hopCountLast;
		  tthTime += (double)(begin - end) / CLOCKS_PER_SEC;
		  break;

		case 100000:
		  hThousandFirst += hopCountOneFourth;
		  hThousandMiddle += hopCountMiddle;
		  hThousandLast += hopCountLast;
		  hthTime += (double)(begin - end) / CLOCKS_PER_SEC;
		  break;

		case 1000000:
		  millionFirst += hopCountOneFourth;
		  millionMiddle += hopCountMiddle;
		  millionLast += hopCountLast;
		  mTime += (double)(begin - end) / CLOCKS_PER_SEC;
		  break;
	}
	amount = amount * 10;

   }//endwhile
  }//endfor
  //calculate averages and print:
  hundredFirst = hundredFirst/20;
  hundredMiddle= hundredMiddle/20;
  hundredLast = hundredLast/20;
  thousandFirst = thousandFirst/20;
  thousandMiddle = thousandMiddle/20;
  thousandLast = thousandLast/20;
  tThousandFirst = tThousandFirst/20;
  tThousandMiddle = tThousandMiddle/20;
  tThousandLast = tThousandLast/20;
  hThousandFirst = hThousandFirst/20;
  hThousandMiddle = hThousandMiddle/20;
  hThousandLast = hThousandLast/20;
  millionFirst = millionFirst/20;
  millionMiddle = millionMiddle/20;
  millionLast = millionLast/20;
  hTime = hTime/20;
  thTime = thTime/20;
  tthTime = tthTime/20;
  hthTime = hthTime/20;
  mTime = mTime/20;
  printf("\nAverage hop counts to nodes amount/4, amount/2, amount-1:\n");
  printf("Time to create 100 tables: %f\n", hTime);
  printf("average 100 first: %f\n", hundredFirst);
  printf("average 100 middle: %f\n", hundredMiddle);
  printf("average 100 last: %f\n\n", hundredLast);

  printf("Time to create 1000 tables: %f\n", thTime);
  printf("average 1000 first: %f\n", thousandFirst);
  printf("average 1000 middle: %f\n", thousandMiddle);
  printf("average 1000 last: %f\n\n", thousandLast);

  printf("Time to create 10000 tables: %f\n", tthTime);
  printf("average 10000 first: %f\n", tThousandFirst);
  printf("average 10000 middle: %f\n", tThousandMiddle);
  printf("average 10000 last: %f\n\n", tThousandLast);

  printf("Time to create 100000 tables: %f\n", hthTime);
  printf("average 100000 first: %f\n", hThousandFirst);
  printf("average 100000 middle: %f\n", hThousandMiddle);
  printf("average 100000 last: %f\n\n", hThousandLast);

  printf("Time to create 1000000 tables: %f\n", mTime);
  printf("average 1000000 first: %f\n", millionFirst);
  printf("average 1000000 middle: %f\n", millionMiddle);
  printf("average 1000000 last: %f\n", millionLast);

  return (EXIT_SUCCESS);
}
