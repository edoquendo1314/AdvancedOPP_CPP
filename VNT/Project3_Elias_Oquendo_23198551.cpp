#include <iostream>
#include <cstdlib>
#include <cassert>
#include <climits>

using namespace std;

template<class T>
class SA;
template<class T>
ostream& operator <<(ostream& os, SA<T> s);
template<class T>
class SM;
template<class T>
ostream& operator <<(ostream& os, SM<T> s);

template<class T>
class SA
{
private: 
    int low, high;
    T *p;
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
        p=new T[h-l+1];
    }

    //single parameter constructor lets us 
    //create a SA almost like a "standard" one by writing
    //SA x(10); and getting an array x indexed from 0 to 9

    SA(int i)
    {
        low=0; high=i-1;
        p=new T[i];
    }

    //copy constructor for pass by value and 
    //initialization

    SA(const SA &s)
    {
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
    }

    //destructor

    ~SA(){
        delete [] p;
    }

    T& operator[](int i)
    {
        if(i < low || i > high)
        {
            cout<<"index"<<i<<"out of range"<<endl;
            exit(1);
        }
        return p[i-low];
    }

    // overloaded assignment lets us assign 
     // one SA to another 
     SA & operator=(const SA & s)
     {
        if(this==&s)return *this;

        delete [] p;
        int size=s.high-s.low+1; 
        p=new T[size];

        for(int i=0; i<size; i++)
            p[i]=s.p[i];

        low=s.low;
        high=s.high;                        
        return *this;
    }            
    // overloads << so we can directly print SAs 
    friend ostream& operator<< <T>(ostream& os, SA<T> s); 
    
};

//SafeArray overloaded <<
template<class T>
ostream& operator<<(ostream& os, SA<T> s)
{
    int size=s.high-s.low+1; 
    for(int i=0; i<size; i++)
        cout<<s.p[i]<<endl;
    return os;
};


template<class T> 
class SM
{
private:
    int row_low, row_high, col_low, col_high;

    SA<SA<T>> p;
public:

    SM(const int row_Size, const int col_Size)
    {
      if(row_Size <= 0 || col_Size <= 0)			
        {
            cerr << "invalid construction" << endl;
            exit(1);
        }
        else if(row_Size == col_Size)			
        {
            int size = row_Size;
            row_low = col_low = 0;
            row_high = col_high = size - 1;
            p = SA<SA<T>> (size);			
            for(int i=0; i < size; i++)
            {
                p[i] = SA<T>(size);
            }		
        }
        else								
        {
            row_low = col_low = 0;
            row_high = row_Size - 1;
            col_high = col_Size - 1;
            p = SA<SA<T>>(row_Size);

            for(int i=0; i<row_Size; i++)
            {
                p[i] = SA<T>(col_Size);	
            }
        }
    }

    //constructor
    SM(int rl, int rh, int cl, int ch)
    {
        if(((rh - rl + 1) <= 0) || ((ch - cl + 1) <= 0))	
        {
            cerr<< "array is out of bounds" <<endl;
            exit(1);
        }
        this->row_low = rl;
        this->row_high = rh;
        this->col_low = cl;
        this->col_high = ch;

        p = SA<SA<T>>(row_low, row_high);		
        for(int i = row_low; i <= row_high; i++)
        {
            p[i] = SA<T>(col_low, col_high);
        }
    }
    
        SA<T>& operator[](int i)
    {
        if((i < row_low || i > row_high) && (i < col_low || i > col_high))
        {
            cerr<<"index"<<i<<"out of range"<<endl; 
        }
        return p[i];
    }

    //overload *
    SM<T> operator*(SM& rhs)
    {   
        int cS = col_high - col_low + 1;
        int sS = row_high - row_low + 1;
        //check column size
        if(cS != sS)
        {
            cerr<<"invalid size for multiplication"<<endl;
            exit(1); 
        }
        
        int lr = row_high - row_low + 1;	
		int lc = col_high - col_low + 1;
		int rr = rhs.row_high - rhs.row_low + 1;
		int rc = rhs.col_high - rhs.col_low + 1;	
        SM<T> result_Matrix(lr, rc);
        for(int x = 0; x < lr; x++){
            for(int y = 0; y < rc; y++)
            {
                result_Matrix[x][y] = 0;
            }
        }

        for(int i = 0; i < lr; i++){
            for(int j = 0; j < rc; j++){
                for(int k = 0; k < rc; k++)
                {
                    result_Matrix[i][j] += (*this)[i+row_low][k + col_low] * rhs[k + rhs.row_low][j + rhs.col_low]; 
                }
            }
        }

        return result_Matrix;
    }
   
