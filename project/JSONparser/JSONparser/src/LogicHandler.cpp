#include "LogicHandler.hpp"
using namespace console;

LogicHandler::LogicHandler() {
    _root = nullptr;
    // initial printing manual to the user.
    printMan();
}

LogicHandler::~LogicHandler() {
    deleteTree();
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
            // clear tree
            deleteTree();
            cout << "Please input a file:" << endl << ">";
            cin >> fileString;
            helperFuncResult = read(fileString);
            if (kSUCCESS == helperFuncResult) {
                cout << "File read successfully, JSON parser tree created.\n";
                //printTree(_root);
                printBFS();
            } else {
                cout << "Failed to read file.\n";
                deleteTree();
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
    // todo: hack idea - function to remove all /" from the file, then add them forced in divideKeyValue func :)
    if (myfile.is_open()) {
        cout << "file " << fileName << " opened:\n";
        // read line by line
        while (getline(myfile,line)) {
            if (!_recStack.empty()) {
                _root = _recStack.top();
            }

            bool isEndOfArray = false;
            pair<string, string> mapped = json::divideKeyValue(line, isEndOfArray);

            // add new node
            json::Node *node = new json::Node(mapped.first, mapped.second);
            // build tree
            // initialization
            if (nullptr == _root) {
                _root = node;
                _recStack.push(node);
                continue;
            }

            _root->addSibling(node);
            if (mapped.first != "[" && mapped.first != "{"
            &&  mapped.second != "[" && mapped.second != "{") {
                // handle leaf
                if (mapped.first == "]" || mapped.first == "}") {
                    // handle closing of array and closing of object
                    if (!_recStack.empty()) {
                        _recStack.pop();
                    }
                }
            } else {
                // handle not leaf
                _recStack.push(node);
            }
        }
        myfile.close();
        // clear stack
        if (!_recStack.empty()) {
            std::cerr << "Invalid format.\n";
            return kFAIL;
        }
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

void LogicHandler::printTree() {
    printTree(_root);
}

void LogicHandler::deleteTree() {
    deleteTree(_root);
}

void LogicHandler::printBFS() {
    if (nullptr == _root) {
        return;
    }

    json::Node* node = nullptr;
    static constexpr json::Node* DELIM_DUMP = nullptr;
    vector<json::Node*> v;
    size_t level = 0;
    queue<json::Node*> q;
    q.push(_root);
    q.push(DELIM_DUMP);
    while (!q.empty()) {
        node = q.front();
        q.pop();
        if (DELIM_DUMP == node) {
            ++level;
            continue;
        }

        v = node->getSiblings();
        cout << "level:" << level << "| ";
        node->print();
        for (int i = 0; i < v.size(); ++i) {
            q.push(v[i]);
        }
        if (v.size()) {
            q.push(DELIM_DUMP);
        }
    }
}
