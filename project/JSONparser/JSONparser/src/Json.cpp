#include "Json.hpp"
namespace json {

    Node::~Node() {
        delete _data;
        _data = nullptr;

        for (size_t i = 0; i < _siblings.size(); ++i) {
            delete _siblings[i];
            _siblings[i] = nullptr;
        }

        _siblings.clear();
    }

    void Node::print() {
        if (_data != nullptr) {
            std::cout << *_data;
        }
    }

} // namespace json
