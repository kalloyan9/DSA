#include <iostream>
#include <string>
#include <map>

bool isAnagram(std::string& lhs, const std::string& rhs)
{
    bool result = false;
    const char *p = &lhs[0];
    std::map<char, int> m;
    while (*p != '\0') {
        if (m.find(*p) != m.end()) {
            ++m[*p];
        } else {
            m[*p] = 1;
        }
        ++p;
    }

    p = &rhs[0];
    while (*p != '\0') {
        if (m.find(*p) != m.end()) {
            --m[*p];
            if (0 == m[*p]) {
                m.erase(*p);
            }
            result = true;
        } else {
            return false;
        }
        ++p;
    }

    // if we still have words that are not used.
    if (m.size()) {
        return false;
    }

    return result;
}

int main ()
{
    // dev test:
    std::string l = "kurra", r = "rukar";

    std::cout << isAnagram(l, r) << std::endl;

    return 0;
}
