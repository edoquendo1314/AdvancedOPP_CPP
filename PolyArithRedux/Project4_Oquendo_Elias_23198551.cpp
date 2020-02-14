#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <utility>
using namespace std;

class Polynomial 
{
    public:
    map<int, int> polynomial;
    bool indexed(int coefficient, int exponent);
    void variables(int coefficient, int exponent);

    Polynomial &operator+(const Polynomial &other) 
    {
        unique_ptr<Polynomial> addition(new Polynomial());
        for (auto i: this->polynomial) 
        {
            addition->variables(i.second, i.first);
        }
        for (auto j: other.polynomial) 
        {
            addition->variables(j.second, j.first);
        }
        return *addition;
    }

    Polynomial &operator-(const Polynomial &other) 
    {
        unique_ptr<Polynomial> subtraction(new Polynomial());
        for (auto i: this->polynomial) 
        {
            subtraction->variables(i.second, i.first);
        }
        for (auto j: other.polynomial) 
        {
            subtraction->variables((-1 * j.second), j.first);
        }
        return *subtraction;
    }

    Polynomial &operator*(const Polynomial &other) 
    {
        unique_ptr<Polynomial> result(new Polynomial());
        for (auto i: this->polynomial) 
        {
            for (auto j: other.polynomial) 
            {
                result->variables((i.second * j.second), (i.first + j.first));
            }
        }
        return *result;
    }
};

bool Polynomial :: indexed(int coefficient, int exponent) 
{
    map<int, int>::iterator iterator = polynomial.find(exponent);
    if (iterator != polynomial.end()) 
    {
        iterator->second += coefficient;
        return true;
    }
    return false;
}

void Polynomial :: variables(int coefficient, int exponent) 
{
    if (!(indexed(coefficient, exponent))) 
    {
        polynomial[exponent] = {coefficient};
    }
}


int main(int argc, char *argv[]) 
{

    Polynomial polyArr[2], addition, subtraction, multiplication;
    fstream inFile;
    fstream outFile;

    inFile.open(argv[1], ios::in);
    outFile.open(argv[2], ios::out);

    if(inFile.is_open())
    {   
        string line;
        int count = 0, coefficient, exponent;
        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            while (ss >> coefficient >> exponent) 
            {
                cout << coefficient << "," <<  exponent << "   ";
                polyArr[count].variables(coefficient, exponent);
            }
            cout << endl;
            count++;
        }
        inFile.close();
        
        outFile <<endl; 
        outFile << "1st polynomial: ";
        
        map<int, int>::iterator it;
        for (it = polyArr[0].polynomial.begin(); it != polyArr[0].polynomial.end(); ++it) 
        {
            if (it->second != 0) 
            {
                if (it == polyArr[0].polynomial.begin()) 
                {
                    outFile << it->second << "x^" << it->first;
                } 
                else if (it->second < 0) 
                {
                    outFile << " - " << (it->second * -1) << "x^" << it->first;
                }
                else 
                {
                    outFile << " + " << it->second << "x^" << it->first;
                }
            }
        }
        
        outFile <<endl; 
        outFile << "2nd polynomial: ";
        
        for (it = polyArr[1].polynomial.begin(); it != polyArr[1].polynomial.end(); ++it) 
        {
            if (it->second != 0) 
            {
                if (it == polyArr[1].polynomial.begin()) 
                {
                    outFile << it->second << "x^" << it->first;
                } 
                else if (it->second < 0) 
                {
                    outFile << " - " << (it->second * -1) << "x^" << it->first;
                } 
                else 
                {
                    outFile << " + " << it->second << "x^" << it->first;
                }
            }
        }
        
        outFile <<endl; 
        outFile << "1st canonical polynomial: ";   
        
        map<int, int>::reverse_iterator reverseIterator;

        for (reverseIterator = polyArr[0].polynomial.rbegin(); reverseIterator != polyArr[0].polynomial.rend(); ++reverseIterator) 
        {
            if (reverseIterator->second != 0) 
            {
                if (reverseIterator == polyArr[0].polynomial.rbegin()) 
                {
                    outFile << reverseIterator->second << "x^" << reverseIterator->first;
                } 
                else if (reverseIterator->second < 0) 
                {
                    outFile << " - " << (reverseIterator->second * -1) << "x^" << reverseIterator->first;
                } 
                else 
                {
                    outFile << " + " << reverseIterator->second << "x^" << reverseIterator->first;
                }
            }
        }
        
        outFile << endl;
        outFile << "2nd canonical polynomial: ";
        
        for (reverseIterator = polyArr[1].polynomial.rbegin(); reverseIterator != polyArr[1].polynomial.rend(); ++reverseIterator) 
        {
            if (reverseIterator->second != 0) 
            {
                if (reverseIterator == polyArr[1].polynomial.rbegin()) 
                {
                    outFile << reverseIterator->second << "x^" << reverseIterator->first;
                } 
                else if (reverseIterator->second < 0) 
                {
                    outFile << " - " << (reverseIterator->second * -1) << "x^" << reverseIterator->first;
                } 
                else 
                {
                    outFile << " + " << reverseIterator->second << "x^" << reverseIterator->first;
                }
            }
        }
        
        addition=polyArr[0]+polyArr[1];
        outFile <<endl;
        outFile << "Result of addition: ";
        
        for (reverseIterator = addition.polynomial.rbegin(); reverseIterator != addition.polynomial.rend(); ++reverseIterator) 
        {
            if (reverseIterator->second != 0) 
            {
                if (reverseIterator == addition.polynomial.rbegin()) 
                {
                    outFile << reverseIterator->second << "x^" << reverseIterator->first;
                } 
                else if (reverseIterator->second < 0) 
                {
                    outFile << " - " << (reverseIterator->second * -1) << "x^" << reverseIterator->first;
                } 
                else 
                {
                    outFile << " + " << reverseIterator->second << "x^" << reverseIterator->first;
                }
            }
        }
        
        outFile <<endl;
        outFile << "Result of subtraction: ";

        subtraction=polyArr[0]-polyArr[1];

        for (reverseIterator = subtraction.polynomial.rbegin(); reverseIterator != subtraction.polynomial.rend(); ++reverseIterator) 
        {
            if (reverseIterator->second != 0) 
            {
                if (reverseIterator == subtraction.polynomial.rbegin()) 
                {
                    outFile << reverseIterator->second << "x^" << reverseIterator->first;
                } 
                else if (reverseIterator->second < 0) 
                {
                    outFile << " - " << (reverseIterator->second * -1) << "x^" << reverseIterator->first;
                } 
                else 
                {
                    outFile << " + " << reverseIterator->second << "x^" << reverseIterator->first;
                }
            }
        }
        
        outFile <<endl; 
        outFile << "Result of multiplication: ";
        multiplication=polyArr[0]*polyArr[1];
        
        for (reverseIterator = multiplication.polynomial.rbegin(); reverseIterator != multiplication.polynomial.rend(); ++reverseIterator) 
        {
            if (reverseIterator->second != 0) 
            {
                if (reverseIterator == multiplication.polynomial.rbegin()) 
                {
                    outFile << reverseIterator->second << "x^" << reverseIterator->first;
                } 
                else if (reverseIterator->second < 0) 
                {
                    outFile << " - " << (reverseIterator->second * -1) << "x^" << reverseIterator->first;
                }
                else 
                {
                    outFile << " + " << reverseIterator->second << "x^" << reverseIterator->first;
                }
            }
        }
    }
    else
    {
        cerr<<"Could not open file" <<endl;
        exit(1);
    }

    outFile.close();
    return 0;
}