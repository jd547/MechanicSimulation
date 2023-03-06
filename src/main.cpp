/*****
-this program should run with claims.txt mechanics.txt output.txt as command-line arguments
-read, split, store and print attributes
-evaluate claims using attributes from Claim and Mechanic struct
-write everything that was printed to output.txt file
****/
#include <iostream>
#include<cstring>
#include<fstream>
#include "header.h"
using namespace std;

int main(int argc, char *argv[])
{
    // first check command-line arguments
    if (argc != 4) {
        cerr<< "Enter the appropriate txt files after the program name please!" <<endl;
        return 1;
    }

    //open mechanics.txt
    loadMechanics(argv[2]);

    //open claims.txt
    processClaims(argv[1], argv[3]);

}
