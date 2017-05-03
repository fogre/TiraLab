/* 
 * File:   randomAddressGenerator.h
 * Author: fogh
 *
 * Functions to create and set the random IP address
 */


#ifndef RANDOMADDRESSGENERATOR_H
#define	RANDOMADDRESSGENERATOR_H

/*If an address is over 1000, we must correct it to range 1-999*/
void correctAddressIfItsOver1000(int * address);

//function to generate a random IP address;
void randomAddressGenerator(int * netmask, int * mask, int * id);

#endif	/* RANDOMADDRESSGENERATOR_H */

