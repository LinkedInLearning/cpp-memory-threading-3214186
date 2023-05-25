#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>
#include <iostream>

#include "singleton.h"

class Configuration
{
public:

    void print()
    {
        for( const auto &pair : mConfigTable )
        {
            std::cout << pair.first << ": " << pair.second  << std::endl;
        }
    }

private:

    std::map<std::string, std::string> mConfigTable;
};


#endif // SETTINGS_H
