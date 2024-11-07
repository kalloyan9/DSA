#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

#define MAXINPUT 128
static const char *EMPTY_URL = "about:blank";

struct Tab {
    char *url;
    int timestamp;
    Tab *left, *right;

    Tab(const char* _url) {
        int len = strlen(_url);
        this->url = new char[len];
        strncpy(this->url, _url, len);
        timestamp = time(nullptr);
        left = nullptr;
        right = nullptr;
    }

    Tab& operator= (const Tab& o) {
        int len = strlen(o.url);
        this->url = new char[len];
        strncpy(this->url, o.url, len);
        this->timestamp = o.timestamp;
        this->left = o.left;
        this->right = o.right;
        return *this;
    }
};

// implementing browser using doubly linked list and "sliding mirror" strategy
class Browser
{
private:
    Tab *tabs;
    Tab *current;
    unsigned size;

public:
    void moveLeft() {
        if (nullptr != current->left) {
            current = current->left;
        }
    }

    void moveRight() {
        if (nullptr != current->right) {
            current = current->right;
        }
    }

    void addNewOnRight(Tab *newTab) {
        if (nullptr == current->right) {
            current->right = newTab;
            newTab->left = current;
            current = newTab;
        } else {
            Tab *temp = current->right;
            current->right = newTab;
            newTab->left = current;
            newTab->right = temp;
            temp->left = newTab;
            current = newTab;
        }
        ++size;
    }

    void removeCurrent() {
        Tab *temp = current;
        int whereExists = 0;
        // check for existing tabs by priority right first then left then create
        if (nullptr != current->right) {
            current->right->left = current->left;
            whereExists = 1;
        }
        if (nullptr != current->left) {
            current->left->right = current->right;
            if (0 == whereExists) {
                whereExists = -1;
            }
        }

        if (1 == whereExists) {
            // new current is right
            current = current->right;
        } else if (-1 == whereExists) {
            // new current is left
            current = current->left;
        } else {
            // open about:blank
            current = new Tab(EMPTY_URL);
            tabs = current;
        }

        if (temp == tabs) {
            tabs = current;
        }

        delete temp;
        temp = nullptr;
        --size;
    }

    void go(const char *name) {
        Tab *temp = current;
        current = new Tab(name);
        current->right = temp->right;
        current->left = temp->left;
        delete temp;
        if (nullptr != current->left) {
            current->left->right = current;
        }
        if (nullptr != current->right) {
            current->right->left = current;
        }
        if (nullptr == tabs) {
            tabs = current;
        }
        if (temp == tabs) {
            tabs = current;
        }
    }

    void print() {
        const Tab *p = tabs;
        while (nullptr != p) {
            if (current == p) {
                cout << "> ";
            }
            cout << p->url << " " << p->timestamp << endl;
            p = p->right;
        }        
    }

    Browser() {
        tabs = new Tab(EMPTY_URL);
        current = tabs;
        current->left = tabs->left = nullptr;
        current->right = tabs->right = nullptr;
        size = 1;
    }
    ~Browser() {
        Tab *p = tabs;
        while (nullptr != p) {
            delete p;
            p = p->right;
        }

        delete tabs;
        tabs = nullptr;
        delete current;
        current = nullptr;
    }
};

int consoleHandler() {
    Browser b;
    char input[MAXINPUT];
    char *inputUrl;
    char *word1;
    char *word2;
    while (1) {
        cin.getline(input, MAXINPUT);
        word1 = strtok(input, " ");
        if (0 == strcmp(word1, "GO")) {
            inputUrl = strtok(NULL, "\n");
            if (nullptr != inputUrl) {
                int len = strlen(inputUrl);
                word2 = new char[len];
                strncpy(word2, inputUrl, len);
                b.go(word2);
            }
        } else if (0 == strcmp(word1, "INSERT")) {
            inputUrl = strtok(NULL, "\n");
            if (nullptr != inputUrl) {
                int len = strlen(inputUrl);
                word2 = new char[len];
                strncpy(word2, inputUrl, len);
                Tab *newTab = new Tab(word2);
                b.addNewOnRight(newTab);
            }
        } else if (0 == strcmp(word1, "BACK")) {
            b.moveLeft();
        } else if (0 == strcmp(word1, "FORWARD")) {
            b.moveRight();
        } else if (0 == strcmp(word1, "REMOVE")) {
            b.removeCurrent();
        } else if (0 == strcmp(word1, "PRINT")) {
            b.print();
        } else if (0 == strcmp(word1, "SORT")) {
            word2 = strtok(NULL, "\n");
            cout << "NOT SUPPORTED!" << endl;
        } else {
            cerr << "UKNOWN COMMAND!" << endl;
        }
    }
}

int main() {
    return consoleHandler();
}

