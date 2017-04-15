/* 
 * File:   main.c
 * Author: fogh
 *
 * Created on April 8, 2017, 1:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "tableCreator.h"
#include "ipTable.h"

/*
 * 
 */


int main(int argc, char** argv) {
    
    ipTable * tables;
    createTables(55000, tables);
    
    free(tables);
    
    
    
    return (EXIT_SUCCESS);
}

