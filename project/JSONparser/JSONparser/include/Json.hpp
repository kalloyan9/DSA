#ifndef JSON_HPP
#define JSON_HPP

#include <vector>
#include <string>
#include <stack>
#include <queue>

// todo: remove
#include <iostream>
using std::cout;
using std::endl;


using std::vector;
using std::string;
using std::stack;
using std::queue;
using std::pair;

namespace json {
    // TODO: add "
    static bool isDelim(char d) {
        if (d == '{') {
            return true;
        } else if (d == '[') {
            return true;
        } else if (d == ':') {
            return true;
        } else if (d == '\n') {
            return true;
        } else {
            return false;
        }
    }

    static pair<string, string> divideKeyValue(const string& str, bool &isEndOfArray) {
        string key, value;
        const char *c = &str[0];
        // skip whitespaces
        while (*c != '\0' && (*c == ' ' || *c == '\t')) {
            ++c;
        }

        // process the key:
        // check new object
        if (*c == '{') {
            key = "{";
            return std::make_pair(key, value);
        }
        // check end of an object
        if (*c == '}') {
            key = "}";
            if (*(c+1) == ',') {
                value = ",";
            }
            return std::make_pair(key, value);
        }
        // check new array
        if (*c == '[') {
            key = "[";
            return std::make_pair(key, value);
        }
        // check end of an array
        if (*c == ']') {
            key = "]";
            isEndOfArray = true;
            if (*(c+1) == ',') {
                value = ",";
            }
            return std::make_pair(key, value);
        }

        // check regular key
        while (*c != '\0' && !isDelim(*c)) {
            // save the key
            key.push_back(*c);
            ++c;
        }

        if (*c == ':') {
            ++c;
        }

        // process the value:
        while(*c != '\0' && !isDelim(*c)) {
            value.push_back(*c);
            ++c;
        }
        // always ending with :

        // check is the value new array or object
        if (*c == '{' || *c == '[') {
            value.push_back(*c);
        } else {
            // always delim is ","
            while (*c != '\0' && *c != ',') {
                value.push_back(*c);
                ++c;
            }
        }

        return std::make_pair(key, value);
    }

    class Node {
        public:
            Node(const string& key, const string& value);
            void print();
            void addSibling(Node *sibling);
            vector<Node*> getSiblings();
            bool containsOpeningBracket();
            bool containsClosingBracket();

            void setKey(const string& key);
            void setValue(const string& value);

            string getKey();
            string getValue();


        private:
            string _key;
            string _value;
            bool _isArray;
            vector<Node*> _siblings;
    };
} // namespace json
#endif // JSON_HPP
