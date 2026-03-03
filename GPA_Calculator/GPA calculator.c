#include<stdio.h>

void main(){
    char STUDENT_NAME[25] , STUDENT_COURSE_CODE , GRADE;
    int STUDENT_ID = "KPKL";
    int CREDIT_HOUR_AAA10003 , CREDIT_HOUR_AAA1014 , QUALITY_POINT_AAA10003 , QUALITY_POINT_AAA1014 , CGPA , TOTAL_CREDIT_HOUR , TOTAL_QUALITY_POINT;
    float GPA , GRADE_POINT , QUALITY_POINT;

    CREDIT_HOUR_AAA10003 = '3';
    CREDIT_HOUR_AAA1014 = '4';

    printf("Enter student name : ");
    printf("Enter student ID : ");
    printf("Enter student course code : ");
    printf("Enter your  grade_AAA1003 : ");
    printf("Enter your grade_AAA1014 : ");

    //Quality Point (for AAA1003)
    QUALITY_POINT_AAA10003 = gets("grade_AAA1003");
    //Quality Point (for AAA1014)
    QUALITY_POINT_AAA1014 = gets("grade_1014");

    if(GRADE == 'A'){
        GRADE_POINT = 4.00;
    }

    else if(GRADE == 'A-'){
        GRADE_POINT = 3.75;
    }

    else if(GRADE == 'B+'){
        GRADE_POINT = 3.50;
    }

    else if(GRADE == 'B'){
        GRADE_POINT = 3.00;
    }

    else if(GRADE == 'B-'){
        GRADE_POINT = 2.75;
    }

    else if(GRADE == 'C+'){
        GRADE_POINT =  2.50;
    }

    else if(GRADE == 'C'){
        GRADE_POINT = 2.00;
    }

    else if(GRADE == 'F'){
        GRADE_POINT = 0.00;
    }

    else{
        printf("ERROR");
    }

    //Calculate 𝑄𝑢𝑎𝑙𝑖𝑡𝑦 𝑃𝑜𝑖𝑛𝑡 AAA10003
    QUALITY_POINT_AAA10003 = GRADE_POINT * CREDIT_HOUR_AAA10003 ;

    //Calculate 𝑄𝑢𝑎𝑙𝑖𝑡𝑦 𝑃𝑜𝑖𝑛𝑡 AAA1014
    QUALITY_POINT_AAA1014 = GRADE_POINT * CREDIT_HOUR_AAA1014 ;

    //Total Quality Point
    TOTAL_QUALITY_POINT = QUALITY_POINT_AAA10003 + QUALITY_POINT_AAA1014 ;

    //Total Credit Hours
    TOTAL_CREDIT_HOUR = CREDIT_HOUR_AAA10003 + CREDIT_HOUR_AAA1014 ;

    //Calculate GPA
    GPA = TOTAL_QUALITY_POINT / TOTAL_CREDIT_HOUR ;
    printf("%d" , GPA);

    //Calculate CGPA
    CGPA = TOTAL_QUALITY_POINT / TOTAL_CREDIT_HOUR ;
    printf("%d" , CGPA);

    return 0;
}
