#ifndef JSON_HPP
#define JSON_HPP

#include <vector>
#include <string>
#include <stack>
#include <queue>

// todo: remove
#include <iostream>
using std::cout, std::endl;


using std::vector;
using std::string;
using std::stack;
using std::queue;
using std::pair;

namespace json {
    // lowest value returned is the highest prio
    enum class delimPrio{
        FIRST = 0,
        SECOND,
        THIRD,
        FOURTH,
        INVALID
    };

    static delimPrio getPrio(char delim) {
        if (delim == '{') {
            return delimPrio::FIRST;
        } else if (delim == '[') {
            return delimPrio::SECOND;
        } else if (delim == ':') {
            return delimPrio::THIRD;
        } else if (delim == ',') {
            return delimPrio::FOURTH;
        } else {
            return delimPrio::INVALID;
        }
    }

    static bool isDelim(char d) {
        if (d == '{') {
            return true;
        } else if (d == '[') {
            return true;
        } else if (d == ':') {
            return true;
        } else if (d == ',') {
            return true;
        } else if (d == '\"') {
            return true;
        } else {
            return false;
        }
    }

    // all objects and arrays { and [ and their endings ] and ) should be on new line and alone on line
    static pair<string, string> divideKeyValue(const string& str, bool &isArray, bool &isEndOfArray) {
        string key, value;
        const char *c = &str[0];
        // skip whitespaces
        while (*c != '\0' && (*c == ' ' || *c == '\t')) {
            ++c;
        }
        // check new object
        if (*c == '{') {
            key = "{";
            return std::make_pair(key, value);
        }
        // check end of an object
        if (*c == '}') {
            return std::make_pair(key, value);
        }
        // check new array
        if (*c == '[') {
            isArray = true;
            ++c;
        }
        // check end of an array
        if (*c == ']') {
            isEndOfArray = true;
            ++c;
        }

        // read key
        // skip "
        while (*c == '\"' && *c != '\0') {
            ++c;
        }
        // save key
        while (!isDelim(*c)) {
            key.push_back(*c);
            ++c;
        }
        // skip " and whitespaces
        while (*c != '\0' && (*c == ' ' || *c == '\t' || *c == '\"')) {
            ++c;
        }

        // check if we have value for mapping or not
        if (*c == ':') {
            ++c;
            // skip " and whitespaces
            while (*c != '\0' && (*c == ' ' || *c == '\t' || *c == '\"')) {
                ++c;
            }
            while (!isDelim(*c)) {
                value.push_back(*c);
                ++c;
            }
        } else {
            // do nothing.
        }

        return std::make_pair(key, value);
    }

    class Node {
        public:
            Node(const string& key, const string& value, bool isArray);
            void print();
            void addSibling(Node *sibling);
            vector<Node*> getSiblings();

            void setKey(const string& key);
            void setIsArray(const string& value);
            void setValue(bool isArray);

            string getKey();
            string getValue();
            bool getIsArray();


        private:
            string _key;
            string _value;
            bool _isArray;
            vector<Node*> _siblings;
    };
} // namespace json
#endif // JSON_HPP
