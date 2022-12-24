#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;


namespace json {
    // helper class:
    class myPair {
        private:
            // data:
            string _key;
            string _value;

            // methods:
            myPair() = default;
            myPair(const string& key, const string& value) {
                _key = key;
                _value = _value;
            }
            myPair(const myPair& other) {
                this->_key = other._key;
                this->_value = other._value;
            }
            myPair& operator=(const myPair& other) {
                this->_key = other._key;
                this->_value = other._value;
                return *this;
            }
            ~myPair() = default;
            bool operator==(const myPair& other) {
                return _key == other._key && _value == other._value;
            }
            friend std::ostream& operator<<(std::ostream& os, const myPair& p) {
                os << "\"" << p._key << "\", "  << "\"" << p._value << "\"";
                return os;
            }


        friend class Node;
    };

    class Node {
        private:
            Node() = default;
            ~Node();

            myPair *_data = nullptr;
            vector<Node*> _siblings{};

            void print();
    };


} // namespace json
#endif // JSON_HPP
