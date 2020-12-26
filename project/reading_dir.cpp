#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

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
                        std::string path = std::string(entry->d_name);
                        std::cout << path << '\t';
                        print_file(&path[0]);
                        stat(path.c_str(), &info);
                        if (S_ISDIR(info.st_mode))
                                explore((char*)path.c_str());
                }
        }
        std::cout << std::endl;

        // 3 close
        closedir(dir);
        return true;
}

void read()
{
        std::string dir_name;
        do {
                console_handler_printmsg("Please enter dir...");
                std::cin >> dir_name;
        } while (!explore(&dir_name[0]));
}

int main ()
{
        // console_handler::read();
        read();
        
        return 0;
}