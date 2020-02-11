///////////////////////////////////////////////////////////////////////////////

//                   

// Author:           Brian Frempa-Dekyi

// Email:            brian.dekyi@yahoo.com

// Label:            02-A02

// Title:            Commented Code

// Course:           CMPS 2143

// Semester:         SPRING 2020

//

// Description:

//       This assingment is to put comments in the assignment below 

//

/////////////////////////////////////////////////////////////////////////////////







#include <iostream>







using namespace std;







int A[100]; // Array of 100





// Creates a struct

struct Node



{



    int x; // a node contains an int x



    Node *next; 



    Node() // an empty node



    {



        x = -1; // the value in x is -1



        next = NULL; // the node after next is NULL



    }



    Node(int n) // a node that contains int n



    {



        x = n; // the value in x is n



        next = NULL;



    }



};





// Creates a class

class List



{



  private:



    Node *Head; // node begins with a head



    Node *Tail; // node ends with a tail



    int Size; // node is determined by Size







  public:



    List()



    {



        Head = Tail = NULL; // The head, tail and Null are the same



        Size = 0; // The Size is 0



    }







    void Push(int val)



    {



        // allocate new memory and init node



        Node *Temp = new Node(val);







        if (!Head && !Tail) // if not head and not tail then...



        {



            Head = Tail = Temp; // head is the same as tail and temp



        }



        else // or else...



        {



            Tail->next = Temp; // the node after tail is temp



            Tail = Temp; // tail is the same as temp



        }



        Size++; // it increments



    }







    void Insert(int val)



    {



        // allocate new memory and init node



        Node *Temp = new Node(val);







        // figure out where it goes in the list







        Temp->next = Head; the node after temp is head



        Head = Temp; // head is the same as temp



        if (!Tail) // if not head then...



        {



            Tail = Head; // tail is the same as head



        }



        Size++;



    }







    void PrintTail()



    {



        cout << Tail->x << endl; // it prints "Tail->" and whatever the value of x is"



    }







    string Print()



    {



        Node *Temp = Head; // the pointer to temp is head

        

        // creates a list consisting of strings

        string list;







        while (Temp != NULL) // while temp is not NULL

       



        {



            list += to_string(Temp->x) + "->"; 



            Temp = Temp->next;



        }







        return list;



    }







    // not implemented 



    int Pop()



    {



        Size--; // it decrements



        return 0; // returns 0



    }







    List operator+(const List &Rhs)



    {



        // Create a new list that will contain both when done



        List NewList;







        // Get a reference to beginning of local list



        Node *Temp = Head;







        // Loop through local list and Push values onto new list



        while (Temp != NULL)



        {



            NewList.Push(Temp->x);



            Temp = Temp->next;



        }







        // Get a reference to head of Rhs



        Temp = Rhs.Head;







        // Same as above, loop and push



        while (Temp != NULL)



        {



            NewList.Push(Temp->x);



            Temp = Temp->next;



        }







        // Return new concatenated version of lists



        return NewList;



    }







    // Implementation of [] operator.  This function returns an



    // int value as if the list were an array.



    int operator[](int index)



    {



        Node *Temp = Head;







        if (index >= Size)



        {



            cout << "Index out of bounds, exiting";



            exit(0);



        }



        else



        {





            

            for (int i = 0; i < index; i++) // creates a for loop



            {



                Temp = Temp->next;



            }



            return Temp->x;



        }



    }







    friend ostream &operator<<(ostream &os, List L)



    {



        os << L.Print();



        return os;



    }



};







int main(int argc, char **argv)



{



    List L1;



    List L2;







    for (int i = 0; i < 25; i++)



    {



        L1.Push(i);



    }







    for (int i = 50; i < 100; i++)



    {



        L2.Push(i);



    }







    //cout << L1 << endl;



    L1.PrintTail();



    L2.PrintTail();







    List L3 = L1 + L2;



    cout << L3 << endl;







    cout << L3[5] << endl;



    return 0;



}
