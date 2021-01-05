#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using std::cout; using std::cin;
using std::cerr; using std::endl;

bool print_file(const char* const fileName)
{
        std::ifstream f(fileName);
        if (!f) {
                std::cerr << "Error opening \"" << fileName << "\"\n";
                return false;
        } else {
                std::cout << f.rdbuf() << std::endl;
                f.close();
                return true;
        }
}

inline void console_handler_printmsg(const char* const msg)
{
        std::cout << msg << std::endl;
        std::cout << "> ";
}

void explore(char *dir_name)
{
        DIR *dir; // pointer to an open dir
        struct dirent *entry;
        struct stat info; // information about each entry
        char fullPath[_MAX_PATH];

        // 1 open
        dir = opendir(dir_name);
        if (!dir) {
                std::string errmsg = "dir \""; errmsg += dir_name; errmsg += "\" failed.\n";
                std::cerr << errmsg;
                return;
        }
        _fullpath(fullPath, entry->d_name, _MAX_PATH);

        // 2 read
        while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] != '.') {
                        cout << "current: " << entry->d_name << endl;
                        _fullpath(fullPath, entry->d_name, _MAX_PATH);
                        cout << "full: " << fullPath << endl;
                        stat(fullPath, &info);
                        if (S_ISDIR(info.st_mode))
                                explore(fullPath);
                }
        }
        std::cout << std::endl;

        // 3 close
        closedir(dir);
}

void read()
{
        std::string dir = "";
        explore(&dir[0]);
}

int main ()
{
        read();
        
        return 0;
}