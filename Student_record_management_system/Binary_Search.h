#ifndef BINARY_SEARCH
#define BINARY_SEARCH

using namespace std;

class Binary_Search
{
    public:
        static int binary_Search(int arr_Student_ID[], int first, int last, int target)
        {
            int index;

            if(first > last)
            {
                index = -1;

            }else{

                int middle = (first + last) / 2;

                if(target == arr_Student_ID[middle])
                {
                    index = middle;

                }else if(target < arr_Student_ID[middle]){

                    index = binary_Search(arr_Student_ID, first, middle - 1, target);

                }else{

                    index = binary_Search(arr_Student_ID, middle + 1, last, target);
                }
            }
            return index;

        }
};

#endif
