/* 
 * File:   ipTableRoutingCell.h
 * Author: fogh
 *
 * These are used in the ipTables destinations table to determine possible route
 */

#ifndef IPTABLEROUTINGCELL_H
#define	IPTABLEROUTINGCELL_H

/* Forward declaration */
struct ipTableRoutingCellTag;
//ipTable destinations tablecell:
typedef struct ipTableRoutingCellTag{
    
    int destination;
    int netmask;
    struct ipTableTag * nextHop;
    //int metric;
    
}ipTableRoutingCell;

/*static void setRoutingCell(ipTableRoutingCell * rCell, ipTable * table){
	rCell->destination=table.identifier;
	rCell->mask=table.mask;
	rCell->nextHop

}*/

#endif	/* IPTABLEROUTINGCELL_H */

