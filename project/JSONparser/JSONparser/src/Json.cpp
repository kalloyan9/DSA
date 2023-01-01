#include "Json.hpp"
namespace json
{

bool StringHandler::isDelim(char d)
{
    if (d == '{')
    {
        return true;
    }
    else if (d == '[')
    {
        return true;
    }
    else if (d == ':')
    {
        return true;
    }
    else if (d == ',')
    {
        return true;
    }
    else if (d == '\"')
    {
        return true;
    }
    else if (d == '\n')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool StringHandler::checkSyntaxValidity(const string& key, const string& value)
{
    // hardcoded values
    if ((key == "{" && value == "") || (key == "[" && value == "") || (key == "}" && value == "") || (key == "}" && value == ",")
            || (key == "]" && value == "") || (key == "]" && value == ","))
    {
        return true;
    }

    int quotes = 0;
    // check validity of the key
    const char *c = &key[0];
    while (*c != '\0')
    {
        if (*c == '\"')
        {
            ++quotes;
        }
        ++c;
    }
    if (quotes != 0 && quotes != 2)
    {
        return false;
    }
    if (0 == quotes)
    {
        // expecting integer only
        c = &key[0];
        for (size_t i = 0; i < key.size(); ++i)
        {
            if (!(key[i] >= '0' && key[i] <= '9'))
            {
                return false;
            }
        }
        // invalid mapping key value with integer key
        if (value != "," && value != "")
        {
            return false;
        }
    }

    quotes = 0;
    // check validity of the value
    c = &value[0];
    while (*c != '\0')
    {
        if (*c == '\"')
        {
            ++quotes;
        }
        ++c;
    }
    if (quotes != 0 && quotes != 2)
    {
        return false;
    }

    return true;
}

pair<string, string> StringHandler::divideKeyValue(const string& str, bool &isEndOfArray)
{
    string key, value;
    size_t index = 0;

    // skip whitespaces
    while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t'))
    {
        ++index;
    }

    // if key is start/end of an object or array
    if (str[index] == '{' || str[index] == '[' || str[index] == '}' || str[index] == ']')
    {
        key.push_back(str[index]);
        ++index;
        // skip whitespaces
        while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t'))
        {
            ++index;
        }
        // process the value
        while (str[index] != '\0' && str[index] != '\n')
        {
            if (str[index] == ',')
            {
                value.push_back(str[index]);
            }
            ++index;
        }
        return std::make_pair(key, value);
    }
    else
    {
        // otherwise - regular string key
        // process the key:
        while (str[index] != '\0' && str[index] != ':' && str[index] != ',' && str[index] != '\n')
        {
            // save the key
            key.push_back(str[index]);
            ++index;
        }

        if (str[index] == ',')
        {
            value.push_back(str[index]);
        }
        else if (str[index] == ':' || str[index] == '\n')
        {
            // skip the delimiter
            ++index;

            // skip whitespaces
            while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t'))
            {
                ++index;
            }

            // process the value:
            while(str[index] != '\0' && str[index] != ',' && str[index] != '\n')
            {
                value.push_back(str[index]);
                ++index;
            }
            if (str[index] == ',')
            {
                value.push_back(',');
            }
        }

        string finalKey;
        // remove whitespaces from regular key after quotes
        size_t quotes = 0;
        for (index = 0; key[index] != '\0'; ++index)
        {
            finalKey.push_back(key[index]);
            if (key[index] == '\"')
            {
                ++quotes;
                if (2 == quotes)
                {
                    break;
                }
            }
        }

        return std::make_pair(finalKey, value);
    }
}

Node::Node(const string& key, const string& value)
    : _key(key), _value(value), _siblings()
{

}

std::ostream& operator<<(std::ostream& os, const Node* node)
{
    os << node->_key;
    if (node->_value != "" && node->_value != ",")
        os << ":";
    if (node->_value != "")
        os << node->_value;

    return os;
}

void Node::addSibling(Node *sibling)
{
    _siblings.push_back(sibling);
}

vector<Node*> Node::getSiblings()
{
    return _siblings;
}

void Node::setKey(const string& key)
{
    _key = key;
}

void Node::setValue(const string& value)
{
    _value = value;
}

void Node::setIsArray(bool isArray)
{
    _isArray = isArray;
}


string Node::getKey()
{
    return _key;
}

string Node::getValue()
{
    return _value;
}

bool Node::getIsArray()
{
    return _isArray;
}


bool Node::containsOpeningBracket()
{
    if (_key == "{" || _key == "["
            ||  _value == "{" || _value == "[")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Node::containsClosingBracket()
{
    if (_key == "}" || _key == "]")
    {
        return true;
    }
    else
    {
        return false;
    }
}

} // json
