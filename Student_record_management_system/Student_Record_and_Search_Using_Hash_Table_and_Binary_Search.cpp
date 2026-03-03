#include "Student.cpp"
#include "Student_Class.h"
#include "Hash_Table.h"
#include "Binary_Search.h"

#include<iostream>
using namespace std;

int main()
{
    Student Student_Number_1(1221106664 , "Lee Wei Kang" , 3.83);
    Student Student_Number_2(1221106032 , "Lim Chuen Shen" , 2.99);
    Student Student_Number_3(1221102237 , "Muhammand Ali bin Ammar" , 3.79);
    Student Student_Number_4(1221107871 , "Puneke A/P Aurangabadker" , 3.94);
    Student Student_Number_5(1221103318 , "Joey Chua Jia Yun" , 2.96);
    Student Student_Number_6(1221109580 , "Craig Srouji" , 3.52);

    Hash_Table HT;
    HT.Insert_Value(1221106664, &Student_Number_1);
    HT.Insert_Value(1221106032, &Student_Number_2);
    HT.Insert_Value(1221102237, &Student_Number_3);
    HT.Insert_Value(1221107871, &Student_Number_4);
    HT.Insert_Value(1221103318, &Student_Number_5);
    HT.Insert_Value(1221109580, &Student_Number_6);

    int Search_ID = 1221106032;
    Student* found = HT.Hash_Search(Search_ID);

    if(found != NULL)
    {
        cout << "The name of the student is: " << found -> Student_NAME() << endl;

    }else{

        cout << "Student not found in hash table!" << endl;
    }

    int arr_ID[] = {1221102237, 1221103318, 1221106032, 1221106664, 1221107871, 1221109580};
    int index  = Binary_Search::binary_Search(arr_ID, 0, 5, Search_ID);

    if(index !=  -1)
    {
        cout << "The Student ID found at index: " << index << endl;

    }else{

        cout << "ID not found at any index using binary search!" << endl;
    }

    return 0;
}
