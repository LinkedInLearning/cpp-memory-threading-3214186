#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> counter(0);
//bool flag = false;
std::atomic<bool> flag{false};

void incrementCounter()
{
    counter.fetch_add(1, std::memory_order_relaxed);
    //flag = true;
    flag.store(true, std::memory_order_release);
}

void checkCounter()
{
    while (!flag);
    //while (!flag.load(std::memory_order_acquire));
    std::cout << "Counter value: " << counter.load(std::memory_order_relaxed) << std::endl;
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(checkCounter);
    t1.join();
    t2.join();
    return 0;
}
