#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <mainActivity.h>
using namespace std;

#define LINE_LENGTH 100 //Max # of characters in an input line
#define MAX_ARGS 7 // Max number of arguments to a command
#define MAX_LENGTH 20 //Max # of characters in an argument
#define MAX_PT_ENTRIES 32 //Max entries in the Process Table

int getCommandType(string raw_input) {
    map<string, int> commands = {
    {"exit", 0},
    {"jobs", 1},
    {"kill", 2},
    {"resume", 3},
    {"sleep", 4},
    {"suspend", 5},
    {"wait", 6},
    };
    for(auto cmd: commands) {
        //if we find any of the command in the first position, return int value
        if (raw_input.find(cmd.first) == 0) {
            return cmd.second;
        }
    }
    return -1;
}

string getInput() {
    string cmdArgument;
    getline(cin, cmdArgument);
    return cmdArgument;
}

void bootUpShell() {
    int commandType = getCommandType(getInput());
}

int main (int argc, char *argv[]) {
    bootUpShell();
}