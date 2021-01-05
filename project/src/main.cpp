#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

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

bool explore(char *dir_name)
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
                return false;
        }

        // 2 read
        while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] != '.') {
                        std::cout << "current: " << entry->d_name << std::endl;
                        _fullpath(fullPath, entry->d_name, _MAX_PATH);
                        std::cout << "full: " << fullPath << std::endl;
                        stat(fullPath, &info);
                        if (S_ISDIR(info.st_mode))
                                std::cout << fullPath << " is a dir!\n";
                        else
                                print_file(fullPath);
                }
        }
        std::cout << std::endl;

        // 3 close
        closedir(dir);
        return true;
}

void read()
{
        std::string dir_name = "C:\\Users\\PC\\Desktop\\testhuff";
        explore(&dir_name[0]);
}

int main ()
{
        // console_handler::read();
        read();
        
        std::cin.get();
        getchar();
        return 0;
}