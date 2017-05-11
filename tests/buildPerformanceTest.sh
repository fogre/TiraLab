#!/bin/bash
#Script to build the performance test

SOURCES="../src/randomAddressGenerator.c ../src/ipTable.c ../src/destinationsCreator.c ../src/routing.c"

gcc performanceTest.c $SOURCES -o performanceTest
