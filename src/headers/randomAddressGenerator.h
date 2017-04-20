/* 
 * File:   randomAddressGenerator.h
 * Author: fogh
 *
 * Functions to create and set the random IP address
 */


#ifndef RANDOMADDRESSGENERATOR_H
#define	RANDOMADDRESSGENERATOR_H

//function to generate a random IP address;
static void randomAddressGenerator(int * mask, int * id){
    
    int random = *id + (rand() % 17+1);
    *id = random;
    if(*id >= 1000){
        random = *mask + (rand() % 3+1);
        *mask = random;
        if(*id == 1000){
            *id = 1;
        }else{
            random = *id-1000;
            *id = random;
        }
    }
}

//Function that sets the randomly generated address to IpTable struct
static void setAddress(int * mask, int * id, ipTable * table){
    randomAddressGenerator(mask, id);
    table->mask = *mask;
    table->identifier = *id;
}

#endif	/* RANDOMADDRESSGENERATOR_H */
