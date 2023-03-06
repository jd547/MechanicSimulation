#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
#include <random>
#include <time.h>
#include<cstdio>
#include "header.h"
using namespace std;

struct Claim {
    int claimId;
    string desc;
    int complexity;
    int uncertainty;
    string mListStr;
    string mList[4]={"-1", "-1", "-1", "-1"}; // majority of problems i encountered were caused by
};                                             // not initialising mList as an int array lol. All working now.

struct Mechanic {
    int mechID;
    string name;
    int ability;
    int vAbility;
};

const int MAX=20;
Claim claims[MAX];
Mechanic mechanics[MAX];

// load in mechanics.txt and split and store individual attributes to struct variables
void loadMechanics(char* b) {
    ifstream inMechanics (b);
    size_t MechanicListSize = 0;
    if (!inMechanics) {
        cout<< "Cannot open file. Termi nating..." <<endl;
        exit(1);
    }

    // reads mechanics.txt
    string mLine;
    string mEntries[20];
    while (getline(inMechanics, mLine)) {
        int l=0, n=0;
        int i=0;
        while ((n=mLine.find(",", l)) != string::npos) { // nested while uses position of comma to retrieve sub-string
            //saves sub-string into an entry[i++] every iteration
            mEntries[i++] = mLine.substr(l, n-l);
            l = n + 1;
        }
        mEntries[i++] = mLine.substr(l);

        mechanics[MechanicListSize].mechID = stoi(mEntries[0]);
        mechanics[MechanicListSize].name = (mEntries[1]);
        mechanics[MechanicListSize].ability = stoi(mEntries[2]);
        mechanics[MechanicListSize].vAbility = stoi(mEntries[3]);

        MechanicListSize++;
    }

    // display formatted mechanics.txt
    cout<< "Mech ID" <<"\t"<< "Name" <<"\t"<< "Ability" <<"\t"<< "Variability"<<endl;
    for (int i=0; i<11; i++) {
        cout<< mechanics[i].mechID<<"\t"<<mechanics[i].name<<"\t"<<mechanics[i].ability<<"\t"<<mechanics[i].vAbility<<endl;
    }
    inMechanics.close();
}

// loads in claims.txt, split and store individual attributes to struct variables
void processClaims(char* a, char* c) {
    ifstream inClaims (a);
    size_t ClaimListSize = 0;
    if (!inClaims) {
        cout<< "Cannot open file. Terminating..." <<endl;
        exit(1);
    }

    // reads claims.txt
    string line;
    string mechLine;
    string entries[20];
    string mEntries[20];
    while (getline(inClaims, line)) {
        size_t l=0, n=0;
        int i=0;
        while ((n=line.find(",", l)) != string::npos) {
            entries[i++] = line.substr(l, n-l);
            l = n + 1;

            if (i==4) { // retrieving another substring within substring
                mechLine = line.substr(l, n+l);
                mechLine.erase(0,10);
                entries[i++] = mechLine; // mechLine is mechanic list in string format
            }
        }
        entries[i++] = line.substr(l);

        claims[ClaimListSize].claimId = stoi(entries[0]);
        claims[ClaimListSize].desc = (entries[1]);
        claims[ClaimListSize].complexity = stoi(entries[2]);
        claims[ClaimListSize].uncertainty = stoi(entries[3]);
        claims[ClaimListSize].mListStr = (entries[4]); // mechanicID elements as string

        // storing mechanic ID, int elements to mList[] of struct Claims
        int cnt=0;
        for (int i=0; i<mechLine.length(); i++) {
            if (i%2==0) {
                claims[ClaimListSize].mList[cnt] = mechLine[i];
                cnt++;
            }
        }
        ClaimListSize++;
    }

    // display formatted claims.txt
    cout<<setw(20)<<"Claim ID" <<setw(20)<< "Description" <<setw(20)<< "Complexity" <<setw(20)<< "Uncertainty"<<setw(20)<<"Mechanic List"<<endl;
    for (int i=0; i<10; i++){
        cout<<setw(20)<<claims[i].claimId<<setw(20)<<claims[i].desc<<setw(20)<<claims[i].complexity<<setw(20)<<claims[i].uncertainty<<setw(20)<<claims[i].mListStr<<endl;
    }

    inClaims.close();

    beginTrial(c);
}

// this function implements an algorithm that evaluates each claims based on claims and mechanics attributes
// it also opens and writes to output.txt while printing
void beginTrial(char* txt) {
    ofstream outPut (txt);
    /****
        mean = mechanic ability - claim complexity
        standard deviation = claim uncertainty + mechanic variability
    ****/
    string formatLine = "==============================================================";
    int i=0;
    while (i<10) {
        int j=0;
        while (j <= sizeof(claims[i].mList)/sizeof(claims[i].mList[0])) {
            // if result is <= 50
            if (valueGenerator(claims[i], mechanics[stoi(claims[i].mList[j])])<=50) {
                if (stoi(claims[i].mList[j+1])!=-1) { // if an mList[] element of claims[i] is not user-defined == if you reach the last element of mList[]
                    int percent=valueGenerator(claims[i], mechanics[stoi(claims[i].mList[j])]);
                    cout<<formatLine<<endl;
                    cout<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                    cout<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                    cout<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                    cout<<"~Trial unsuccessful. Move to next mechanic.~"<<endl;
                    outPut<<formatLine<<endl;
                    outPut<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                    outPut<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                    outPut<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                    outPut<<"~Trial unsuccessful. Move to next mechanic.~"<<endl;
                } else {
                    int percent=valueGenerator(claims[i], mechanics[stoi(claims[i].mList[j])]);
                    cout<<formatLine<<endl;
                    cout<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                    cout<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                    cout<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                    cout<<"~Trial unsuccessful. Car is scrap. Move to next claim.~"<<endl;
                    outPut<<formatLine<<endl;
                    outPut<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                    outPut<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                    outPut<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                    outPut<<"~Trial unsuccessful. Car is scrap. Move to next claim.~"<<endl;
                    break;
                }
            } else {
                int percent=valueGenerator(claims[i], mechanics[stoi(claims[i].mList[j])]);
                cout<<formatLine<<endl;
                cout<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                cout<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                cout<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                cout<<"~Trial successful. Car is repaired.~"<<endl;
                outPut<<formatLine<<endl;
                outPut<<"Claim ID: "<<i+1<<"\t|\tDescription: "<<claims[i].desc<<endl;
                outPut<<"Attempt: "<<j+1<<"\t|\tPossibility: "<<percent<<"%"<<endl;
                outPut<<"Mechanic ID: "<<claims[i].mList[j]<<"\t|\t Mechanic Name: "<<mechanics[stoi(claims[i].mList[j])].name<<endl;
                outPut<<"~Trial successful. Car is repaired.~"<<endl;
                break;
            }
            j++;
        }
        i++;
    }
    cout<<"\nCompleted writing... Terminating...";
    outPut<<"\nCompleted writing... Terminating...";
    outPut.close();
}

// this function is called with a claim and mechanic object reference and returns an integer which==possibility
int valueGenerator(Claim oneClaim, Mechanic oneMechanic){
	int mean = oneMechanic.ability - oneClaim.complexity;
	int std_dev = oneClaim.uncertainty + oneMechanic.vAbility;
	default_random_engine random_engine(time(NULL));
	normal_distribution<> dist( mean, std_dev);
	return round(dist(random_engine));
}


