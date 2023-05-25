#include <iostream>
#include <memory>

struct MyVector {
  int mNum = 0;
  std::unique_ptr<int[]> mValues = nullptr;
};

int main()
{    
    auto pMyVec = std::unique_ptr<MyVector>(new MyVector);
    int num = 0;

    std::cout << "Wieviele Elemente brauchen Sie? ";
    std::cin >> num;

    pMyVec->mNum = num;
    pMyVec->mValues = std::unique_ptr<int[]>(new int[pMyVec->mNum]);

    for(int i=0 ; i<pMyVec->mNum ; i++) {
        std::cout << "Element " << i << " hat folgenden Wert: ";
        std::cin >> pMyVec->mValues[i];
    }

    std::cout << "Eingegebene Werte sind wie folgt:" << std::endl;

    int sum = 0;
    for(int i=0 ; i<pMyVec->mNum ; i++) {
        std::cout << pMyVec->mValues[i] << std::endl;
        sum += pMyVec->mValues[i];
    }

    std::cout << "Die Summe ist: " << sum << std::endl;

    return 0;
}