/*
 * Tests for ipTable creation. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/headers/ipTable.h"
#include "../src/headers/tableCreator.h"

static int setup(void **state){
    ipTable *tabless;
    createTables(100, tabless);
    assert_non_null(tabless);
    *state = tabless;
    return 0;
}

static int teardown(void ** state){
    //free(*state);
    return 0;
}

/*The size of the ipTables should be 100 and no two contiguous identifier should be the same*/
static void testTablesSizeAndIpAddresses(void ** state){
    ipTable * t = *state;
    int amount;
    int previousId = 999;
    for(amount = 0; amount < 100; amount ++){
        if(previousId == t[amount].identifier){
            break;
        }
        previousId = t[amount].identifier;        
    }
    assert_int_equal(amount, 100);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testTablesSizeAndIpAddresses),
    };

    return cmocka_run_group_tests(tests, setup, NULL);
}
