 
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

/*
Dieses Programm weist ein undefiniertes Verhalten auf.
Die Aufgabe ist es den Code so umzustellen, dass
folgende Ergebnisse erlaubt sind:
(b==0, a==0) (b==3000, a==42) (b==3000, a==0) (b==0, a==42)

Um welches Modell handelt es sich? Welches Model würden Sie einsetzen
um folgende Kombination von Ergebnissen zu erreichen?:
(b==0, a==0) (b==3000, a==42) (b==0, a==42)

*/

using namespace std;

atomic<int> a(0);
atomic<int> b(0);


void push_relax()
{
    a.store(42, memory_order_relaxed);
    b.store(3000, memory_order_relaxed);
}

void pull_relax()
{
    cout << "b = " << b.load(memory_order_relaxed) << endl;
    cout << "a = " << a.load(memory_order_relaxed) << endl;
}

void push_stricter()
{
    a.store(42, memory_order_relaxed);
    b.store(3000, memory_order_release);
}

void pull_stricter()
{
    cout << "b = " << b.load(memory_order_acquire) << endl;
    cout << "a = " << a.load(memory_order_relaxed) << endl;
}

int main()
{
    thread t_push_relax(push_relax);
    thread t_pull_relax(pull_relax);

    t_push_relax.join();
    t_pull_relax.join();

    thread t_push_stricter(push_stricter);
    thread t_pull_stricter(pull_stricter);

    t_push_stricter.join();
    t_pull_stricter.join();

    return 0;
}
