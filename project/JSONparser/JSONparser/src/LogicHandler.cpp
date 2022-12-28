#include "LogicHandler.hpp"
using namespace console;

LogicHandler::LogicHandler() {
    _root = nullptr;
    _keep = nullptr;
    // initial printing manual to the user.
    printMan();
}

LogicHandler::~LogicHandler() {
    deleteTree(_keep);
    deleteTree(_root);
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

int LogicHandler::runCyclic() {
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
                printTree(_keep);
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
        // read line by line
        while (getline(myfile,line)) {
//            cout << line << '\n';

            if (!_recStack.empty()) {
                _root = _recStack.top();
            }
            bool isArray = false;
            bool isEndOfArray = false;
            pair<string, string> mapped = json::divideKeyValue(line, isArray, isEndOfArray);
//            cout << "key: " << mapped.first << endl;
//            cout << "value: " << mapped.second << endl;

            // add new node
            json::Node *node = new json::Node(mapped.first, mapped.second, isArray);
//            node->print();
            // build tree
            // initialization
            if (nullptr == _root) {
                if (nullptr == _keep) {
                    _root = node;
                    _keep = node;
                    _recStack.push(node);
                    continue;
                }
            }

            _root->addSibling(node);
            _recStack.push(node);

            if (!node->getIsArray() && node->getKey() != "{") {
                // leaf
                _recStack.pop();
            } else {
                // object or array
            }
        }
        myfile.close();
    } else {
        cout << "Unable to open file...\n";
        return kFAIL;
    }

    return kSUCCESS;
}

void LogicHandler::deleteTree(json::Node *root) {
    if (nullptr == root) {
        return;
    }

    vector<json::Node*> siblings = root->getSiblings();
    for (int i = 0; i < siblings.size(); ++i) {
        deleteTree(siblings[i]);
    }
    delete _root;
    _root = nullptr;
}

void LogicHandler::printTree(json::Node *root) {
    if (nullptr == root) {
        cout << endl;
        return;
    }

    root->print();
    vector<json::Node*> siblings = root->getSiblings();
    for (int i = 0; i < siblings.size(); ++i) {
        printTree(siblings[i]);
    }
}
