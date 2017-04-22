cmake_minimum_required (VERSION 3.1)
project ("IpGrapher")

#headers
include_directories(scr/headers)

#project files
set(SOURCE
	src/main.c)

add_executable(IpGrapher ${SOURCE} ${HEADERS})
