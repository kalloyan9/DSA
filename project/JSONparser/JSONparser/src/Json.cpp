#include "Json.hpp"
namespace json {

    Node::Node(const string& key, const string& value)
        : _key(key), _value(value), _siblings()
    {

    }

    void Node::print() {
        cout << "key: " << _key << "  value: " << _value << "  siblings: " << _siblings.size() << endl;
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

} // namespace json
