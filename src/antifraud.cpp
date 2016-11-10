#include <iostream>
#include <string>
#include <ctime>
#include "NetWork.h"
using namespace std;

int main(int argc, char *argv[])
{
    clock_t begin = clock();

    string inputfile_batch_name;
    string inputfile_stream_name;
    string outputfile_name[3];

    // Assign the associated file names.
    inputfile_batch_name=argv[1];
    inputfile_stream_name=argv[2];
    for(int i=0; i<3; i++)  outputfile_name[i]=argv[i+3];

    NetWork network;
    // Build the initial network.
    network.addEdge_multiple(inputfile_batch_name);
    // Determine the possibility of fraud and update the network at the same time.
    network.antifraud_multiple(inputfile_stream_name, outputfile_name);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    //Uncomment this line to print the running time.
    //cout<<"Time is "<<elapsed_secs<<endl;

    return 0;
}