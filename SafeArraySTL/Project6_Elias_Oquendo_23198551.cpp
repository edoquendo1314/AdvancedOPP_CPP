#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

class SA
{
private: 
    int low, high;
    int *p;
public:

    //default constructor
    //allows for writing things like SA a;

    SA(){low = 0; high=-1; p=NULL;}

    //2 parameter constructor lets us write
    //SA x(10,20)

    SA(int l, int h)
    {
        if((h-l+1)<=0)
        {cout<<"constructor error in bounds definition"<<endl;
        exit(1);}
        low=1;
        high=h;
        p=new int[h-l+1];
    }

    //single parameter constructor lets us 
    //create a SA almost like a "standard" one by writing
    //SA x(10); and getting an array x indexed from 0 to 9

    SA(int i)
    {
        low=0; high=i-1;
        p=new int[i];
    }

    //copy constructor for pass by value and 
    //initialization

    SA(const SA &s)
    {
        int size = s.high - s.low + 1;
        p = new int[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
    }

    //destructor

    ~SA(){
        delete [] p;
    }

    int& operator[](int i)
    {
        if(i < low || i > high)
        {
            cout<<"index"<<i<<"out of range"<<endl;
            exit(1);
        }
        return p[i-low];
    }

    SA &operator+(const SA &s)
    {
        SA res;
    }
    // overloaded assignment lets us assign 
     // one SA to another 
     SA & operator=(const SA & s)
     {
        if(this==&s)return *this;

        delete [] p;
        int size=s.high-s.low+1; 
        p=new int[size];

        for(int i=0; i<size; i++)
            p[i]=s.p[i];

        low=s.low;
        high=s.high;                        
        return *this;
    }            
    // overloads << so we can directly print SAs 
    friend ostream& operator<<(ostream& os, SA s); 
    
};

//SafeArray overloaded <<
ostream& operator<<(ostream& os, SA s)
{
    int size=s.high-s.low+1; 
    for(int i=0; i<size; i++)
        cout<<s.p[i]<<endl;
    return os;
};


int main()
{
    SA a(10);

    for(int i = 0; i < 10; i++)
    {
        a[i] = i;

    }
    int *b = new int[10];

    for(int i = 0; i < 10; i++)
    {
        b[i] = a[i]; 
    }

    std::vector<int> myvector(b, b+10); 

    std::sort(myvector.begin(), myvector.begin() + 4); 

    auto it = std::find(myvector.begin(), myvector.end(), 6);

    if(it != myvector.end())
    {
        cout<< "Element found in SA: " << *it << '\n';
    }
    else
    {
        cout << "Element not found in SA \n"; 
    }
    
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';

    return 0; 
}
