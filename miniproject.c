/**
 * **************************************************************************************************************
 * ==============================================================================================================
 * @file miniproject.c
 * @author Sadikshya Pokharel 
 *         psaishya@gmail.com
 * @brief This program reads a csv file, calculates and displays the precision and recall of the datas from file. 
 * @date 2021-08-14
 * @copyright Copyright (c) 2021
 * ===============================================================================================================
 * ***************************************************************************************************************
 */

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>

/************** Declaring the structure with members expected and actual ****************/
typedef struct datas{
    char expected;
    char actual;
}tdatas;  ///creating alias for datatype struct datas


/************* Declaring all the functions used in this program ***************/

void introduction(FILE *xy);
void fspace(int s);
void display(FILE *xy);
void count(tdatas value_arr[],int n_data,float *tp,float *fp,float *fn);
void fprecision(float tp,float fp);
void frecall(float tp,float fn);

/*============================================================================================================*/

/**
 * -------------------------------------------------------------------------------------------------------
 * @brief The main function
 * This is the entry point of the function.
 * In this function, we read a csv file that contains data for expected and actual values.
 * This function displays the menu then asks user to make a choice from the menu.
 * Then it calls different functions to perform different tasks.
 * @return int 
 * --------------------------------------------------------------------------------------------------------
 */
int main()
{   
    system("cls");
    
    FILE *xy;  ///declaring file pointer
    xy=fopen("MP_csv.csv","r");
    
    /**************** Calling the introduction function to display introduction of program**************/
    introduction(xy);
    
    printf("Displaying the contents of files.......");
    for(int f=0;f<20;f++){
        printf("\n");
    }

    printf("Please press enter to continue");
    getch();
    
    system("cls");
    /*----------------------------------------------------------------------------------------------------*/

    /**************** Calling the display function to display contents of file****************/
    display(xy);

    /**************** Counting the no. of rows in the file *****************/
    rewind(xy);
    char ch;
    int n_data=0;
    do
        {   
            ch=fgetc(xy);
            if(ch=='\n'){
                n_data++;
            }
        }while(ch!=EOF);

    tdatas value_arr[n_data];    /// declaring the array having n_data number of elements 
    
    rewind(xy);
    /// skipping the first heading line and setting the cursor to the start of second line
    do{
        ch=fgetc(xy);
        if(ch=='\n'){
            break;
        }
    }while(1);

    /************** Storing the datas from the file in the structure array : value_arr ****************/
    int i=0;
    do
        {   
            ch=fgetc(xy);
            value_arr[i].expected=toupper(ch);
            
            fseek(xy,1,SEEK_CUR);
            
            ch=fgetc(xy);
            value_arr[i].actual=toupper(ch);
           
            i++;
            ch=fgetc(xy);
            
        }while(ch!=EOF);
    
    float tp=0,fp=0,fn=0;

    /**************** Calling the count function the find value of tp fp and fn *****************/
    count(value_arr,n_data,&tp,&fp,&fn);

    /**************** Displaying values of tp fp and fn ******************/
    printf("\n\nHere,\n\nThe values are found to be\n\n"); 
    printf("    TRUE POSITIVE=%1.f              \'TP= no. of rows where Expected = Y and Actual =Y\'\n",tp);
    printf("    FALSE POSITIVE=%1.f             \'FP= no. of rows where Expected = Y and Actual =N\'\n",fp);
    printf("    FALSE NEGATIVE=%1.f             \'FN= no. of rows where Expected = N and Actual =Y\'\n\n",fn);
    
    /**************** Displaying the menu for the users *****************/
    make_selection: 

    for(int f=0;f<14;f++){
        printf("*-*_*-*_");
    }
    
    int selection;
    printf("\n\nWhat do you want to calculate?\n");
    printf("*****[Please select from the below mentioned options]*****\n");
    
    printf("\t\t1.  Precision\n");
    printf("\t\t2.  Recall\n");
    printf("\t\t3.  Both\n");
    printf("\t\t4.  Display the file contents again\n");
    printf("\t\t5.  Exit\n\n");

    for(int f=0;f<68;f++){
        printf("*");
    }
    printf("\n");
    scanf("%d",&selection);   ///taking the input from user for the menu selection

    system("cls");

    printf("\n\n\n\n");

    switch(selection)
    {
        case(1):   ///the user wants to calculate precision
            fprecision(tp,fp);
            goto make_selection;
            break;
            
        case(2):   ///the user wants to calculate recall
            frecall(tp,fn);
            goto make_selection;
            break;

        case(3):   ///the user wants to calculate both precision and recall
            fprecision(tp,fp);
            frecall(tp,fn);
            goto make_selection;
            break;

        case(4):   ///the user wants to display the contents of file again
            display(xy);
             
            printf("\nHere,\n\nThe values are found to be\n\n"); 
            printf("    TRUE POSITIVE=%1.f              \'TP= no. of rows where Expected = Y and Actual =Y\'\n",tp);
            printf("    FALSE POSITIVE=%1.f             \'FP= no. of rows where Expected = Y and Actual =N\'\n",fp);
            printf("    FALSE NEGATIVE=%1.f             \'FN= no. of rows where Expected = N and Actual =Y\'\n\n",fn);
            goto make_selection;
            break;    

        case(5):    ///the user wants to quit the program
            for(int f=0;f<10;f++){
                printf("\n");
            };
                printf("*****************\t\tThank you\t\t*******************");
            for(int f=0;f<18;f++){
                printf("\n");
            };
            exit(1);

        default:    ///the user made choices other than listed in the menu
            printf("\nInvalid choice\n");
            goto make_selection;
    }
    return 0;
}

