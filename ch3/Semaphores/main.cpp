#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;             // mutex for critical section
std::condition_variable cv; // condition variable for critical section
bool ready = false;         // Tell threads to run
int current = 0;            // current count

// Prints the thread id / max number of threads
void print_num(const int num, const int max) {

    std::unique_lock<std::mutex> lck(mtx);

    while(!ready || num != current){ cv.wait(lck); }

    current++;
    std::cout << "Thread: ";
    std::cout << num + 1 << " / " << max;
    std::cout << " current count is: ";
    std::cout << current << std::endl;

    // Notify next threads to check if it is their turn
    cv.notify_all();
}

// Changes ready to true, and begins the threads printing
void run() {

    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    cv.notify_all();
}

int main () {

    constexpr int threadnum = 15;
    std::array<std::thread, threadnum> threads;

    // spawn threadnum threads 
    int id = 0;
    for (auto &th : threads)    {
        th = std::thread(print_num, id++, threadnum);
    }

    std::cout << std::endl << "Running " << threadnum;
    std::cout << " in parallel: " << std::endl << std::endl;

    run(); // Allows threads to run

    // Merge all threads to the main thread 
    for (auto &th : threads)    {
        th.join();
    }

    std::cout << std::endl << "Completed semaphore example!";
    std::cout << std::endl;

    return 0;
}
