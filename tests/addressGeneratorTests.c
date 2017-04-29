/*
 * Unit tests for randomAddressGenerator.h
 * Tests use Cmocka
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/randomAddressGenerator.h"

/*test that the method creates an random value for id and that it is
  within given range
*/
static void generatesRandomAddress(){
    int m = 0;
    int i = 1;
    int * mask = &m;
    int * id = &i;
    randomAddressGenerator(mask, id);
    assert_int_equal(*mask, 0);
    assert_in_range(*id,2,17);
}

//Id address is so big that the mask address value is changed as well. Id is not over 1000
static void generatesAddressThatChangesMask(){
    int m = 2;
    int i = 999;
    int * mask = &m;
    int * id = &i;
    randomAddressGenerator(mask, id);
    assert_int_equal(*mask, 3);
    assert_in_range(*id,1,17);
}

/*An ipTable is created and a random address is given into it. The given address 
  should be same as the result that comes from the genereteAddress function
*/
static void generatedAddressIsGivenToIpTable(){
    int m = 1;
    int i = 992;
    int * mask = &m;
    int * id = &i;
    struct ipTableTag table;
    setAddress(mask, id, &table);
    assert_int_equal(*mask, table.mask);
    assert_int_equal(*id, table.identifier);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(generatesRandomAddress),
        cmocka_unit_test(generatesAddressThatChangesMask),
        cmocka_unit_test(generatedAddressIsGivenToIpTable),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
