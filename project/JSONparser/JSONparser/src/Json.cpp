#include "Json.hpp"
namespace json {

    Node::Node(const string& key, const string& value, bool isArray)
        : _key(key), _value(value), _isArray(isArray), _siblings()
    {

    }

    void Node::print() {
        cout << "key: " << _key << ", value: " << _value << " siblings: " << _siblings.size() << " ";
        if (_isArray) {
            cout << "start of array ";
        }
        cout << endl;
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

    void Node::setIsArray(const string& value) {
        _value = value;
    }

    void Node::setValue(bool isArray) {
        _isArray = isArray;
    }

    string Node::getKey() {
        return _key;
    }

    string Node::getValue() {
        return _value;
    }

    bool Node::getIsArray() {
        return _isArray;
    }

} // namespace json
