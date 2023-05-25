#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> x(0),y(0);

void func_store() {
    x.store(100, std::memory_order_relaxed);
    y.store(100, std::memory_order_release);    
}

void func_load() {
    while(y.load(std::memory_order_acquire) <= 0);
    if(x.load(std::memory_order_relaxed) > 0)
    {
        std::cout << "y und x sind groesser als 0" << std::endl;
    }
}

int main() {
    std::thread t1(func_store);
    std::thread t2(func_load);
    t1.join();
    t2.join();
}