    friend ostream& operator<<<T>(ostream& os, SM<T> s);
};

//SM overloaded <<
template<class T>
ostream& operator<<(ostream& os, SM<T> s)
{
    int size=s.row_Size-s.col_Size+1; 
    for(int i=0; i<size; i++)
        cout<<s.p[i]<<endl;
    return os;
};

class VNT 
{
    int m, n;
    SM<int> p;

public:
    
    VNT(int m, int n):p(SM<int>(m, n)) 
    {
        m = 0;
        n = 0;

        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j)
            {
                p[i][j] = INT_MAX;
            }
        }
    }

    int getMin() 
    {
        if (p[0][0] == INT_MAX) 
        {
            cout << "table is empty" << endl;
            return INT_MAX;
        }
        else 
        {
            int minVal = p[0][0];
            int rows = 0, cols = 0;

            while (rows < m - 1) 
            {
                cols = 0;
                if (p[rows + 1][cols] > p[rows][cols])
                    swap(p[rows + 1][cols], p[rows][cols]);
                while (cols < n - 1) 
                {
                    if (rows == m - 2 && (p[rows + 1][cols + 1] > p[rows + 1][cols])) 
                    {
                        swap(p[rows + 1][cols + 1], p[rows + 1][cols]);
                        swap(p[rows][cols + 1], p[rows][cols]);
                    }
                    else if (p[rows][cols + 1] < p[rows][cols]) 
                    {
                        swap(p[rows][cols + 1], p[rows][cols]);
                    }
                    cols++;
                }
                rows++;
            }
            p[m - 1][n - 1] = INT_MAX;
            return minVal;
        }
    }

    bool find(int var) 
    {
        int rows = m - 1; 
        int cols = 0;

        while (rows >= 0) 
        {
            if (var < p[rows][cols]) 
            {
                rows--;
            }
            else if (var > p[rows][cols]) 
            {
                while (cols <= m - 1) 
                {
                    cols++;
                    if (var == p[rows][cols])
                    {
                        return true;
                    }
                    else if (var < p[rows][cols])
                    {
                        return false;
                    } 
                }
            }
            else
            { 
                return true;
            }

        return false;
        }
    }

    void sort(int *arr, int size) 
    {
        for (int i = 0; i < size; ++i)
        {
            add(arr[i]);
        }
        for (int i = 0; i < size; ++i)
        {
            arr[i] = getMin();
        }
    }


     int* add(int value) 
    {
        // If VNT is full
        if (p[m - 1][n - 1] < INT_MAX) 
        {
            cout << "table is full" << endl;
        }
        else 
        {
            p[m - 1][n - 1] = value;
            int rows = m - 1, cols = n - 1;

            while (rows > 0) 
            {
                cols = n - 1;
                if (p[rows - 1][cols] > p[rows][cols])
                    swap(p[rows - 1][cols], p[rows][cols]);
                while (cols > 0) 
                {
                    if (rows == 1 && (p[rows - 1][cols - 1] > p[rows - 1][cols])) {
                        swap(p[rows - 1][cols - 1], p[rows - 1][cols]);
                        swap(p[rows][cols - 1], p[rows][cols]);
                    }
                    else if (p[rows][cols - 1] > p[rows][cols]) {
                        swap(p[rows][cols - 1], p[rows][cols]);
                    }
                    cols--;
                }
                rows--;
            }
        }
    }

};

int main()
{
    int rows = 5;
    int cols = 6; 
    VNT matrix(rows, cols);
    int *arr = new int[cols];

    for(int i = 0; i < cols; i++)
    {
        arr[i] = i; 
    }

    matrix.sort(arr, cols); 
    bool value = matrix.find(3);
    cout << "Did it find the value?: " << value << endl; 

    return 0; 
}
