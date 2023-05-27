#ifndef ASS4_TAKEINPUT_H
#define ASS4_TAKEINPUT_H
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// a function to count how many elements that input text has
int inputSize(string filename){
    string command, line;
    int size = 0;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        while (getline(inputFile, line, '\n')) {
            stringstream ss(line);
            while (getline(ss, command, '\t')) {
                size++;
            }
        }
    } else {
        cout << "There is a problem with opening input file." << endl;
    }
    inputFile.close();
    return size;
}

// a function to store all elements of input text in an array
string *inputArray(string filename) {
    string command, line;
    int size = inputSize(filename);
    int i = 0;
    string *commands;
    commands = new string[size];
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        while (getline(inputFile, line, '\n')) {
            stringstream ss(line);
            while (getline(ss, command, '\t')) {
                commands[i] = command;
                i++;
            }
        }
    } else{
        cout << "There is a problem with opening input file." << endl;
    }
    inputFile.close();
    return commands;
}

#endif //ASS4_TAKEINPUT_H
