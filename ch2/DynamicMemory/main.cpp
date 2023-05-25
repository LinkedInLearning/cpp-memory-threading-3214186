#include <iostream>

int main()
{
    int size = 0;

    std::cout << "Wie viele Zahlen moechten Sie speichern? ";
    std::cin >> size;

    if(size <= 0)
    {
        std::cout << "Bitte eine realistische Zahl angeben.";
        return 1;
    }

    // Dynamische Speicherallokation für das Array
    int* array = new int[size];

    // Werte für das Array vom Benutzer einlesen
    for (int i = 0; i < size; i++) {
        std::cout << "Geben Sie die " << i+1 << ". Zahl ein: ";
        std::cin >> array[i];
    }

    // Array ausgeben
    std::cout << "Die eingegebenen Zahlen sind: ";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Dynamisch allokierten Speicher freigeben
    delete[] array;

    return 0;
}
