#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

//global variables
fstream inFile;
fstream outFile;

class ListNode
{
private:
    friend class linkedList; 
public:
    int coeff;
    int expon;
    ListNode* next;
    //regular constructor
    ListNode()
    {
        this->coeff = 0;
        this->expon = 0;
        this->next = nullptr;
    }

    ListNode(int coeff, int expon) : coeff(coeff), expon(expon)
    {}

    //Deep copy constructor
    ListNode(const ListNode &source)
    {
        next = new ListNode();
        next = source.next;

        cout<<"Copy constructor- Deep - data copy: " << next <<endl;
    }

    //Move Constructor
    ListNode(ListNode &&source)
    {
        next = new ListNode();
        next = source.next; 
        source.next = nullptr;
    }
};

class linkedList
{
    public:
        ListNode *head;
        ListNode *tail; 

        linkedList()
        {
            head = nullptr;
            tail = nullptr;  
        }

        void addNode(int coeff, int expon)
        {
            ListNode *temp = new ListNode(); 
            temp->coeff = coeff;
            temp->expon = expon; 
            temp->next = nullptr;
            std::cout<<endl; 
            std::cout << temp->coeff <<endl;
            std::cout << temp->expon <<endl;
            if(head == nullptr) 
            {
                head = temp;
                tail = temp; 
            }
            else 
            {
                tail->next = temp;
                tail = tail->next; 
            }
        }

        void canonicalOrder()
        {

            cout<<"in canonicalOrder" <<endl; 
            ListNode *current = head;
            cout << current->coeff <<endl;


            while(current->next != nullptr)
            { 
                if(current->expon < current->next->expon)
                {
                    std::swap(current->coeff, current->next->coeff);  
                    std::swap(current->expon, current->next->expon); 
                }

                current = current->next;
            }

            current = head; 

            while(current->next != nullptr)
            { 
                if(current->expon < current->next->expon)
                {
                    std::swap(current->coeff, current->next->coeff);  
                    std::swap(current->expon, current->next->expon); 
                }

                current = current->next;
            }

            current = head; 

            while(current->next != nullptr)
            { 
                if(current->expon < current->next->expon)
                {
                    std::swap(current->coeff, current->next->coeff);  
                    std::swap(current->expon, current->next->expon); 
                }

                current = current->next;
            }

            current = head; 

            while(current->next != nullptr)
            { 
                if(current->expon < current->next->expon)
                {
                    std::swap(current->coeff, current->next->coeff);  
                    std::swap(current->expon, current->next->expon); 
                }

                current = current->next;
            }

            ListNode *canonicalNode = head; 

            while(canonicalNode != nullptr)
            {
                outFile << canonicalNode->coeff << "x^" << canonicalNode->expon <<endl; 

                if(canonicalNode->next == nullptr)
                {
                    goto outofloop; 
                }  

                canonicalNode = canonicalNode->next;
            }

            outofloop:
            cout<<" " <<endl;

        }  

        void output()
        {
            ListNode obj1, obj2, obj3, obj4; 
            ListNode *temp = head;
            int counter = 0; 
            while(temp != nullptr)
            {
                cout << temp->coeff << temp->expon <<endl;
                if(counter == 0)
                {
                    obj1.coeff = temp->coeff; 
                    obj1.expon = temp->expon; 
                    cout << "OBJ1: " << obj1.coeff <<endl; 
                }
                else if(counter == 1)
                {
                    obj2.coeff = temp->coeff; 
                    obj2.expon = temp->expon; 
                }
                else if(counter == 2)
                {
                    obj3.coeff = temp->coeff; 
                    obj3.expon = temp->expon; 
                }
                else if(counter == 3)
                {
                    obj4.coeff = temp->coeff; 
                    obj4.expon = temp->expon; 
                }                
            
                counter++; 
                temp = temp->next;
            }

        
            //Addition------------------------------------
             if(obj1.expon == obj2.expon)
             {
                 int resultAdd = obj1.coeff + obj2.coeff;
                 outFile << "Addition: " << resultAdd << "x^" << obj1.expon <<endl; 
             }

            
            if(obj3.expon == obj4.expon)
            {
                 int resultAdd2 = obj3.coeff + obj4.coeff;
                 outFile << "2nd Addition: " << resultAdd2 << "x^" << obj3.expon <<endl; 
            }
             //Subtraction---------------------------------
             if(obj1.expon == obj2.expon)
             {
                 int resultSub = obj1.coeff - obj2.coeff;
                 outFile << "Subtraction: " << resultSub << "x^" << obj1.expon <<endl; 
             }

            
             if(obj3.expon == obj4.expon)
             {
                 int resultSub2 = obj3.coeff - obj4.coeff;
                 outFile << " 2nd Subtraction: " << resultSub2 << "x^" << obj4.expon <<endl;
             }
            //Multiplication------------------------------
                 int resultMulti = obj1.coeff * obj2.coeff * obj3.coeff * obj4.coeff;
                 int resultMultiAdd = obj1.expon + obj2.expon + obj3.expon + obj4.expon;

                 outFile << "Multiplication: " << resultMulti << "x^" << resultMultiAdd <<endl;

        }
};

int main(int argc, char *argv[])
{
    linkedList obj;
    inFile.open(argv[1], ios::in);
    outFile.open(argv[2], ios::out);

    int coeff, expon; 
    string line; 

    if(inFile.is_open())
    {
        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            while (ss >> coeff >> expon) 
            {
                cout << coeff << "," <<  expon << "   ";
                obj.addNode(coeff, expon); 
            }
            cout << endl;
        }
    }
    else
    {
        cerr<<"Could not open file" <<endl;
        return 1;
    }

    obj.canonicalOrder(); 
    obj.output();

    inFile.close(); 
    outFile.close();
}
