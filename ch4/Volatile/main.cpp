// NOTE: Compile Code with optimizations enabled!
#include <vector>
#include <iostream>
#include <thread>

using namespace std;

void volatileTestSingleThreaded()
{
    //const int local = 10; // Achtung: Weil const, denkt Compiler, dass local sich nie etwas ändert ...
    const volatile int local = 10;
    int *ptr = (int*) &local;

    cout << "Initial value of local: " << local << endl;

    *ptr = 100; // ... doch der Pointer-Trick sollte den Wert verändern. -> Wiederspruch zu const

    cout << "Modified value of local: " << local << endl;
}

volatile int a = 0;
volatile int b = 0;

void push()
{    
    a = 42;
    b = 3000;
}

void pull()
{
    cout << "b = " << b << endl;
    cout << "a = " << a << endl;
}

int main()
{
    volatileTestSingleThreaded();

    thread t_pull(pull);
    thread t_push(push);
    
    t_pull.join();
    t_push.join();

    return 0;
}
