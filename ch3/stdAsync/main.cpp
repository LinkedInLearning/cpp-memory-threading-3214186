#include <iostream>
#include <future>
#include <string>
#include <mutex>

std::mutex gMutex;

struct Concurrent {
    void test1(const int i, const std::string& str)
    {
        std::lock_guard<std::mutex> lock(gMutex);
        std::cout << str << ' ' << i << std::endl;        
    }
    void test2(const std::string& str)
    {
        std::lock_guard<std::mutex> lock(gMutex);
        std::cout << str << std::endl;
    }
    int operator()(const int i)
    {
        std::lock_guard<std::mutex> lock(gMutex);
        std::cout << i << std::endl;
        return i + 10;
    }
};


int main()
{
    Concurrent conc;

    // Default policy (std::launch::deferred | std::launch::async)
    auto a1 = std::async(&Concurrent::test1, &conc, 42, "Hello");

    // Lazy evaluation
    auto a2 = std::async(std::launch::deferred, &Concurrent::test2, conc, "world!"); 

    // Asynchronous evaluation
    auto a3 = std::async(std::launch::async, Concurrent(), 43);       

    a2.wait(); // We need a2 to be launched
    std::cout << a3.get() << std::endl;

    // Destructor of a1 will force thread of a1 to be launched at latest here.
    return 0;
}
