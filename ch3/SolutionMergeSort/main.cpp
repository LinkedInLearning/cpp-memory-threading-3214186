#include <iostream>
#include <vector>
#include <future>
#include <atomic>

using namespace std;

static void measureTimeOf(function<void()> function, const string &desc)
{
    const auto start = chrono::high_resolution_clock::now();
    function();
    const auto end = chrono::high_resolution_clock::now();

    const auto elapsed = chrono::duration<double>(end-start);
    cout << desc << ": Time: " << elapsed.count() << " seconds" << endl;
}

void merge(const int low, const int mid, const int high, vector<int>&num)
{
    vector<int> copy(num.size());
    int h,i,j,k;
    h=low;
    i=low;
    j=mid+1;

    while((h<=mid)&&(j<=high))
    {
        if(num[h]<=num[j])
        {
            copy[i]=num[h];
            h++;
        }
        else
        {
            copy[i]=num[j];
            j++;
        }
        i++;
    }

    if(h>mid)
    {
        for(k=j;k<=high;k++)
        {
            copy[i]=num[k];
            i++;
        }
    }
    else
    {
        for(k=h;k<=mid;k++)
        {
            copy[i]=num[k];
            i++;
        }
    }

    for(k=low;k<=high;k++)
    {
        swap(num[k],copy[k]);
    }
}

std::atomic<int> thread_ctr(0);
constexpr int maxNumThreads = 16;

void mergeSortParallel(int low,int high,vector<int>& num)
{
    int mid;
    if(low<high)
    {
        mid = low + (high-low)/2;
        if(thread_ctr.load() < maxNumThreads) 
        {
            thread_ctr.fetch_add(2);
            auto future1    =  std::async( [&]()
                                      {
                                          mergeSortParallel(low,mid,num);
                                      });
            auto future2    =  std::async( [&]()
                                       {
                                          mergeSortParallel(mid+1,high,num) ;
                                       });            
            future1.get();
            future2.get();
            thread_ctr.fetch_sub(2);
        }
        else {
            mergeSortParallel(low,mid,num);
            mergeSortParallel(mid+1,high,num);
        }

        merge(low,mid,high,num);
    }
}

void mergeSortSerial(int low,int high,vector<int>& num)
{
    int mid;
    if(low<high)
    {
        mid = low + (high-low)/2;
        mergeSortSerial(low,mid,num);
        mergeSortSerial(mid+1,high,num);
        merge(low,mid,high,num);
    }
}


void mergeSortParallel(vector<int>& num)
{
    mergeSortParallel(0, num.size(), num);
}

void mergeSortSerial(vector<int>& num)
{
    mergeSortSerial(0, num.size(), num);
}


int main()
{

    vector<int> num;

    constexpr int vecSize = 100'000;

    for( auto i=0 ; i<vecSize ; i++ )
    {
       num.push_back((i%100) * i+1);
    }

    auto numPara = num;
    auto numSer = num;


    measureTimeOf([&](){
        mergeSortSerial(numSer);
    },"MergesortSerial");

    measureTimeOf([&](){
        mergeSortParallel(numPara);
    },"MergesortParallel");


    /*
    cout << "numPara: " << endl;
    for(const auto &x : numPara)
    {
        cout << x << ", ";
    }
    cout << "numSer: " << endl;
    for(const auto &x : numSer)
    {
        cout << x << ", ";
    }
*/
    cout << endl;

    return 0;
}
