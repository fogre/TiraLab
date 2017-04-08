/* 
 * File:   ipTable.h
 * Author: fogh
 *
 *Header file for ipTable struct and its methods. Ip tables are the units 
 * which are used for routing in the graph. For now th
 */

#include "ipTableRoutingCell.h"

#ifndef IPTABLE_H
#define	IPTABLE_H


/* Forward declaration */
struct ipTableTag;
//Defining the ipTable structure
typedef struct ipTableTag{
    
    //String version of the ip address. Will be "192.168.mask.identifier"
    const char * ipAddress;
    //address mask
    int mask;
    //unique address identifier
    int identifier;
    struct ipTableRoutingUnitTag destinations[5];
    
}ipTable;


#endif	

