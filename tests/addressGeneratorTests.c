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
#include "../src/headers/randomAddressGenerator.h"

/*test that the method creates an random value for id and that it is
  within given range*/
static void generatesRandomAddress(){
    int nm = 168;
    int m = 0;
    int i = 1;
    int * nmask = &nm;
    int * mask = &m;
    int * id = &i;
    randomAddressGenerator(nmask, mask, id);
    assert_int_equal(*nmask, 168);
    assert_int_equal(*mask, 0);
    assert_in_range(*id,2,17);
}

//Id address is so big that the mask address value is changed as well. Id is not over 1000
static void generatesAddressThatChangesMask(){
    int nm = 168;
    int m = 2;
    int i = 999;
    int * nmask = &nm;
    int * mask = &m;
    int * id = &i;
    randomAddressGenerator(nmask, mask, id);
    assert_in_range(*mask, 3, 6);
    assert_in_range(*id,1,17);
}

/*Identifier and mask addresses are so big, that the mask and netmask address value is changed as well. 
  Id or mask should not be over 1000*/
static void generatesAddressThatChangesNetmask(){
    int nm = 168;
    int m = 999;
    int i = 999;
    int * nmask = &nm;
    int * mask = &m;
    int * id = &i;
    randomAddressGenerator(nmask, mask, id);
    assert_int_equal(*nmask, 169);
    assert_in_range(*mask, 2, 4);
    assert_in_range(*id,1,17);
}

/*Test correctAddressIfItsOver1000.
  An address should be 1 if its 1000 and amount-1000 if it is bigger.*/
static void addressShouldBeOneAnd1000(){
    int thousand = 1000;
    int itsOverOneThousaaaaand = 1200;
    int * p1 = &thousand, * p2 = &itsOverOneThousaaaaand;
    correctAddressIfItsOver1000(p1);
    correctAddressIfItsOver1000(p2);
    assert_int_equal(thousand, 1);
    assert_int_equal(itsOverOneThousaaaaand, 200);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(generatesRandomAddress),
        cmocka_unit_test(generatesAddressThatChangesMask),
        cmocka_unit_test(generatesAddressThatChangesNetmask),
        cmocka_unit_test(addressShouldBeOneAnd1000),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