/*==============================================================================================================*/

/**
 * @brief The introduction function
 * This function displays the introduction portion of the program.
 * @param xy , the file which is read by the program.
 * @return void
 */
void introduction(FILE *xy){
    printf("\n\n");
    fspace(6);
    for(int f=0;f<26;f++){
        printf("*");
    }
    printf("\n");
    fspace(6);
    printf("WELCOME TO MY MINI PROJECT\n");
    fspace(6);
    for(int f=0;f<26;f++){
        printf("*");
    }
    printf("\n\n\n\n\n");
    fspace(9);
    printf("Presented by:\n");
    fspace(9);
    printf("Sadikshya Pokharel\n");
    fspace(9);
    printf("Roll no.: 36\n");
    fspace(9);
    printf("Group:CE\n\n\n\n\t");
    for(int f=0;f<15;f++){
        printf("*-*_*-*_");
    }
    printf("\n\n\n\t\t In this program, we will be calculating the precision and recall from the data given in the csv file.\n");
    
    for(int f=0;f<10;f++){
        printf("\n");
    }
    
    int start;
    printf("Do you want to continue?\n");
    printf("\t1.\tYES  (Press any number)\n");
    printf("\t2.\tNO   (Press 2)\n");
    scanf("%d",&start);
    if(start==2){
        printf("\n\n***********\t\tThank you\t\t************\n\n");
        exit(1);
    }
    system("cls");

    /*************** Checking if the file is present or not ****************/
    printf("\n\nLet's check if the provided file is present or not.\n\n");
    printf("\n\nChecking.....");

    for(int f=0;f<20;f++){
        printf("\n");
    }

    printf("Please press enter to continue\n");
    getch();

    system("cls");

    if (xy==NULL){
        printf("File not present\n");
        printf("Please put the correct path of file\n");
        exit(1);
    }
    else{
        printf("\n\nFile is present\n\n");
    }

}

/*============================================================================================================*/

/**
 * -------------------------------------------------------------------------------------------------------
 * @brief the fspace function
 * This function prints the requored number of black space.
 * @param s which gives the the no. of blank spaces to be printed.
 * @return void 
 * -------------------------------------------------------------------------------------------------------
 */
void fspace(int s){
    
    for(int f=0;f<s;f++){
        printf("\t");
    }

}

/*==========================================================================================================*/

/**
 * -------------------------------------------------------------------------------------------------------
 * @brief the display function
 * This function reads individual character of the file.
 * It then displays the contents of the file.
 * @param xy , the file which has to be read.
 * @return void
 * --------------------------------------------------------------------------------------------------------
 */
void display(FILE *xy){
    rewind(xy);
    int ch;
    do
        {   
            ch=fgetc(xy);
            printf("%c",ch);
        }
        while(ch!=EOF);
    
    printf("\n\n");    

    for(int f=0;f<14;f++){
        printf("*-*_*-*_");
    }
}

/*============================================================================================================*/

/**
 * --------------------------------------------------------------------------------------------------------
 * @brief The count function.
 * This function counts the no. of tp, fp and fn.
 * @param value_arr, which is the structure array that contains the information from file
 * @param tp , True Positive (Expected=Y and Actual=Y)
 * @param fp , False Positive (Expected=Y and Actual=N)
 * @param fn , False Negative (Expected=N and Actual=Y)
 * @return void
 * ---------------------------------------------------------------------------------------------------------
 */
void count(struct datas value_arr[],int n_data,float *tp,float *fp,float *fn){
    int x=0;
    for(int j=0;j<n_data;j++)
    {   
        if((value_arr[j].expected=='Y')&&(value_arr[j].actual=='Y')){
            (*tp)++;
            
        }
        else if((value_arr[j].expected=='Y')&&(value_arr[j].actual=='N')){
            (*fp)++;
        }
        else if((value_arr[j].expected=='N')&&(value_arr[j].actual=='Y')){
            (*fn)++;
        }    
    }
}

/*============================================================================================================*/

/**
 * -----------------------------------------------------------------------------------------------------------
 * @brief The precision function
 * This function calculates the precision of the data.
 * It then displays the value of precision.
 * @param tp , True Positive (Expected=Y and Actual=Y)
 * @param fp , False Positive (Expected=Y and Actual=N)
 * @return void
 * -----------------------------------------------------------------------------------------------------------
 */
void fprecision(float tp,float fp)
{   
    float precision=tp/(tp+fp);
    
    printf("\nPrecision = TRUE POSITIVE / (TRUE POSITIVE + FALSE POSITIVE)");
    printf("\nThe precision of the given data is: %.2f\n\n\n\n",precision);

}

/*=============================================================================================================*/

/**
 * -------------------------------------------------------------------------------------------------------------
 * @brief The recall function
 * This function calculates the recall of the data.
 * It the displays the value of recall.
 * @param tp , True Positive (Expected=Y and Actual=Y)
 * @param fn , False Negative (Expected=N and Actual=Y)
 * @return void
 * -------------------------------------------------------------------------------------------------------------
 */
void frecall(float tp,float fn)
{
    float recall=tp/(tp+fn);
    
    printf("\nRecall = TRUE POSITIVE / (TRUE POSITIVE + FALSE NEGATIVE)");
    printf("\nThe recall of the given data is: %.2f\n\n\n\n",recall);
}
/*================================================================================================================*/