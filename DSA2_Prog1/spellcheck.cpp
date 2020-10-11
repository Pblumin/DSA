#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include "hash.h"
using namespace std;

//Checks if the word has a digit in it
bool isdigit(string &word){
    for(char &ch : word) {
        //ch = tolower(ch);
        if (ch >= 48 && ch <= 57){
            //cout<< ch << "\n";
            return true;
        } 
    }
    return false;
}

//Main errorcheck
//Checks for spaces, wordsize, and if the word is in the dictionary
void errorCheck(string word, int line, bool longWord, hashTable* dictionary, ofstream &outputFile){
    longWord = false;
    string first_20;
    if (word == ""){
        return;
    }
    if(isdigit(word) == true){
        return;
    }
    if (word.size() > 20){
        longWord = true;
        first_20 = word.substr(0, 20);
        outputFile << "Long word at line " << line <<", starts: " << first_20 << endl;
    } else if (!(dictionary -> contains(word)) ){
        outputFile << "Unknown word at line " << line << ": " << word << endl;
    }
}

//Function for loading in the dictionary
//Makes are words in dictionary lowercase
void load(string inputFile, hashTable* dictionary){
    string line;
    ifstream inputFileStream(inputFile);
    while (getline(inputFileStream, line)){
        string word = "";
        stringstream var(line);
        while(var >> word){
            //make all lowercase
            for(char &c : word){
                c = tolower(c);
            }
            dictionary -> insert(word, nullptr);
        }
    }
        inputFileStream.close();
}


//FUNCTION THAT READS THE DOCUMENT TO SPELL CHECK
//
void read(ifstream &inputFile, ofstream &outputFile, hashTable* dictionary){
    string line;
    int linenum = 0;
    bool longWord = false;
    while (getline(inputFile, line)) {
        ++linenum;
        string word = "";

        //get one word at a time and fix up the input file to get all the wordseperators and make lowercase
        stringstream var(line);
        while(var >> word){
            stringstream wordstream(word);
            char ch;
            int flag = 0;
            string temp  = "";
            while(wordstream >> ch){
                ch = tolower(ch);
                if ((ch != 39) && (ch != 45) && !(ch >= 65 && ch <= 90) && !(ch>= 97 && ch <= 122) && !(ch >= 48 && ch <= 57)){
                    //dictionary -> insert(temp, nullptr);
                    
                    errorCheck(temp, linenum, longWord, dictionary, outputFile);
                    //cout<<temp<< " ";
                    temp = "";
                } else {
                    temp += ch;
                }     
            }
            //cout<<temp << " ";
            errorCheck(temp, linenum, longWord, dictionary, outputFile);
        }
    }
}

int main() {
    string dictionary;
    string inputFile, outputFile;
    
    cout << "Enter name of the dictionary file: ";
    cin >> dictionary;

    clock_t t0, t1;
    //Start timer
    t0 = clock();

    //make hashTable
    hashTable* dictionary1 = new hashTable(50000);
    
    //cout << "done";

    //Need to put words from dictioary file into hashtable
    load(dictionary, dictionary1);

    //stop clock
    t1=clock(); 
    cout << "Total time (in seconds) to load dictionary: " << ((float)(t1-t0))/CLOCKS_PER_SEC << endl;

    cout << "Enter name of input file:  \n";
    cin >> inputFile;

    cout << "Enter name of output file:  \n" ;
    cin  >> outputFile;

    //Start timer 2
    t0 = clock();

    ifstream inputFileStream2(inputFile);
    ofstream outputFileStream(outputFile);

    //WRITE SOMETHING HERE THAT PROFORMS THE READING OPERATION
    read(inputFileStream2, outputFileStream, dictionary1);

    //inputFileStream.close();
    outputFileStream.close();

    //end timer 2
    t1 = clock();

    cout << "Total time (in seconds) to check document: " << ((float)(t1-t0))/CLOCKS_PER_SEC << endl;

    return 0;
}