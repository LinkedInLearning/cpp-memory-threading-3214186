#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class MeyerSingleton
{
public:
    // Returns the single instance of the class
    static T& get()
    {
        static T instance;
        return instance;
    }

    // Delete the copy constructor and assignment operator
    MeyerSingleton(const T&) = delete;
    MeyerSingleton& operator=(const T&) = delete;

protected:
    // Protected constructor to prevent creation of objects from outside
    MeyerSingleton() {}

    // Protected destructor to prevent deletion from outside
    ~MeyerSingleton() {}
};

#endif // SINGLETON_H
