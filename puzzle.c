#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>

int board[9][9];
int rowsucc[9];
int colsucc[9];
int gridsucc[9];

//Function to check if a single row is correct
void *checkrows(void* args){
    //sets row to true
    int succ = 1;

    //rowval is which row it is on the board
    int rowval = *((int*)args);

    //initializes array for the counter of digits 0 to 9
    int row[10]={0};

    //Counts how many times a number appears in a row
    for(int i = 0; i < 9; i++){

        //ignoring zeroes
        if(board[rowval][i] != 0){

            //Add one to the counter for the digit
            row[board[rowval][i]] += 1;
        }

        //if a digit appears twice then row is unvalid, sets it to false and breaks
        if(row[board[rowval][i]] >= 2){
            succ = 0;
            break;
        }
    }

    //returns whether the row is correct(1) or wrong(0)
    rowsucc[rowval] = succ;

    return NULL;
}

//Function to check if a single column is correct
void *checkcols(void* args) {

    int succ = 1;
    int colval = *((int*)args);
    int col[10] = {0};

    for(int i = 0; i < 9; i++){

        if(board[i][colval] != 0){
            col[board[i][colval]] += 1;
        }

        if(col[board[i][colval]] >= 2){
            succ = 0;
            break;
        }
    }

    colsucc[colval] = succ;
    return NULL;
}

//Function to check if a single sub-grid correct
void *checkgrids(void* args){ 
    int succ = 1;
    int gridval = *((int*)args);

    //initializes array for the counter of digits 0 to 9
    int grid[10] = {0};

    // 0|1|2
    // -----
    // 3|4|5
    // -----
    // 6|7|8

    int g_row;
    int g_col;

    //What I am doing here is getting the number of what sub grid we are in (shown in the comment pic above) and
    //using case to set my staring position on the board, so it can check the 3 by 3 square

    switch(gridval) {
      case 0:
         g_row = 0;
         g_col = 0;
         break;
      case 1:
         g_row = 0;
         g_col = 3;
         break;
      case 2:
         g_row = 0;
         g_col = 6;
         break;
      case 3:
         g_row = 3;
         g_col = 0;
         break;
      case 4:
         g_row = 3;
         g_col = 3;
         break;
      case 5:
         g_row = 3;
         g_col = 6;
         break;
      case 6:
         g_row = 6;
         g_col = 0;
         break;
      case 7:
         g_row = 6;
         g_col = 3;
         break;
      case 8:
         g_row = 6;
         g_col = 6;
         break;
    }

    //Counts how many times a number appears in a sub grid
    for(int i = g_row; i < (g_row+3); i++){ 

            for(int j = g_col; j < (g_col+3); j++){ 

                //ignoring zeroes
                if(board[i][j] != 0){

                    //Add one to the counter for the digit
                    grid[board[i][j]] += 1;
                }
                 
                //if a digit appears twice then sub grid is unvalid, sets it to false and breaks
                if(grid[board[i][j]] >= 2){
                    succ = 0;
                    //Exits the double for loop and goes to the flag i have set
                    goto OUT_OF_LOOP;
                }
            }
    }

    //flag
    OUT_OF_LOOP:

    //returns whether the sub grid is correct(1) or wrong(0)
    gridsucc[gridval] = succ;
    return NULL;
}

int main() {

    //Time to read the file
    FILE *file;
    file = fopen("puzzle.txt", "r");

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            char c;

            if (fscanf(file, " %c", &c) != 1) { printf("Error\n"); }
            else if (isdigit((unsigned char)c)) {
                board[i][j] = c - '0';
            } else {
                board[i][j] = 0;
            }
        }
    }
    fclose(file);

    //Printing the board
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    printf("\nDone Reading File...\n\n");

    printf("Above is the Sudoku puzzle given inside puzzle.txt\n\n");

    //Creating the threads
    pthread_t tid_r[9];
    pthread_t tid_c[9];
    pthread_t tid_Sg[9];

    //A constant array, so each thread gets the numbers - to 8 sent to it
    int Digit[9]= {0, 1, 2, 3, 4, 5, 6, 7, 8};

    //rows
    for (int i = 0; i < 9; i++) {
        //sleep(1);
        pthread_create(&tid_r[i], NULL, checkrows, &Digit[i]);
    }

    for (int i = 0; i < 9; i++){
        pthread_join(tid_r[i], NULL);
    }

    //columns
    for (int i = 0; i < 9; i++) {
        //sleep(1);
        pthread_create(&tid_c[i], NULL, checkcols, &Digit[i]);
    }

    for (int i=0; i < 9; i++){
        pthread_join(tid_c[i], NULL);
    }

    //Sub-grid
    for (int i = 0; i < 9; i++) {
        //sleep(1);
        pthread_create(&tid_Sg[i], NULL, checkgrids, &Digit[i]);
    }

    for (int i=0; i < 9; i++){
        pthread_join(tid_Sg[i], NULL);
    }


    //Checking if rows are Valid, if not printing which rows are incorrect
    //Setting Row_result to True
    int Row_result = 1;
    for(int i=0; i<9; i++){
        //Taking the and of all the results in the array, if ther is one 0 then Row_result will becom and stay 0
        Row_result &= rowsucc[i];
    }

    if (Row_result == 1){
        printf("Rows are Valid\n\n");
    }

    else{
        for(int i = 0; i < 9; i++) {
            if(rowsucc[i] == 0){
                printf("Row %d is invalid\n", i+1);
            }
        }
        printf("\n");
    }

    //Checking if columns are Valid
    int Col_result = 1;
    for(int i=0; i<9; i++){
        Col_result &= colsucc[i];
    }

    if (Col_result == 1){
        printf("Columns are Valid\n\n");
    }

    else{
        for(int i = 0; i < 9; i++) {
            if(colsucc[i] == 0){
                printf("Column %d is invalid\n", i+1);
            }
        }
        printf("\n");
    }

    //Checking if Sub Grids are Valid
    int Sg_result = 1;
    for(int i=0; i<9; i++){
        Sg_result &= gridsucc[i];
    }

    if (Sg_result == 1){
        printf("Sub Grids are Valid\n\n");
    }

    else{
        for(int i = 0; i < 9; i++) {
            if(gridsucc[i] == 0){
                printf("Sub Grid %d is invalid\n", i+1);
            }
        }
        printf("\n");
    }
    
    if (Row_result == 1 && Col_result == 1 && Sg_result == 1){
        printf("Sudoku Puzzle is Valid\n");
    }

    else {
        printf("Sudoku Puzzle is Invalid\n");
    }

    return 0;
}