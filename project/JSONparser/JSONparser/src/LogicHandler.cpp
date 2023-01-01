#include "LogicHandler.hpp"
using namespace console;
using namespace functionResult;

LogicHandler::LogicHandler()
{
    _root = nullptr;
    // initial printing manual to the user.
    printMan();
}

LogicHandler::~LogicHandler()
{
    deleteTree();
}

void LogicHandler::printMan() const
{
    cout << endl << endl;
    cout << "===================[man]===================\n";
    cout << "type 'read' - to read a file.\n";
    cout << "type 'search_key' - to search by key.\n";
    cout << "type 'change_object' - to change object.\n";
    cout << "type 'create_object' - to create object.\n";
    cout << "type 'save' - to save to a file.\n";
    cout << "type 'exit' - to exit.\n";
    cout << "type 'man' - to see manual.\n";
    cout << "===========================================\n";
    cout << endl;
}

int LogicHandler::handleConsole()
{
    cout << ">";
    getline(cin, _command);

    if (kEXIT == _command)
    {
        _consoleInput = ConsoleInput::EXIT;
    }
    else if (kREAD == _command)
    {
        _consoleInput = ConsoleInput::READ;
    }
    else if (kSEARCH_BY_KEY == _command)
    {
        _consoleInput = ConsoleInput::SEARCH_BY_KEY;
    }
    else if (kCHANGE_OBJECT == _command)
    {
        _consoleInput = ConsoleInput::CHANGE_OBJECT;
    }
    else if (kCREATE_OBJECT == _command)
    {
        _consoleInput = ConsoleInput::CREATE_OBJECT;
    }
    else if (kSAVE == _command)
    {
        _consoleInput = ConsoleInput::SAVE;
    }
    else
    {
        _consoleInput = ConsoleInput::UNKNOWN;
        printMan();
    }

    return _consoleInput;
}

int LogicHandler::runCyclic()
{
    int consoleResult = handleConsole();
    int helperFuncResult = 0;
    string fileString{}, searchKey{}, fullPath{}, object{}, fileName{};
    vector<string> values;

    switch (consoleResult)
    {
    case ConsoleInput::EXIT:
        deleteTree();
        return kFAIL;
        break;

    case ConsoleInput::READ:
        // clear tree
        deleteTree();
        cout << "Please input a file:" << endl << ">";
        cin >> fileString;
        helperFuncResult = read(fileString);
        if (kSUCCESS == helperFuncResult)
        {
            cout << "File read successfully, JSON parser tree created.\n";
            printTree_BFS();
        }
        else
        {
            cout << "Failed to read file.\n";
            deleteTree();
        }
        return kSUCCESS;
        break;

    case ConsoleInput::SEARCH_BY_KEY:
        cout << "Please input a key to search: " << endl << ">";
        cin >> searchKey;
        if (nullptr == _root)
        {
            cout << "No JSON object available.\n";
        }
        else
        {
            values = findByKey(searchKey);
            cout << "All mapped values to key " << searchKey << " are:\n";
            if (values.size() == 0)
            {
                cout << "nothing is found.\n";
            }
            else
            {
                for (auto i : values)
                {
                    cout << i << endl;
                }
            }
        }
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
        if (nullptr == _root)
        {
            cout << "No JSON object available.\n";
        }
        else
        {
            saveToFile(fileName);
            cout << "JSON object saved successfully to file " << fileName << endl;
        }
        return kSUCCESS;
        break;

    default:
    case ConsoleInput::UNKNOWN:
        return kSUCCESS;
        break;
    }
}

