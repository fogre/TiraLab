#!/bin/bash
#Script to build the tests

SOURCES="../src/randomAddressGenerator.c ../src/ipTable.c ../src/destinationsCreator.c"

#Path to Cmocka sources. If you want to run the test, change the path to your local Cmocka source
CMOCKAPATH="-l cmocka -L /usr/local/lib"

#build tests
gcc addressGeneratorTests.c ../src/ipTable.c ../src/randomAddressGenerator.c -o addressGeneratorTests $CMOCKAPATH
gcc destinationsCreatorTests.c $SOURCES -o destinationsCreatorTests $CMOCKAPATH
gcc routingTests.c $SOURCES ../src/routing.c -o routingTests $CMOCKAPATH

