//Jimmy Puli
#include <iostream>
using namespace std;
//check function does the row test and up and down diagonal test 
bool check(int q[], int c){
  for(int i = 0; i < c; i++){
      if(q[i] == q[c] || (c - i) == abs(q[c] - q[i]))
        return false;
  }
  return true;
}
//print function
//only q array is passed in 
//int i,j,k,l are initialized to prevent repetition in the for loops
//i and j are the rows and columns of the board (8 x 8) respectively 
//k and l are the inner rows and columns of the boxes in the board (5 x 7) respectively 
//static int count is used to keep track of the solutions 
//static prevents count from being initialized everytime print is called
//typedef creates an alias(another name for) the type defined here(char)
//so box becomes another name for the type char[5][7]
//box then creates arrays of 5 by 7 for bb(black box),wb(white box),bq(black queen),wq(white queen)
//then for *board[8][8] an array (5x7) is created within an array of 8 by 8
void print(int q[]){
  int i,j,k,l;
  static int count = 0;
  typedef char box[5][7];
  box bb,wb,bq,wq,*board[8][8];
//for loop goes through the wb,bb,wq,bq arrays and sets them equal to blank spaces or X's
//this is for the board whose entries will point to theses arrays 
  for(i = 0; i < 5; i++)
    for(j = 0; j < 7; j++){
      wb[i][j] = ' ';
      bb[i][j] = 'X';
      wq[i][j] = ' ';
      bq[i][j] = 'X';
    }
  //for the white queens and black queens specific entries in the array need to be modified so they show a queen's crown
  //the X's and spaces are arranged so that when they are printed they would look like crowns in a black or white background
  wq[1][1] = 'X';
  wq[2][1] = 'X';
  wq[3][1] = 'X';
  wq[3][2] = 'X';
  wq[3][3] = 'X';
  wq[2][3] = 'X';
  wq[1][3] = 'X';
  wq[3][4] = 'X';
  wq[3][5] = 'X';
  wq[2][5] = 'X';
  wq[1][5] = 'X';

  bq[1][1] = ' ';
  bq[2][1] = ' ';
  bq[3][1] = ' ';
  bq[3][2] = ' ';
  bq[3][3] = ' ';
  bq[2][3] = ' ';
  bq[1][3] = ' ';
  bq[3][4] = ' ';
  bq[3][5] = ' ';
  bq[2][5] = ' ';
  bq[1][5] = ' ';
//this for loop traverses the rows and columns of the board and assigns a square with X's or spaces 
//this depends on if the sum of the rows is even or odd
//if even, the address to the white board is assigend 
//if odd, the address to the black board(X's) is assigned 
//the for loop also places the queens if the conditions are met
//if the row(q[j]) equals the column(i) and the sum of the row and column is even then we print the address of the white queen
//else if the row equals the column and the sum of the row(i) and column(j) is odd then we print the address of the black queen
//this is done so the right queens is placed in the right box  
//the boxes of the board are given addresses
//when they are dereferenced later on in the code they can be used to access other arrays(wb,bb,wq,bq) that will provide the correct character that needs to be printed
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      if((i+j)%2 == 0)
        board[i][j] = &wb;
      else
        board[i][j] = &bb;
      if(q[j] == i && (i+j)%2 == 0)
        board[i][j] = &wq;
      else if(q[j] == i && (i+j)%2 != 0)
        board[i][j] = &bq;
    }
  }
//solution number is printed 
cout << "Solution: " << ++count << endl;
cout << "    "; //space is printed 
for(i = 0; i < 7*8; i++)//upper border is printed 7 columns in one box, there are 8 boxes(7 * 8) = 56
  cout << '_';
cout << endl;

for(i = 0; i < 8; i++)//begin with i the row of the board
  for(k = 0; k < 5; k++){ //k is the line in the box we are at, it's a row within a row 
    cout << "   " << "|"; //make some space but before we print anything we print the left border 
    for(j = 0; j < 8; j++)// j is the column of the board
      for( l = 0; l < 7; l++)// l moves down the board and is repeated the most as j increments 
        cout << (*board[i][j])[k][l];//the board is dereferenced and becomes an alias for wb,bb,wq,or bq according to i and j 
  cout << "|" << endl;//right side border is printed  
  }
  cout << "    ";//space printed 
  for(i = 0; i < 7*8; i++)
    cout << "-";//lower border is printed 
  cout << endl;
//this clears the board for the next solution 
//makes all the boxes in the board point to addresses of either white box or black box
//there are no more queens, they are removed after the printing is done
for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++)
      if((i+j)%2 == 0)
        board[i][j] = &wb;
      else
        board[i][j] = &bb;

}

int main() {
  int q[8] = {0}, col = 1; //sets array to all 0 

  while(col != -1){ //while all solutions are not found 
    if(q[col] == 8){
      q[col] = 0; // resets the queen
      col--; // goes back a column
      if(col == -1) return 0;
      q[col]++; // increments row in the new column
    }

    else if(col == 8){
      print(q);
      col--;
      q[col]++;
    }
    else if(check(q,col)){
       col++;
    }else{
      q[col]++;
    }
  }
  return 0;
}