int LogicHandler::read(const string& fileName)
{
    size_t line = 1;
    string str;
    std::ifstream myfile(fileName);
    if (myfile.is_open())
    {
        cout << "file " << fileName << " opened:\n";
        // read line by line
        while (getline(myfile,str))
        {
            // build JSON tree recursive
            if (!_recStack.empty())
            {
                _root = _recStack.top();
            }

            // check and store the key and the value
            bool isEndOfArray = false;
            pair<string, string> mapped = _stringHandler.divideKeyValue(str, isEndOfArray);
            if (!_stringHandler.checkSyntaxValidity(mapped.first, mapped.second))
            {
                std::cerr << "Detected invalid syntax on line " << line << ", symbol: XXX" << mapped.first << "XXX" << mapped.second  << "XXX" << endl;
                std::cerr << "Aborting...\n";
                return kFAIL;
            }
            cout << "keyXXX" << mapped.first << "XXXvalueXXX" << mapped.second << "XXX" << endl;
            // add new node
            json::Node *node = new json::Node(mapped.first, mapped.second);
            // build tree
            // initialization
            if (nullptr == _root)
            {
                _root = node;
                _recStack.push(node);
                continue;
            }

            _root->addSibling(node);
            if (node->containsClosingBracket())
            {
                // closing bracket
                if (!_recStack.empty())
                {
                    _recStack.pop();
                }
            }
            else if (node->containsOpeningBracket())
            {
                // opening array or object
                node->setIsArray(true);
                _recStack.push(node);
            }
            else
            {
                // leaf
                // do nothing
            }
            ++line;
        }
        myfile.close();
        // clear stack
        if (!_recStack.empty())
        {
            std::cerr << "Invalid format.\n";
            return kFAIL;
        }
    }
    else
    {
        cout << "Unable to open file...\n";
        return kFAIL;
    }

    return kSUCCESS;
}

void LogicHandler::deleteTree(json::Node *root)
{
    if (nullptr == root)
    {
        return;
    }

    vector<json::Node*> siblings = root->getSiblings();
    for (size_t i = 0; i < siblings.size(); ++i)
    {
        deleteTree(siblings[i]);
    }

    delete _root;
    _root = nullptr;
}

void LogicHandler::printTree(json::Node *root, size_t level)
{
    if (nullptr == root)
    {
        cout << endl;
        return;
    }

    cout << "level:" << level << " " << root << endl;
    vector<json::Node*> siblings = root->getSiblings();
    for (size_t i = 0; i < siblings.size(); ++i)
    {
        printTree(siblings[i], level + 1);
    }
}

void LogicHandler::printTree()
{
    printTree(_root, 0);
}

void LogicHandler::deleteTree()
{
    deleteTree(_root);
}

void LogicHandler::printTree_BFS()
{
    if (nullptr == _root)
    {
        return;
    }

    static constexpr json::Node* DELIM_DUMP = nullptr;
    vector<json::Node*> v;
    queue<json::Node*> q;
    size_t level = 0;
    json::Node* node = nullptr;
    q.push(_root);
    q.push(DELIM_DUMP);
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        if (DELIM_DUMP == node && !q.empty())
        {
            ++level;
            q.push(DELIM_DUMP);
            continue;
        }
        else if (DELIM_DUMP == node && q.empty())
        {
            break;
        }
        else
        {
            cout << "level:" << level << "|" << node<< endl;
            v = node->getSiblings();
            for (size_t i = 0; i < v.size(); ++i)
            {
                q.push(v[i]);
            }
        }
    }
}

vector<string> LogicHandler::findByKey(const string& key)
{
    vector<string> values;
    stack<json::Node*> s;

    // check the key is valid
    if (key == "{" || key == "[" || key == ",")
    {
        return values;
    }

    s.push(_root);
    json::Node *current;
    vector<json::Node*> siblings;

    while (!s.empty())
    {
        current = s.top();
        s.pop();

        if (current->getKey() == key && !current->containsOpeningBracket())
        {
            values.push_back(current->getValue());
        }

        siblings = current->getSiblings();
        for (size_t i = 0; i < siblings.size(); ++i)
        {
            s.push(siblings[i]);
        }
    }

    return values;
}

// TODO:
int LogicHandler::changeObject(const string& fullPath, const string& newValue)
{
    return 0;
}

// TODO:
int LogicHandler::createObject(const string& fullPath, const string& value)
{
    return 0;
}

int LogicHandler::saveToFile(const string& fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "error opening the file, aborting...\n";
        return kFAIL;
    }

    convertToReadableFormat(_root, 0, file);

    file.close();

    return kSUCCESS;
}

void LogicHandler::convertToReadableFormat(json::Node *root, size_t level, std::ostream& os)
{
    if (nullptr == root)
    {
        os << endl;
        return;
    }

    size_t i = 0;
    string key = root->getKey();
    if (root->containsClosingBracket())
    {
        i = 1;
    }
    while (i < level)
    {
        os << '\t';
        ++i;
    }
    os << root << endl;

    vector<json::Node*> siblings = root->getSiblings();
    for (size_t i = 0; i < siblings.size(); ++i)
    {
        convertToReadableFormat(siblings[i], level + 1, os);
    }
}
