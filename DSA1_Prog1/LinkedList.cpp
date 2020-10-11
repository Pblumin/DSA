//
//  main.cpp
//  DSAAssignment1
//
//  Created by Philip Blumin on 11/16/19.
//  Copyright © 2019 Philip Blumin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <cstring>

using namespace std;

//node class
template <typename T>
class Node {
public:
    T data;
    Node *next;
};

//simpleList Class
template <typename L>
class SimpleList {
public:
    //Constructor
    SimpleList(string &n)
    {
        head=NULL;
        tail=NULL;
        name = n;
    }
    
    //check if empty
    bool isEmpty(){
        if(head == NULL)
            return true;
        else
            return false;
    }
    
    //insert to the front of list
    void insert_front(L d)
    {
        Node<L> *ptr = new Node<L>;
        ptr->data = d;
        if(head == NULL){
            ptr->next = NULL;
            head = ptr;

        } else {

        ptr->next = head;
        head = ptr;
        }
    }
    
    //insert to the back of list
    void insert_back(L d)
    {
        if(!tail){
            Node<L> *ptr = new Node<L>;
            ptr->data = d;
            ptr->next = NULL;
            tail = head;
            head = ptr;
            tail = ptr;
        } else {
            Node<L> *ptr = new Node<L>;
            ptr->data = d;
            //tail->data=d;
            ptr->next = nullptr;
            tail->next = ptr;
            tail = ptr;
        }
    }
    
    //List Function to pop front
    L pop_front()
    {
        //Node<L> *ptr;
        //ptr = head;
        L d = head->data;
        head = head->next;
        if(head == NULL){
            tail = NULL;
        }
        //delete ptr;
        //
        return d;
    }
    
    //Function to pop from a stack and queue
    L test;
    L pop(ofstream &outputFile){
        if(head == NULL) {
            //cerr << "ERROR NULL" << endl;
            outputFile<<"ERROR: This list is empty!"<<endl;
            return test;
        } else {
            L value = pop_front();
            outputFile<<"Value popped: " << value << endl;
            return value;
        }
    }
    
    //get name
    string getname(){
        return name;
    }
    
    virtual void push(L d) = 0;
    //virtual L pop(ofstream &outputFile) = 0;
    
    list<string> names;
    
private:
    Node<L> *head, *tail;
    string name;
};


//stack class
template <typename S>
class Stack : public SimpleList<S>{
public:
    Stack(string &n) : SimpleList<S>(n){}
    
    //Insert element into stack
    void push(S d){
        this->insert_front(d);
    }
};


//stack queue
template <typename Q>
class Queue: public SimpleList<Q> {
public:
    
    Queue(string &n) : SimpleList<Q>(n){}
    
    //Insert element into queue
    void push(Q d){
        this->insert_back(d);
    }
};


//Figure out if name exists
template <typename L>
bool find(const list<SimpleList<L> *> &List, string name){
    bool exists = false;
    for (typename list<SimpleList<L> *>::const_iterator i = List.begin(); i != List.end(); i++){
        //cout << ((*i)->getname()) << endl;
        if(name == ((*i)->getname())){
            exists = true;
            break;
        }
    }
    return exists;
}

//Figure out if type a specific name is
template <typename L>
SimpleList<L>* findList(const list<SimpleList<L> *> &List, string name){
    //std::cerr << "SEARCH NAME: " << name << " " << std::endl;
    //loop to run through the list of names
    for (typename list<SimpleList<L> *>::const_iterator i = List.begin(); i != List.end(); i++){
        //std::cerr << "LIST NAME: " << (*i)->getname() << std::endl;
        if(name == ((*i)->getname())){
            return *i;
            
        }
    }
    return NULL;
}

//create stack/queue function
template <typename L>
void create(list<SimpleList<L> *> &List, string name, string type, ofstream &outputFile){
    bool exists = find(List, name);
    //check if it exists
    if(exists){
        outputFile << "ERROR: This name already exists!"<< endl;
    } else {
        if(type == "stack"){
            SimpleList<L>* ptrL = new Stack<L>(name);
            List.push_front(ptrL);
        } else if (type == "queue") {
            SimpleList<L>* ptrL = new Queue<L>(name);
            List.push_front(ptrL);
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string inputFile, outputFile;
    
    cout<< "Enter name of input file: ";
    cin>> inputFile;
    cout<< '\n';
    
    cout<< "Enter name of output file: ";
    cin>> outputFile;
    cout<< '\n';
    
    //Create input file stream
    ifstream inputFileStream(inputFile);
    
    ofstream outputFileStream(outputFile);
    
    list<SimpleList<int> *> listSLi; // all integer stacks and queues
    list<SimpleList<double> *> listSLd; // all double stacks and queues
    list<SimpleList<string> *> listSLs; // all string stacks and queues
    
    
    //outputFileStream << "hi" << endl;
    //string line;
    string word1, word2, word3;
    while(inputFileStream>> word1 >> word2){
        if(word1 != "pop"){
            inputFileStream>> word3; //need word 3 for create and push
            outputFileStream << "PROCESSING COMMAND: " << word1 << " " << word2 << " " << word3<<"\n";
            if(word1 == "create"){
                char c = word2.at(0); //get the first letter of the name of the file
                if(c == 'i'){
                    create(listSLi, word2, word3, outputFileStream);
                } else if(c == 'd'){
                    create(listSLd, word2, word3, outputFileStream);
                } else if(c == 's'){
                    create(listSLs, word2, word3, outputFileStream);
                }
            } else if (word1 == "push") {
                char c = word2.at(0);
                if (c == 'i'){
                    SimpleList<int>* test = findList(listSLi, word2); //find the type
                    if(test == NULL) {
                        outputFileStream << "ERROR: This name does not exist!" <<"\n";
                    } else {
                        test->push(stoi(word3));
                    }
                }
                else if (c == 'd'){
                    SimpleList<double>* test = findList(listSLd, word2);
                    if(test == NULL) {
                        outputFileStream << "ERROR: This name does not exist!" <<"\n";
                    } else {
                        test->push(stod(word3));
                    }
                }
                else if (c == 's'){
                    SimpleList<string>* test = findList(listSLs, word2);
                    if(test == NULL) {
                        outputFileStream << "ERROR: This name does not exist!" <<"\n";
                    } else {
                        test->push(word3);
                    }
                }
            }
        } else {
            outputFileStream << "PROCESSING COMMAND: " << word1 << " " << word2 <<"\n";
            char c = word2.at(0);
            if (c == 'i'){
                SimpleList<int>* test = findList(listSLi, word2);
                if (test == NULL) {
                    outputFileStream << "ERROR: This name does not exist!" << "\n";
                }else{
                    test->pop(outputFileStream);
                }
            }
            else if (c == 'd'){
                SimpleList<double>* test = findList(listSLd, word2);
                if (test == NULL) {
                    outputFileStream << "ERROR: This name does not exist!" << "\n";
                } else {
                    test->pop(outputFileStream);
                }
            }
            else if (c == 's'){
                SimpleList<string>* test = findList(listSLs, word2);
                if (test == NULL) {
                    outputFileStream << "ERROR: This name does not exist!" << "\n";
                }else{
                    test->pop(outputFileStream);
                }
            }
            
        }
        //outputFileStream << word1 << " " << word2 << " " << word3<<endl;
    }
    
    //outputFileStream << word1 << " " << word2 << " " << word3<<endl;
    
    //close the files
    inputFileStream.close();
    outputFileStream.close();
    
    return 0;
}
