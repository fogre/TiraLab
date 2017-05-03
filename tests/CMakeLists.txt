cmake_minimum_required (VERSION 3.1)
project ("IpGrapher")
set(EXENAME "routingTests")


#project files
set(SOURCES
	../src/randomAddressGenerator.c
	../src/ipTable.c
	../src/destinationsCreator.c
	../src/routing.c
)
#project headers
set(HEADERS
	../src/headers/randomAddressGenerator.h
	../src/headers/ipTable.h
	../src/headers/destinationsCreator.h
	../src/headers/routing.h
)

add_executable(${EXENAME} ${SOURCES} ${HEADERS})
