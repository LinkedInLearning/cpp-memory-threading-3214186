#include <thread>
#include <mutex>
#include <iostream>

int main()
{
    std::mutex mutex;

    std::thread t1( [&]
    {
        mutex.lock();
        std::cout << "1. Lock" << std::endl;
        std::cout << "1. My turn!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "1. Still my turn!" << std::endl;
        std::cout << "1. Unlock" << std::endl;
        mutex.unlock();
    });
    std::thread t2( [&]
    {
        mutex.lock();
        std::cout << "2. Lock" << std::endl;
        std::cout << "2. My turn!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "2. Still my turn!" << std::endl;
        std::cout << "2. Unlock" << std::endl;
        mutex.unlock();
    });

    t1.join();
    t2.join();
}
