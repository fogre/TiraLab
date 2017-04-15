/* 
 * File:   ipTableRoutingCell.h
 * Author: fogh
 *
 * These are used in the ipTables destinations table to determine possible route
 */

#ifndef IPTABLEROUTINGCELL_H
#define	IPTABLEROUTINGCELL_H

/* Forward declaration */
struct ipTableRoutingUnitTag;
//ipTable destinations tablecell:
typedef struct ipTableRoutingUnitTag{
    
    int destination;
    int netmask;
    struct ipTableTag * nextHop;
    //int metric;
    
}ipTableRoutingUnit;

#endif	/* IPTABLEROUTINGCELL_H */

