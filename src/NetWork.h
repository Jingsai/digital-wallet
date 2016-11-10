#ifndef NETWORK_H_
#define NETWORK_H_

#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct transaction{
    long sender;    // ID of user.
    long receiver;  // ID of user.
    string time;
    float money;
    //string message; // Ignore.
};

// Each user has one Friend_Table.
struct Friend_Table{
    vector<long> level1; // List of 1st-degree friends.
    vector<long> level2; // List of 2nd-degree friends.
};

/*
Hash Table ---  Key     ---    Value
           ---  User ID --- 1st-degree friends.
                        --- 2nd-degree friends.
*/
class NetWork{
    public:
        NetWork();
        ~NetWork();
        // Build a network based on a group of transactions imported from a file.
        int addEdge_multiple(string filename);
        // Update the network by one transaction.
        void addEdge(long ID1, long ID2);
        // Decide friend distances based on a group of transactions imported from a file.
        int antifraud_multiple(string filename, string outputfile_name[4]);
        // Decide friend distance between one sender and one receiver.
        void antifraud(long ID1, long ID2, string* output);
        // Print friend lists of one ID.
        void getVertex(long ID);
        // Print current network.
        void print();
        // Is there a common user between two lists?
        bool hasCommonFriend(vector<long> left, vector<long> right);
    private:
        // Hash map to store the network: <User ID, Friend Table of this user>
        unordered_map<long,Friend_Table> graph;
        unordered_map<long,Friend_Table>::iterator it;
};

#endif