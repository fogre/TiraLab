/*
 * Test are done with CMocka. For now at least. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/destinationsCreator.h"
#include "../src/headers/randomAddressGenerator.h"


static int setup(void **state){
    ipTable *tables = malloc(7 * sizeof *tables);
    assert_non_null(tables);
    int addressMask = 0;
    int addressId = 1;
    //create tables:
   for(int i = 0; i < 7; i++){
        setupTable(&tables[i]);
        setAddress(&addressMask, &addressId, &tables[i]);
    }
    *state = tables;
    return 0;
}

static int teardown(void **state){
    ipTable * set = *state;
    free(set);
    return 0;
}

/*Tests setSingle destination function. 
  Sets a destination for an IpTable. The tables int lengthOfDestinations should increase by one
  and the destinations should contain the set destination.
*/
static void setsSingleDestinationAndItShouldBeRight(void **state){
    ipTable * set = *state;
    assert_int_equal(set[2].lengthOfDestinations,0);
    setSingleDestination(&set[2], &set[3]);
    assert_int_equal(set[2].lengthOfDestinations,1);
    assert_true(set[2].destinations[0] == &set[3]);
}

/*Test setRandomDestinations function
  Sets random destinations for an IpTable. The function sets one destination,
  the set destination should be included in both setted and destination's ipTables destinations.
*/
static void setsRandomDestinationAndItShouldBeIncludedInBothTables(void **state){
    ipTable * set = *state;
    selectRandomDestinations(&set[5], set, 7, 1);
    //the asserted table should be included into both tables destinations
    assert_true(set[6].destinations[0] == &set[5]);
    assert_true(set[5].destinations[0] == &set[6]);
}

/*Test setRandomDestinations function
  Sets random destinations for an IpTable. The function should set at least one destination,
  the set destinations should be 2-4th cell of the created tables.
*/
static void setsAtleastOneRandomDestination(void **state){
    ipTable * set = *state;
    selectRandomDestinations(&set[5], set, 7, 3);
    assert_true(set[5].lengthOfDestinations > 0);
    for(int i = 0; i < set[5].lengthOfDestinations; i++){
        assert_true(set[5].destinations[i] == &set[2] 
                    || set[5].destinations[i] == &set[3]
                    || set[5].destinations[i] == &set[4]);
    }
}

/*Test setDestinations function
  Sets random destinations for an IpTable. The function should set at least one destination,
  number of created tables is smaller than 5 (size of numberToLink) and the set destinations
  are with given range: 0-2.
*/
static void setDestinationsForCreatedTablesSmallerNumberToLink(void **state){
    ipTable * set = *state;
    setDestinations(&set[3], set, 3);
    assert_true(set[3].lengthOfDestinations > 0);
    assert_true(set[3].lengthOfDestinations < 4);
    for(int i = 0; i < set[3].lengthOfDestinations; i++){
        assert_true(set[3].destinations[i] == &set[0] 
                    || set[3].destinations[i] == &set[1]
                    || set[3].destinations[i] == &set[2]);
    }
}
/*Test setDestinations function
  Sets random destinations for an IpTable. The function should set at least one destination,
  number of created tables is greater than 5 (size of numberToLink) and the set destinations
  are with given range: 0-5.
*/
static void setDestinationsForCreatedTablesGreaterNumberToLink(void **state){
    ipTable * set = *state;
    setDestinations(&set[6], set, 6);
    assert_true(set[6].lengthOfDestinations > 0);
    for(int i = 0; i < set[6].lengthOfDestinations; i++){
        assert_true(set[6].destinations[i] == &set[0] 
                    || set[6].destinations[i] == &set[1]
                    || set[6].destinations[i] == &set[2]
                    || set[6].destinations[i] == &set[3]
                    || set[6].destinations[i] == &set[4]
                    || set[6].destinations[i] == &set[5]);
    }
}

/*creates 2000 tables and checks that they all have destinations*/
static void create2000TablesAndTheyShouldBeConnected(){
    ipTable *tables = malloc(2000 * sizeof *tables);
    assert_non_null(tables);
    int addressMask = 0;
    int addressId = 1;
    tables[0].identifier = addressId;
    tables[0].mask = addressMask;
    setupTable(&tables[0]);
    //create tables:
   for(int i = 1; i < 2000; i++){
        setupTable(&tables[i]);
        setAddress(&addressMask, &addressId, &tables[i]);
        setDestinations(&tables[i],tables, i);
    }
    for(int j = 1999; j > 0; j--){
        assert_non_null(tables[j].destinations);
    }
    free(tables);    
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(setsSingleDestinationAndItShouldBeRight, setup, teardown),
        cmocka_unit_test_setup_teardown(setsRandomDestinationAndItShouldBeIncludedInBothTables, setup, teardown),
        cmocka_unit_test_setup_teardown(setsAtleastOneRandomDestination, setup, teardown),
        cmocka_unit_test_setup_teardown(setDestinationsForCreatedTablesSmallerNumberToLink, setup, teardown),
        cmocka_unit_test_setup_teardown(setDestinationsForCreatedTablesGreaterNumberToLink, setup, teardown),
        cmocka_unit_test(create2000TablesAndTheyShouldBeConnected),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
