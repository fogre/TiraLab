/* 
 * File:   main.c
 * Author: fogh
 *
 * Created on April 8, 2017, 1:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "ipTable.h"
#include "tableCreator.h"

/*
 * 
 */


int main(int argc, char** argv) {
    
    ipTable * tables;
    createTables(5, tables);
    
    return (EXIT_SUCCESS);
}

