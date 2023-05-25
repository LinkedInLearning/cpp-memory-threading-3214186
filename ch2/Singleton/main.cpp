#include <iostream>
#include <string>

/////////////////////
// Singleton Class //
/////////////////////
template <class T>
class Singleton {
public:
    // Returns the single instance of the class
    static T* get() {
        if (instance_ == nullptr) {
            instance_ = new T();
        }
        return instance_;
    }

private:
    // Private constructor to prevent creation of objects from outside
    Singleton() {}

    // Private destructor to prevent deletion from outside
    ~Singleton() {}

    // The single instance of the class
    inline static T* instance_ = nullptr;
};

//////////////////////////////////////////
// Some own class using this singleton  //
//////////////////////////////////////////
class Logger
{
public:
    std::string logdata;

    void printLog()
    {
        std::cout << logdata  << std::endl;
    }
};

#define gLogger Singleton<Logger>::get()

////////////////////
// Main function  //
////////////////////
int main()
{
    gLogger->logdata = "Test";

    gLogger->printLog();

    return 0;
}
