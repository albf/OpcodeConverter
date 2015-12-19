#include <stdio.h>

#ifdef X86
#else
#include "stdthing.h"
#endif

int isAvailable(int puzzle[][9], int row, int col, int num)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i, j;

    for(i=0; i<9; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        if (puzzle[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
    }
    return 1;
}

int fillSudoku(int puzzle[][9], int row, int col)
{
    int i;
    if(row<9 && col<9)
    {
        if(puzzle[row][col] != 0)
        {
            if((col+1)<9) return fillSudoku(puzzle, row, col+1);
            else if((row+1)<9) return fillSudoku(puzzle, row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if(isAvailable(puzzle, row, col, i+1))
                {
                    puzzle[row][col] = i+1;
                    if((col+1)<9)
                    {
                        if(fillSudoku(puzzle, row, col +1)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else if((row+1)<9)
                    {
                        if(fillSudoku(puzzle, row+1, 0)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}

int main()
{
    int i, j, ret=0;
    int puzzle[9][9];
    /*int puzzle[9][9]={{0, 0, 0, 0, 0, 0, 0, 9, 0},
                      {1, 9, 0, 4, 7, 0, 6, 0, 8},
                      {0, 5, 2, 8, 1, 9, 4, 0, 7},
                      {2, 0, 0, 0, 4, 8, 0, 0, 0},
                      {0, 0, 9, 0, 0, 0, 5, 0, 0},
                      {0, 0, 0, 7, 5, 0, 0, 0, 9},
                      {9, 0, 7, 3, 6, 4, 1, 8, 0},
                      {5, 0, 6, 0, 8, 1, 0, 7, 4},
                      {0, 8, 0, 0, 0, 0, 0, 0, 0}}; */
    puzzle[0][0] = 0; puzzle[0][1] = 0; puzzle[0][2] = 0; puzzle[0][3] = 0; puzzle[0][4] = 0; puzzle[0][5] = 0; puzzle[0][6] = 0; puzzle[0][7] = 9; puzzle[0][8] = 0;
    puzzle[1][0] = 1; puzzle[1][1] = 9; puzzle[1][2] = 0; puzzle[1][3] = 4; puzzle[1][4] = 7; puzzle[1][5] = 0; puzzle[1][6] = 6; puzzle[1][7] = 0; puzzle[1][8] = 8;
    puzzle[2][0] = 0; puzzle[2][1] = 5; puzzle[2][2] = 2; puzzle[2][3] = 8; puzzle[2][4] = 1; puzzle[2][5] = 9; puzzle[2][6] = 4; puzzle[2][7] = 0; puzzle[2][8] = 7;
    puzzle[3][0] = 2; puzzle[3][1] = 0; puzzle[3][2] = 0; puzzle[3][3] = 0; puzzle[3][4] = 4; puzzle[3][5] = 8; puzzle[3][6] = 0; puzzle[3][7] = 0; puzzle[3][8] = 0;
    puzzle[4][0] = 0; puzzle[4][1] = 0; puzzle[4][2] = 9; puzzle[4][3] = 0; puzzle[4][4] = 0; puzzle[4][5] = 0; puzzle[4][6] = 5; puzzle[4][7] = 0; puzzle[4][8] = 0;
    puzzle[5][0] = 0; puzzle[5][1] = 0; puzzle[5][2] = 0; puzzle[5][3] = 7; puzzle[5][4] = 5; puzzle[5][5] = 0; puzzle[5][6] = 0; puzzle[5][7] = 0; puzzle[5][8] = 9;
    puzzle[6][0] = 9; puzzle[6][1] = 0; puzzle[6][2] = 7; puzzle[6][3] = 3; puzzle[6][4] = 6; puzzle[6][5] = 4; puzzle[6][6] = 1; puzzle[6][7] = 8; puzzle[6][8] = 0;
    puzzle[7][0] = 5; puzzle[7][1] = 0; puzzle[7][2] = 6; puzzle[7][3] = 0; puzzle[7][4] = 8; puzzle[7][5] = 1; puzzle[7][6] = 0; puzzle[7][7] = 7; puzzle[7][8] = 4;
    puzzle[8][0] = 0; puzzle[8][1] = 8; puzzle[8][2] = 0; puzzle[8][3] = 0; puzzle[8][4] = 0; puzzle[8][5] = 0; puzzle[8][6] = 0; puzzle[8][7] = 0; puzzle[8][8] = 0;

    if(fillSudoku(puzzle, 0, 0))
    {
        //printf("\n+-----+-----+-----+\n");
        for(i=1; i<10; ++i)
        {
            for(j=1; j<10; ++j) ret+= puzzle[i-1][j-1];//printf("|%d", puzzle[i-1][j-1]);
            //printf("|\n");
            //if (i%3 == 0) printf("+-----+-----+-----+\n");
        }
    }
    //else printf("\n\nNO SOLUTION\n\n");

    return 0;
}