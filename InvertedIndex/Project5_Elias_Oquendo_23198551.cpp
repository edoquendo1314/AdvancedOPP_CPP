#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

fstream inFile;

class invertedIndex{
    private:
        map<string, pair<int, vector<int>>> index;
    public: 

    void add(string s, int row, int col) 
    {
        map<string, pair<int, vector<int>>>::iterator i = index.find(s);

        if (i != index.end())
        {
            i->second.first += 1;
            i->second.second.push_back(row);
            i->second.second.push_back(col);
        }
        else
        {
            index[s] = {1, {row, col}};
        }
    }

    //REFACTOR OUTPUT
    void output() 
    {
        int count {0};

        for (auto x: index) 
        {
            cout << x.first << " " << x.second.first<<"[";

            for (auto y: x.second.second) 
            {
                int modResult = count % 2; 

                if (modResult == 1) 
                {
                    cout << y << ")";
                    count++;
                }
                else if (modResult == 0) 
                {
                    cout << "(" << y << ",";
                    count++;
                } 
            }
            cout << "]" << endl << endl;
            count = 0;
        }
    }
};

int main(int argc, char *argv[])
{
    inFile.open(argv[1], ios::in);

    int cnt {1}; 
    invertedIndex object; 
    size_t column;
    string word;
    string stored_value; 

    if(!inFile.is_open())
    {
        cerr << "error in opening file" <<endl;
        return 0; 
    }
    else
    {
         while(getline(inFile, stored_value))
         {
             istringstream words(stored_value);
             while(words >> word)
             {
                 column = stored_value.find(word);
                 for(int i = 0; i < word.length(); i++)
                 {
                     if(word[i] == ',' || word[i] == '.')
                     {
                         word.erase(word.begin() + i); 
                     }
                 }
                object.add(word, cnt, int(column)); 
             }
             cnt += 1; 
         }
    }
    
    inFile.close(); 
    object.output(); 
}
