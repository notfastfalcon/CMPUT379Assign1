#include "stdlib.h"
#include "errno.h"
#include "stdio.h"
#include "iostream"
#include "string.h"
#include "map"
#include "mainActivity.h"
#include "commandHandler.h"
using namespace std;

#define LINE_LENGTH 100 //Max # of characters in an input line
#define MAX_ARGS 7 // Max number of arguments to a command
#define MAX_LENGTH 20 //Max # of characters in an argument
#define MAX_PT_ENTRIES 32 //Max entries in the Process Table

int getCommandType(string raw_input) {
    map<string, int> commands = {
    {"exit", 1},
    {"jobs", 2},
    {"kill", 3},
    {"resume", 4},
    {"sleep", 5},
    {"suspend", 6},
    {"wait", 7},
    {"\n", -1}
    };
    for(auto cmd: commands) {
        //if we find any of the command in the first position, return int value
        if (raw_input.find(cmd.first) == 0) {
            return cmd.second;
        }
    }
    return 0;
}

string getInput() {
    string cmdArgument;
    getline(cin, cmdArgument);
    return cmdArgument;
}

void bootUpShell() {
    bool runShell = true;
    while (runShell) {
        string raw_input = getInput();
        int commandType = getCommandType(raw_input);
        runShell = shellProcess(raw_input, commandType);
    }
}

int main (int argc, char *argv[]) {
    bootUpShell();
}