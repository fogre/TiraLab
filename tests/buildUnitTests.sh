#!/bin/bash
#Script to build the tests. The tests are also run if command line argument -r is given,
#but you should ALWAYS try to create the tests first and see if they have errors.

SOURCES="../src/randomAddressGenerator.c ../src/ipTable.c ../src/destinationsCreator.c"

#Path to Cmocka sources. If you want to run the test, change the path to your local Cmocka source
CMOCKAPATH="-l cmocka -L /usr/local/lib"

#build tests
gcc addressGeneratorTests.c ../src/randomAddressGenerator.c -o addressGeneratorTests $CMOCKAPATH
gcc ipTableTests.c $SOURCES -o ipTableTests $CMOCKAPATH
gcc destinationsCreatorTests.c $SOURCES -o destinationsCreatorTests $CMOCKAPATH
gcc routingTests.c $SOURCES ../src/routing.c -o routingTests $CMOCKAPATH

#run tests if command line argument -r is given
if [ "$1" = "-r" ]
then
   ./routingTests
   ./addressGeneratorTests
   ./destinationsCreatorTests
   ./ipTableTests
fi
