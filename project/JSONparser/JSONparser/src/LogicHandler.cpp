#include "LogicHandler.hpp"

LogicHandler::LogicHandler()
{
    // initial printing manual to the user.
    printMan();
    //ctor
}

LogicHandler::~LogicHandler()
{
    //dtor
}

void LogicHandler::printMan() {
    cout << "===================[man]===================\n";
    cout << "type 'read' - to read a file\n";
    cout << "type 'search_key' - to search by key\n";
    cout << "type 'change_object' - to change object\n";
    cout << "type 'create_object' - to create object\n";
    cout << "type 'save' - to save object\n";
    cout << "type 'exit' - to exit\n";
    cout << "type 'man' - to see manual\n";
    cout << "===========================================\n";
}

int LogicHandler::handleConsole() {
    cout << ">";
    getline(cin, _command);

    if (kEXIT == _command) {
        consoleInput = ConsoleInput::EXIT;
    } else if (kREAD == _command) {
        consoleInput = ConsoleInput::READ;
    } else if (kSEARCH_BY_KEY == _command) {
        consoleInput = ConsoleInput::SEARCH_BY_KEY;
    } else if (kCHANGE_OBJECT == _command) {
        consoleInput = ConsoleInput::CHANGE_OBJECT;
    } else if (kCREATE_OBJECT == _command) {
        consoleInput = ConsoleInput::CREATE_OBJECT;
    } else if (kSAVE == _command) {
        consoleInput = ConsoleInput::SAVE;
    } else {
        consoleInput = ConsoleInput::UNKNOWN;
        printMan();
    }

    return consoleInput;
}

bool LogicHandler::runCyclic(Forest& roots) {
    int consoleResult = handleConsole();
    string fileString{}, searchKey{}, fullPath{}, object{}, fileName{};

    switch (consoleResult) {
        case ConsoleInput::EXIT:
            return false;
        break;

        case ConsoleInput::READ:
            cout << "Please input a file:" << endl << ">";
            cin >> fileString;
            return true;
        break;

        case ConsoleInput::SEARCH_BY_KEY:
            cout << "Please input a key to search: " << endl << ">";
            cin >> searchKey;
            return true;
        break;

        case ConsoleInput::CHANGE_OBJECT:
            cout << "Please input a full path to the object: " << endl << ">";
            cin >> fullPath;
            cout << "Please input a string for the new object: " << endl << ">";
            cin >> object;
            return true;
        break;

        case ConsoleInput::CREATE_OBJECT:
            cout << "Please input a full path to the object: " << endl << ">";
            cin >> fullPath;
            cout << "Please input a string for the new object: " << endl << ">";
            cin >> object;
            return true;
        break;

        case ConsoleInput::SAVE:
            cout << "Please input a file name: " << endl << ">";
            cin >> fileName;
            return true;
        break;

        default:
        case ConsoleInput::UNKNOWN:
            return true;
        break;
    }
}

/*
static const string kREAD{"read"};
static const string kSEARCH_BY_KEY{"search_key"};
static const string kCHANGE_OBJECT{"change_object"};
static const string kCREATE_OBJECT{"create_object"};
static const string kSAVE{"save"};
static const string kEXIT{"exit"};
*/
