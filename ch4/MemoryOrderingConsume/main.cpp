#include <thread>
#include <atomic>
#include <cassert>
#include <string>

// Inspiriert von https://en.cppreference.com/w/cpp/atomic/memory_order (2023-05-07)
// ACHTUNG: std::memory_order_consume wird mit std::memory_order_acquire von
// den meisten Compilern gleichgesetzt.

std::atomic<std::string*> ptr(nullptr);
int data = 0;

void producer()
{
    std::string* p  = new std::string("Hallo Welt");
    data = 42;
    ptr.store(p, std::memory_order_release); // Zeiger auf String an alle anderen Threads freigeben
}

void consumer()
{
    std::string* p2 = nullptr;

    while (!(p2 = ptr.load(std::memory_order_consume))); // Warten bis ptr von producer() gesetzt wurde

    assert(*p2 == "Hallo Welt"); // Kein Fehler: *p2 ist abhängig von ptr
    assert(data == 42); // Könnte Fehler werfen: Data ist unabhängig von ptr
                        // Mit std::memory_order_acquire wäre der Fehler ausgeschlossen.
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); t2.join();
}
