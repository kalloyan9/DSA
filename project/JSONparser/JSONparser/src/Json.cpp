#include "Json.hpp"
namespace json {

    Node::Node(const string& key, const string& value)
        : _key(key), _value(value), _siblings()
    {

    }

    void Node::print() {
        cout << "`" << _key << "`||`" << _value << "`" << endl;
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

} // namespace json
