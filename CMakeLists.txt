cmake_minimum_required (VERSION 3.1)
project ("IpGrapher")

#headers
include_directories(scr/headers)

#project files
set(SOURCE
	src/main.c)

set(HEADERS
	src/headers/ipTable.h
	src/headers/ipTableRoutingCell.h
	src/headers/randomAddressGenerator.h
	src/headers/tableCreator.h)

add_executable(IpGrapher ${SOURCE} ${HEADERS})
