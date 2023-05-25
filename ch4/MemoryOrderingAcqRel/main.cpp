#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> counter(0);

void increment_counter()
{
    for (int i = 0; i < 10'000; ++i)
    {
        counter.fetch_add(1, std::memory_order_acq_rel);
    }
}

int main() {
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);
    t1.join();
    t2.join();
    std::cout << "Counter value: " << counter << std::endl;
    return 0;
}
