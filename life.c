
// Harvey Benjen
// Game of Life
// Due: 26th October 2018
// The system("clear") function throws a warning, but I needed to include it
// so that it would refresh the screen

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 62
#define COLUMNS 82
#define ALIVE 1
#define DEAD 0
#define ITERATIONS 1000

void delay(int seconds);
void loadBoard(int board[ROWS][COLUMNS]);
int countNeighbors(int board[ROWS][COLUMNS], int row, int column);
void checkConditions(int previous[ROWS][COLUMNS],int next[ROWS][COLUMNS]);
int compareGenerations(int previous[ROWS][COLUMNS], int next[ROWS][COLUMNS]);
void updateBoard(int previous[ROWS][COLUMNS], int next[ROWS][COLUMNS]);
void printBoard(int board[ROWS][COLUMNS]);

int main(void)
{
   int n;
   int previousBoard[ROWS][COLUMNS];
   int nextBoard[ROWS][COLUMNS];
   loadBoard(nextBoard);
   for(n=0; n < ITERATIONS; ++n)
   {
      updateBoard(previousBoard, nextBoard);
      checkConditions(previousBoard, nextBoard);
      printBoard(nextBoard);
      delay(100);
      system("clear");
      //compareGenerations(previousBoard, nextBoard);
      // compareGenerations function above can be used in a while loop in order
      // to exit the loop once the previous and next generations become the
      // same. However here I am only iterating 1000 times
   }
   return 0;
}

void delay(int seconds)
{
    int milliseconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

void loadBoard(int board[ROWS][COLUMNS])
{
   int i, j, current = 1, randomCell;
   srand(time(0));
   for (i=0; i < ROWS; ++i)
   {
      for(j=0; j < COLUMNS; ++j)
      {
         board[i][j] = DEAD;
      }
   }
   j = 1;
   for (i=1; i < ROWS-1; ++i)
   {
      while(j < COLUMNS-1)
      {
         randomCell = rand() % 5; //chooses a random cell within group of 5
         current += randomCell;
         board[i][current] = ALIVE;
         j += 5;     //jump to the next 5 cells in the row
         current = j;
      }
      j = 1;
   }
}

int countNeighbors(int board[ROWS][COLUMNS], int row, int column)
{
   int x, y, count = 0;
   for(x=row-1; x<=row+1; ++x)
   {
      for(y=column-1; y<=column+1;++y)
      {
         if(board[x][y] == ALIVE)
         {
            count += 1;
         }
      }
   }
   if(board[row][column] == ALIVE){
      count -= 1;
   }
   return count;
}

void checkConditions(int previous[ROWS][COLUMNS], int next[ROWS][COLUMNS])
{
   int i, j, neighbors;
   for (i=1; i<ROWS-1; ++i)
   {
      for(j=1; j<COLUMNS-1; ++j)
      {
         neighbors = countNeighbors(previous, i, j);
         if(previous[i][j] == ALIVE)
         {
            if(neighbors == 0 || neighbors == 1)
            {
               next[i][j] = DEAD;
            }
            else if(neighbors==4 || neighbors==5 || neighbors==6 ||
            neighbors==7 || neighbors==8)
            {
               next[i][j] = DEAD;
            }
            else if(neighbors==2 || neighbors==3)
            {
               next[i][j] = ALIVE;
            }
         }
         else if(previous[i][j] == DEAD)
         {
            if(neighbors == 3)
            {
               next[i][j] = ALIVE;
            }
            else if(neighbors==0 || neighbors==1 || neighbors==2 ||
            neighbors==4 || neighbors==5 || neighbors==6 || neighbors==7
            || neighbors==8)
            {
               next[i][j] = DEAD;
            }
         }
      }
   }
}

int compareGenerations(int previous[ROWS][COLUMNS], int next[ROWS][COLUMNS])
{
   int i, j, same = 1;
   for (i=1; i<ROWS-1; ++i)
   {
      for(j=1; j<COLUMNS-1; ++j)
      {
         if(next[i][j] != previous[i][j]){
            same = 0;
            break;
         }
      }
   }
   return same;
}

void updateBoard(int previous[ROWS][COLUMNS], int next[ROWS][COLUMNS])
{
   int i, j;
   for (i=1; i<ROWS-1; ++i)
   {
      for(j=1; j<COLUMNS-1; ++j)
      {
         previous[i][j] = next[i][j];
      }
   }
}

void printBoard(int board[ROWS][COLUMNS])
{
   int i, j;
   for (i=1; i<ROWS-1; ++i)
   {
      for(j=1; j<COLUMNS-1; ++j)
      {
         if(board[i][j] == ALIVE){
            printf("*");
         }
         else if(board[i][j] == DEAD){
            printf(" ");
         }
      }
      printf("\n");
   }
}
