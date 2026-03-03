#ifndef HASH_TABLE
#define HASH_TABLE
#include "Student_Class.h"

using namespace std;

const int TABLE_SIZE = 10;

class Hash_Table
{
    public:
        Hash_Table()
        {
            for(int i = 0; i < TABLE_SIZE; i++)
            {
                Table[i] = NULL;
            }
        }

        void Insert_Value(int Key_Student_ID, Student* Student_Number)
        {
            int Hash_Index = Hash_Function(Key_Student_ID);
            int Start_Index = Hash_Index;

            while (Table[Hash_Index] != NULL)
            {
                Hash_Index = (Hash_Index + 1) % TABLE_SIZE;

                if(Hash_Index == Start_Index)
                {
                    cout << "The hash table is full!" << endl;
                    cout << "Cannot insert new student!" << endl;
                    return;
                }
            }
            
            Table[Hash_Index] = Student_Number;
        }

        Student* Hash_Search(int Key_Student_ID)
        {
            int Hash_Index = Hash_Function(Key_Student_ID);
            int Start_Index = Hash_Index;

            while (Table[Hash_Index] != NULL)
            {
                if(Table[Hash_Index] -> Student_ID() == Key_Student_ID)
                {
                    return Table[Hash_Index];
                }

                Hash_Index = (Hash_Index + 1) % TABLE_SIZE;

                if(Hash_Index == Start_Index)
                {
                    break;
                }
            }

            return NULL;
        }

    private:
        Student* Table[TABLE_SIZE];

        int Hash_Function(int key)
        {
            return key % TABLE_SIZE;
        }
};

#endif
