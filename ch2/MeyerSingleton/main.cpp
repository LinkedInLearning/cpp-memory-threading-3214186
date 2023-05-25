#include <iostream>
#include <string>

/////////////////////
// Singleton Class //
/////////////////////

template <class T>
class MeyerSingleton
{
public:
    // Returns the single instance of the class
    static T& get()
    {
        static T instance;
        return instance;
    }

    // Delete the copy constructor and assignment operator
    MeyerSingleton(const T&) = delete;
    MeyerSingleton& operator=(const T&) = delete;

protected:
    // Protected constructor to prevent creation of objects from outside
    MeyerSingleton() {}

    // Protected destructor to prevent deletion from outside
    virtual ~MeyerSingleton() {}
};

//////////////////////////////////////////
// Some own class using this singleton  //
//////////////////////////////////////////

class Logger : public MeyerSingleton<Logger>
{
public:
    std::string logdata;

    void printLog()
    {
        std::cout << logdata  << std::endl;
    }
};

#define gLogger Logger::get()

int main()
{
    gLogger.logdata = "Test";

    gLogger.printLog();

    return 0;
}
