#include "Json.hpp"
namespace json {

    bool StringHandler::isDelim(char d) {
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

    bool StringHandler::checkSyntaxValidity(const string& key, const string& value) {
        int quotes = 0;
        // check validity of the key
        const char *c = &key[0];
        if (*c != '\0' && *c != ']' && *c != '}' && !isDelim(*c)) {
            while (*c != '\0') {
                if (*c == '\"') {
                    ++quotes;
                }
                ++c;
            }
            if (quotes != 2) {
                return false;
            }

            quotes = 0;
            c = &value[0];
            // check validity of the value
            if (*c != '\0' && !isDelim(*c)) {
                while (*c != '\0') {
                    if (*c == '\"') {
                        ++quotes;
                    }
                    ++c;
                }
                if (quotes != 2) {
                    return false;
                }
            }

            return true;
        }
        return true;
    }

    pair<string, string> StringHandler::divideKeyValue(const string& str, bool &isEndOfArray) {
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

        // skip whitespaces
        while (*c != '\0' && (*c == ' ' || *c == '\t')) {
            ++c;
        }

        if (*c == ':') {
            ++c;
        }

        // skip whitespaces
        while (*c != '\0' && (*c == ' ' || *c == '\t')) {
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


        // remove everything after quotes
        string finalKey;
        size_t quotes = 0;
        c = &key[0];
        while(*c != '\0') {
            if (*c == '\"') {
                ++quotes;
            }
            finalKey.push_back(*c);
            if (quotes == 2) {
                break;
            }
            ++c;
        }

        return std::make_pair(finalKey, value);
    }

    Node::Node(const string& key, const string& value)
        : _key(key), _value(value), _siblings()
    {

    }

    std::ostream& operator<<(std::ostream& os, const Node* node) {
        os << node->_key;
        if (node->_value != "" && node->_value != ",")
                os << ":";
        if (node->_value != "")
            os << node->_value;

        return os;
    }

    void Node::addSibling(Node *sibling) {
        _siblings.push_back(sibling);
    }

    vector<Node*> Node::getSiblings() {
        return _siblings;
    }

    void Node::setKey(const string& key) {
        _key = key;
    }

    void Node::setValue(const string& value) {
        _value = value;
    }

    string Node::getKey() {
        return _key;
    }

    string Node::getValue() {
        return _value;
    }

    bool Node::containsOpeningBracket() {
        if (_key == "{" || _key == "["
        ||  _value == "{" || _value == "[") {
            return true;
        } else {
            return false;
        }
    }

    bool Node::containsClosingBracket() {
        if (_key == "}" || _key == "]") {
            return true;
        } else {
            return false;
        }
    }

} // json
