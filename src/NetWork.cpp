#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "NetWork.h"
using namespace std;

int NetWork::addEdge_multiple(string filename){
    ifstream file(filename);
    // Default extension of the file in run.sh is .txt.
    // Change to .csv if the actual file extension is .csv.
    if(!file.is_open()){
        size_t lastindex = filename.find_last_of(".");
        filename = filename.substr(0, lastindex) + ".csv";
        file.open(filename);
    }

    cout<<"Begin to build the initial network..."<<endl;
    transaction tran;
    string strtran;
    getline(file, strtran); //skip the head
    while(getline(file, strtran, '\n')){
        stringstream s(strtran);
        string item;
        vector<string> tokens;
        while(getline(s,item,',')){
            tokens.push_back(item);
        }

        if(tokens.size()>4){
            //tran.time=tokens[0];
            tran.sender=stol(tokens[1]);  // Change to long format.
            tran.receiver=stol(tokens[2]); // Change to long format.
            //tran.money=stof(tokens[3]);
            //tran.message=tokens[4];
            //test code
            //cout<<tran.time<<" "<<tran.sender<<" "<<tran.receiver<<" "<<tran.money<<" "<<tran.message<<endl;
            addEdge(tran.sender, tran.receiver); // Add this edge into the network.
        }
        else if(tokens.size()>0){
            cout<<"Each transaction must contain these five parts: time, sender, receiver, money, message."<<endl;
            cout<<"This following record is not complete:"<<endl;
            for(int i=0; i<tokens.size(); i++) cout<<tokens[i]<<", ";
            cout<<endl;
            return -1;
        }
    }
    file.close();
    cout<<"Done"<<endl;
    return 0;
}

void NetWork::addEdge(long ID1, long ID2){
    // Initialize the vertex for new user.
    if(graph.find(ID1)==graph.end()){
        Friend_Table tab;
        graph[ID1]=tab;
    }
    if(graph.find(ID2)==graph.end()){
        Friend_Table tab;
        graph[ID2]=tab;
    }

    /*
    Update the network for a new edge between user A and user B.
             _____________new 2nd___________
            |                     new 1st   |
    1st-degree list of A  ---  A   ------   B   ---   1-st degree list of B
                               |______________new 2nd__________________|

    */
    if(find(graph[ID1].level1.begin(), graph[ID1].level1.end(), ID2) == graph[ID1].level1.end()){
        vector<long> :: iterator i;
        // Add B into 2nd-degree list of user in 1st-degree list of A, and vice versa.
        for(i = graph[ID1].level1.begin(); i != graph[ID1].level1.end(); ++i){
            graph[*i].level2.push_back(ID2);
        }
        for(i = graph[ID2].level1.begin(); i != graph[ID2].level1.end(); ++i){
            graph[*i].level2.push_back(ID1);
        }
        // Add 1st-degree list of B into 2nd-degree list of A, and vice versa.
        graph[ID1].level2.insert(graph[ID1].level2.end(), graph[ID2].level1.begin(), graph[ID2].level1.end());
        graph[ID2].level2.insert(graph[ID2].level2.end(), graph[ID1].level1.begin(), graph[ID1].level1.end());
        // Add B into 1st-degree list of A, and vice versa.
        graph[ID1].level1.push_back(ID2);
        graph[ID2].level1.push_back(ID1);
    }
}

