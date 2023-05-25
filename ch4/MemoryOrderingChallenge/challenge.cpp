 
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

int a = 0;
int b = 0;

using namespace std;

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
    thread t_push(push);
    thread t_pull(pull);

    t_push.join();
    t_pull.join();

    return 0;
}
