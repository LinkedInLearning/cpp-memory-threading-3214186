#include <atomic>
#include <thread>
#include <iostream>

/**
 *  | x  | y    | possible? |
 *  | 0  | 0    |   yes     |
 *  | 0  | 4000 |   no      |
 *  | 10 | 0    |   yes     |
 *  | 10 | 4000 |   yes     |
 */

std::atomic<int> x(0),y(0);

void thread_store() {
    x.store(10, std::memory_order_seq_cst);
    y.store(4000, std::memory_order_seq_cst);
}

void thread_load() {
    std::cout << "y_val: " << y.load(std::memory_order_seq_cst) << ", ";
    std::cout << "x_val: " << x.load(std::memory_order_seq_cst) << std::endl;
}

int main()
{
    std::thread t1(thread_store);
    std::thread t2(thread_load);
    t1.join();
    t2.join();
}
