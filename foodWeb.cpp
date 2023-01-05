/*
Marcus Mallows
12/4/2020

Description: Program takes in text file of organisms, another text file of connections,
and computes the trophic levels of each organism.

*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <list>
#include <queue>

using namespace std;

int index (string name, vector<string> vec){    //Returns index of organism in list
        for(int i = 0; i < vec.size(); i++){
            if (vec.at(i)==name) return i;
        }
        cout << "Error finding '" << name << "'" << endl;
        return -1;
    }

int main(){

    /*
    Step One (1):
    */

    vector<string> orgs;
    int n=0;

    list<string> fromFile;
    string nextItem;

    ifstream inFile("organisms.txt");

    list<string>::iterator i = fromFile.begin();
    while(inFile >> nextItem){
	    fromFile.insert(i, nextItem);
	    orgs.push_back(nextItem);
	    n++;
	    i++;
    }

    cout << "Organisms:" << endl;
    vector<string>::iterator ii=orgs.begin();
    for( ii = orgs.begin(); ii != orgs.end(); ii++){
	    //orgs.push_back(*i);
	    //n++;
	    cout << *ii << endl;
    }
    cout << "Total num organisms read in: " << n << endl << endl;

    /*
    Step Two (2):
    */

    vector<int> adjList[n]; // 2D VECTOR
    int incoming[n]; //Keep track of (number of) incoming edges
    for (int j = 1; j < n; j++){
        incoming[j]=0;
    }

    ifstream inFile2("connections.txt");
    while(inFile2 >> nextItem){         //Reads in connections, adds them to vector array, tracks incoming edges
	    int ind1 = index(nextItem, orgs);
        inFile2 >> nextItem;
        int ind2 = index(nextItem, orgs);
        adjList[ind1].push_back(ind2);
        incoming[ind2]++;
    }

    /*
    Step Three (3)
    */

    int trop[n]; //Tropic level array
    for (int j = 0; j < n; j++){  //  Initialize to -1
     trop[j] = -1;
    }

    queue<int> bfsq; //Queue for BFS

    for (int j = 0; j < n; j++){ //If no inc. edges, trop level = 0
        if (incoming[j]==0){
            trop[j]=0;
            bfsq.push(j);
        }
    }

    while (!bfsq.empty()){  //Calculate Tropic Levels:
        int cur = bfsq.front();  //Current item:
        for (vector<int>::iterator i3 = adjList[cur].begin(); i3 != adjList[cur].end(); i3++){ //Iterate through adjList
            if (trop[*i3] == -1){       //Only take note of those not found yet or those with larger trop. level than
                bfsq.push(*i3); //Add newly found item to queue
                trop[*i3] = trop[cur]+1;  //Set trop. level to that of parent +1
            }
        }
        bfsq.pop();     //Remove current item from queue
    }

    /*
    TESTING CODE:
    */

    cout << "Tropic Levels:" << endl;
    for (ii = orgs.begin(); ii != orgs.end(); ii++){
        cout << *ii << ": " << trop[index(*ii, orgs)] << endl;
    }

}