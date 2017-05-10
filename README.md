# IpGrapher

This C-program is done for an university course. 

The program creates a randomly generated graph, or a "network", from which you can search a path to a specific node.

## Requirements

* gcc 5.4.0 or newer
* CMake 3.1 or newer
* Testing is done with Cmocka. Not needed to run the main program

The program has been tested only with the previously mentioned versions on Ubuntu 16.04.

## Building

You need to have Cmake to generate the make files: 
* Clone or download the repository
* Create an installation folder for the program
* Go to the installation folder and call cmake ../PathToDownloadedRepository
* Run make on the installation folder to build the executable program <b>IpGrapher</b>

## How to use

`IpGrapher [amount]`

The program takes only one <b>optional</b> command line argument <i>amount</i>. It determines the number of the nodes to be generated in the network and it should be an integer between 10-1200000.

Without it, a network of 100000 nodes is created.





