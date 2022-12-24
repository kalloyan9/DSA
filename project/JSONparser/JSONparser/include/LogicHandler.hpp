#ifndef LOGICHANDLER_HPP
#define LOGICHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "Json.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

using Forest = std::vector<json::Node*>;

static const string kREAD{"read"};
static const string kSEARCH_BY_KEY{"search_key"};
static const string kCHANGE_OBJECT{"change_object"};
static const string kCREATE_OBJECT{"create_object"};
static const string kSAVE{"save"};
static const string kEXIT{"exit"};

enum ConsoleInput {
    READ = 0,
    SEARCH_BY_KEY,
    CHANGE_OBJECT,
    CREATE_OBJECT,
    SAVE,
    EXIT,
    UNKNOWN
};

class LogicHandler
{
    public:
        LogicHandler();
        ~LogicHandler();


        void printMan();
        // return false if terminating the program, true otherwise.
        bool runCyclic(Forest &roots);
        int handleConsole();

    private:
        string _command;
        ConsoleInput consoleInput;
};

#endif // LOGICHANDLER_HPP
