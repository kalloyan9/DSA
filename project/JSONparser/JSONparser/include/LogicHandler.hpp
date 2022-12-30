#ifndef LOGICHANDLER_HPP
#define LOGICHANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

#include "Json.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::stack;
using std::queue;

namespace functionResult
{
    static constexpr int kSUCCESS = 0;
    static constexpr int kFAIL = 1;
} // functionResult

namespace console
{
    static const string kREAD = "read";
    static const string kSEARCH_BY_KEY = "search_key";
    static const string kCHANGE_OBJECT = "change_object";
    static const string kCREATE_OBJECT = "create_object";
    static const string kSAVE = "save";
    static const string kEXIT = "exit";

    enum ConsoleInput
    {
        READ = 0,
        SEARCH_BY_KEY,
        CHANGE_OBJECT,
        CREATE_OBJECT,
        SAVE,
        EXIT,
        UNKNOWN
    };
} // console

class LogicHandler
{
public:
    LogicHandler();
    ~LogicHandler();

    void printMan() const;
    // return kFAIL if terminating the application, kSUCCESS otherwise.
    int runCyclic();
    int handleConsole();

private:
    // read from file and build json tree
    int read(const string& fileName);
    void deleteTree(json::Node *root);
    void printTree(json::Node *root, size_t level);
    void printTree();
    void deleteTree();
    void printTree_BFS();

    // data members
    console::ConsoleInput _consoleInput;
    string _command;
    json::StringHandler _stringHandler;
    json::Node *_root;
    stack<json::Node*> _recStack;
};

#endif // LOGICHANDLER_HPP
