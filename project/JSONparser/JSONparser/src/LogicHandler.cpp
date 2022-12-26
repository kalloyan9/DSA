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

void LogicHandler::printMan() const {
    cout << endl << endl;
    cout << "===================[man]===================\n";
    cout << "type 'read' - to read a file\n";
    cout << "type 'search_key' - to search by key\n";
    cout << "type 'change_object' - to change object\n";
    cout << "type 'create_object' - to create object\n";
    cout << "type 'save' - to save object\n";
    cout << "type 'exit' - to exit\n";
    cout << "type 'man' - to see manual\n";
    cout << "===========================================\n";
    cout << endl;
}

int LogicHandler::handleConsole() {
    cout << ">";
    getline(cin, _command);

    if (kEXIT == _command) {
        _consoleInput = ConsoleInput::EXIT;
    } else if (kREAD == _command) {
        _consoleInput = ConsoleInput::READ;
    } else if (kSEARCH_BY_KEY == _command) {
        _consoleInput = ConsoleInput::SEARCH_BY_KEY;
    } else if (kCHANGE_OBJECT == _command) {
        _consoleInput = ConsoleInput::CHANGE_OBJECT;
    } else if (kCREATE_OBJECT == _command) {
        _consoleInput = ConsoleInput::CREATE_OBJECT;
    } else if (kSAVE == _command) {
        _consoleInput = ConsoleInput::SAVE;
    } else {
        _consoleInput = ConsoleInput::UNKNOWN;
        printMan();
    }

    return _consoleInput;
}

int LogicHandler::runCyclic(Forest& roots) {
    int consoleResult = handleConsole();
    int helperFuncResult = 0;
    string fileString{}, searchKey{}, fullPath{}, object{}, fileName{};

    switch (consoleResult) {
        case ConsoleInput::EXIT:
            return kFAIL;
        break;

        case ConsoleInput::READ:
            cout << "Please input a file:" << endl << ">";
            cin >> fileString;
            helperFuncResult = read(fileString);
            if (kSUCCESS == helperFuncResult) {
                cout << "File read successfully, JSON parser tree created.\n";
            } else {
                cout << "Failed to read file.\n";
            }
            return kSUCCESS;
        break;

        case ConsoleInput::SEARCH_BY_KEY:
            cout << "Please input a key to search: " << endl << ">";
            cin >> searchKey;
            return kSUCCESS;
        break;

        case ConsoleInput::CHANGE_OBJECT:
            cout << "Please input a full path to the object: " << endl << ">";
            cin >> fullPath;
            cout << "Please input a string for the new object: " << endl << ">";
            cin >> object;
            return kSUCCESS;
        break;

        case ConsoleInput::CREATE_OBJECT:
            cout << "Please input a full path to the object: " << endl << ">";
            cin >> fullPath;
            cout << "Please input a string for the new object: " << endl << ">";
            cin >> object;
            return kSUCCESS;
        break;

        case ConsoleInput::SAVE:
            cout << "Please input a file name: " << endl << ">";
            cin >> fileName;
            return kSUCCESS;
        break;

        default:
        case ConsoleInput::UNKNOWN:
            return kSUCCESS;
        break;
    }
}

int LogicHandler::read(const string& fileName) {
    string line;
    std::ifstream myfile(fileName);
    if (myfile.is_open()) {
        cout << "file " << fileName << " opened:\n";
        while (getline(myfile,line)) {
            cout << line << '\n';
        }

        // prioritization
        if (line == "[") {
            // create sibling
        } else if (line == "{") {
            // create node
        } else if (line == ":") {
            // setValue
        } else if (line == ",") {
            // do nothing
        } else {
            // setKey
        }






        myfile.close();
    } else {
        cout << "Unable to open file...\n";
        return kFAIL;
    }

    return kSUCCESS;
}
