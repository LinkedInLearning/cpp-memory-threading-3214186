#include <iostream>
#include <string>

#include "settings.h"

int main()
{
    std::cout << "Settings bevor wir Daten setzen:" << std::endl;
    std::cout << std::endl;

    gSettings.print();

//    gSettings.setColor("red");
//    gSettings.setUser("Jack");
//    gSettings.setVersion("0.1 beta");

    std::cout << "Settings nachdem wir ein paar Daten gesetzt haben:" << std::endl;

    gSettings.print();
    std::cout << std::endl;

    return 0;
}
