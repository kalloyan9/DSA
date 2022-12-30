#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::pair;

namespace json
    {
    class StringHandler
    {
    public:
        bool isDelim(char d);
        bool checkSyntaxValidity(const string& key, const string& value);
        pair<string, string> divideKeyValue(const string& str, bool &isEndOfArray);
    };

    class Node
    {
    public:
        Node(const string& key, const string& value);
        void addSibling(Node *sibling);
        vector<Node*> getSiblings();
        bool containsOpeningBracket();
        bool containsClosingBracket();

        void setKey(const string& key);
        void setValue(const string& value);

        string getKey();
        string getValue();

        friend std::ostream& operator<<(std::ostream& os, const Node* node);

    private:
        string _key;
        string _value;
        bool _isArray;
        vector<Node*> _siblings;
    };
} // namespace json
#endif // JSON_HPP