int NetWork::antifraud_multiple(string filename, string outputfile_name[4]){
    string output[4];
    ofstream outputfile[4];
    for(int i=0; i<4; i++)  outputfile[i].open(outputfile_name[i]);

    // Default extension of the file in run.sh is .txt.
    // Change to .csv if the actual file extension is .csv.
    ifstream file(filename);
    if(!file.is_open()){
        size_t lastindex = filename.find_last_of(".");
        filename = filename.substr(0, lastindex) + ".csv";
        file.open(filename);
    }

    cout<<"Begin to monitor each transaction and update the network..."<<endl;
    transaction tran;
    string strtran;
    getline(file, strtran); //skip the head
    while(getline(file, strtran, '\n')){
        stringstream s(strtran);
        string item;
        vector<string> tokens;
        while(getline(s,item,',')){
            tokens.push_back(item);
        }

        if(tokens.size()>4){
                //tran.time=tokens[0];
                tran.sender=stol(tokens[1]);  // Change to long format.
                tran.receiver=stol(tokens[2]); // Change to long format.
                tran.money=stof(tokens[3]);
                //tran.message=tokens[4];

                antifraud(tran.sender, tran.receiver, output);
                for(int i=0; i<3; i++)  outputfile[i]<<output[i]; // Write the values.
                if(tran.money>50.0) outputfile[3]<<"unverified\n";
                else outputfile[3]<<"trusted\n";
            }
        else if(tokens.size()>0){
            cout<<"Each transaction must contain these five parts: time, sender, receiver, money, message."<<endl;
            cout<<"This following record is not complete:"<<endl;
            for(int i=0; i<tokens.size(); i++) cout<<tokens[i]<<", ";
            cout<<endl;
            return -1;
        }
    }
    file.close();
    for(int i=0; i<4; i++)  outputfile[i].close();
    cout<<"Done"<<endl;
    return 0;
}

void NetWork::antifraud(long ID1, long ID2, string* output){
    //0-degree. Sender is receiver.
    if(ID1==ID2){
        output[0]="trusted\n";
        output[1]="trusted\n";
        output[2]="trusted\n";
    }
    //new user
    else if(graph.find(ID1)==graph.end() || graph.find(ID2)==graph.end()){ // symmetric
        output[0]="unverified\n";
        output[1]="unverified\n";
        output[2]="unverified\n";
    }
    // 1-degree. B is in 1st-degree list of A.
    else if(find(graph[ID1].level1.begin(), graph[ID1].level1.end(), ID2) != graph[ID1].level1.end()){
        output[0]="trusted\n";
        output[1]="trusted\n";
        output[2]="trusted\n";
    }
    // 2-degree. B is in 2nd-degree list of A.
    else if(find(graph[ID1].level2.begin(), graph[ID1].level2.end(), ID2) != graph[ID1].level2.end()){
        output[0]="unverified\n";
        output[1]="trusted\n";
        output[2]="trusted\n";
    }
    // 3-degree. 1st-degree list of B interects with 2nd-degree list of A.
    else if(hasCommonFriend(graph[ID1].level2,graph[ID2].level1)){
        output[0]="unverified\n";
        output[1]="unverified\n";
        output[2]="trusted\n";
    }
    // 4-degree. 2nd-degree list of B interects with 2nd-degree list of A.
    else if(hasCommonFriend(graph[ID1].level2,graph[ID2].level2)){
        output[0]="unverified\n";
        output[1]="unverified\n";
        output[2]="trusted\n";
    }
    else{
        output[0]="unverified\n";
        output[1]="unverified\n";
        output[2]="unverified\n";
    }

    //update the graph
    addEdge(ID1, ID2);
}

NetWork::NetWork(){
    // Do something here.
}

NetWork::~NetWork(){
    // Do something here.
}

void NetWork::print(){
    for(it=graph.begin(); it!=graph.end(); it++){
        getVertex(it->first);
    }
}

void NetWork::getVertex(long ID){
    vector<long> :: iterator i;
    cout<<ID<<endl;
    cout<<"level 1, size: "<<graph[ID].level1.size()<<endl;
    for(i = graph[ID].level1.begin(); i != graph[ID].level1.end(); ++i) cout<<*i<<", ";
    cout<<endl;
    cout<<"level 2, size: "<<graph[ID].level2.size()<<endl;
    for(i = graph[ID].level2.begin(); i != graph[ID].level2.end(); ++i) cout<<*i<<", ";
    cout<<endl;
}

bool NetWork::hasCommonFriend(vector<long> left, vector<long> right){
    for(int i=0; i<left.size(); i++){
        for(int j=0; j<right.size(); j++){
            if(left[i]==right[j]){
                return true;
            }
        }
    }
    return false;
}