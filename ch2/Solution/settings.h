#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>
#include <iostream>

#include "singleton.h"

class Configuration : public MeyerSingleton<Configuration>
{
public:

    void setVersion(const std::string &version)
    {
        mConfigTable["version"] = version;
    }
    void setColor(const std::string &col)
    {
        mConfigTable["color"] = col;
    }

    void setUser(const std::string &user)
    {
        mConfigTable["user"] = user;
    }

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

#define gSettings Configuration::get()

#endif // SETTINGS_H
