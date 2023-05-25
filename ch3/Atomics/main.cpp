#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

using namespace std;

atomic<int> atomic_counter = 0;
int non_atomic_counter = 0;

void incrementCounter()
{
    for (int j = 0; j < 10; ++j)
    {
        for (int i = 0; i < 1'000'000; ++i)
        {
            atomic_counter.fetch_add(1);
        }
    }
}

void incrementCounterNonAtomic()
{
    for (int j = 0; j < 10; ++j)
    {
        for (int i = 0; i < 1'000'000; ++i)
        {
            non_atomic_counter += 1;
        }
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    thread t1(incrementCounter);
    thread t2(incrementCounter);
    t1.join();
    t2.join();

    auto end = chrono::high_resolution_clock::now();
    const auto duration_atomic = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Zeit: " << duration_atomic.count() <<  " msecs. Der Wert von atomic_counter ist: " << atomic_counter << std::endl;

    {
        start = chrono::high_resolution_clock::now();
        thread t2(incrementCounterNonAtomic);
        thread t3(incrementCounterNonAtomic);
        t2.join();
        t3.join();
        end = chrono::high_resolution_clock::now();

        const auto duration_non_atomic = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Zeit: " << duration_non_atomic.count() <<  " msecs. Der Wert von non_atomic_counter ist: " << non_atomic_counter << std::endl;
    }

    return 0;
}
