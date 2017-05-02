/* 
 * File:   randomAddressGenerator.h
 * Author: fogh
 *
 * Functions to create and set the random IP address
 */


#ifndef RANDOMADDRESSGENERATOR_H
#define	RANDOMADDRESSGENERATOR_H

/*If an address is over 1000, we must correct it to range 1-999*/
static void correctAddressIfItsOver1000(int * address){
    if(*address == 1000){
        *address = 1;
    }else{
        *address = *address-1000;
    }
}


//function to generate a random IP address;
static void randomAddressGenerator(int * netmask, int * mask, int * id){
    int random = *id + (rand() % 17+1);
    *id = random;
    if(*id >= 1000){//correct id address and increase mask
        correctAddressIfItsOver1000(id);
        random = *mask + (rand() % 3+1);
        *mask = random;
        if(*mask >= 1000){//correct mask address and increace netmask by 1
            correctAddressIfItsOver1000(mask);
            *netmask = *netmask+1;
        }
    }
}

#endif	/* RANDOMADDRESSGENERATOR_H */

