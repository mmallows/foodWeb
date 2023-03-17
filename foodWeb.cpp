/*
Marcus Mallows
12/4/2020
Dr. Pangborn

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

int index(string name, vector<string> vec)
{ // Returns index of organism in list
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i) == name)
            return i;
    }
    cout << "Error finding '" << name << "'" << endl;
    return -1;
}

int main()
{

    /*
    Step One (1):
        Define vector of organisms, reads in file of organisms ("organisms.txt")
        and adds all the organisms to vector orgs & fromFile
    */

    vector<string> orgs;
    int orgCounter = 0;

    list<string> fromFile;
    string nextItem;

    ifstream inFile("organisms.txt");

    // list<string>::iterator i = fromFile.begin();
    vector<string>::iterator i = orgs.begin();
    while (inFile >> nextItem)
    { // iterate through "organisms.txt" adding each org to list
        // fromFile.insert(i, nextItem);
        orgs.push_back(nextItem);
        orgCounter++;
        i++;
    }

    cout << "Organisms:" << endl;
    vector<string>::iterator ii = orgs.begin();
    for (ii = orgs.begin(); ii != orgs.end(); ii++)
    {
        // orgs.push_back(*i);
        // orgCounter++;
        cout << *ii << endl;
    }
    cout << "Total num organisms read in: " << orgCounter << endl
         << endl;

    /*
    Step Two (2):
        Create an adjacency list to mark adjacent nodes (organisms)
    */

    vector<int> adjList[orgCounter];     // 2D VECTOR, adding indices of adjacent organisms
    int incoming[orgCounter];            // Keep track of (number of) incoming edges
    for (int j = 0; j < orgCounter; j++) // initialize incoming to 0
    {
        incoming[j] = 0;
    }

    ifstream inFile2("connections.txt");
    while (inFile2 >> nextItem)
    { // Reads in connections, adds them to vector array, tracks incoming edges
        int orgIndex1 = index(nextItem, orgs);
        inFile2 >> nextItem;
        int orgIndex2 = index(nextItem, orgs);
        adjList[orgIndex1].push_back(orgIndex2);
        incoming[orgIndex2]++;
    }

    /*
    Step Three (3):
        Calculate trophic levels:
    */

    int trop[orgCounter]; // Trophic level array
    for (int j = 0; j < orgCounter; j++)
    { //  Initialize to -1
        trop[j] = -1;
    }

    queue<int> bfsq; // Queue for BFS (breadth-first search)

    for (int j = 0; j < orgCounter; j++)
    { // If no inc. edges, trop. level = 0
        if (incoming[j] == 0)
        {
            trop[j] = 0;
            bfsq.push(j);
            // cout << "trophic level 0 - orgIndex: " << j << endl;
        }
    }

    while (!bfsq.empty())
    {                                  // Calculate Tropic Levels:
        int currentOrg = bfsq.front(); // Current item:
        for (vector<int>::iterator i3 = adjList[currentOrg].begin(); i3 != adjList[currentOrg].end(); i3++)
        { // Iterate through adjList
            if (trop[*i3] == -1)
            {                                     // Only take note of those not found yet or those with larger trop. level than
                bfsq.push(*i3);                   // Add newly found item to queue
                trop[*i3] = trop[currentOrg] + 1; // Set trop. level to that of parent +1
            }
        }
        bfsq.pop(); // Remove current item from queue
    }

    /*
    TESTING CODE:
    */

    cout << "Tropic Levels:" << endl;
    for (ii = orgs.begin(); ii != orgs.end(); ii++)
    {
        cout << *ii << ": " << trop[index(*ii, orgs)] << endl;
    }
}