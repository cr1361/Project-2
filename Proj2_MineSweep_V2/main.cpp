        /* 
 * File:   main.cpp
 * Author: Christopher Ramirez-Alba
 * Created on July 25, 2017, 1:12 PM
 *Purpose: Project 2 Minesweep
 */
 
 //System Librariez
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//Function Prototypes 

void reDraw (bool guessed [] [10], int rows, int columns);
void newBoard (int rows, int columns);


int main(int argc, const char * argv[])
{
 //Declare Variables
  const int ROWS = 10;
  const int COLUMNS = 10;
int board [ROWS][COLUMNS];
bool Guessd [10] [10]; 
int rowgues, colgues; 
bool bomb = false;
srand((unsigned) time(0));


// Welcome User, Give Direction

{

 //function to randomly populate array elements
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            board [row] [column] = rand() % 100; 
            if (board [row] [column] >= 85) {
        }
    }
}

// Create a new Display Board
newBoard(10, 10);

// Process Guesses
do {
    cout<<endl<<"Please Input your ROW & COLUMN Guess coordinate (i.e. 3 2): ";
    cin>>rowgues>>colgues;

    if (board [rowgues] [colgues] >= 85) {
        bomb = true;
        {
            break;
            }
    } else {
        Guessd [rowgues] [colgues] = true;
        reDraw(Guessd, 10, 10);
    }
} while (!bomb);

}


return 0;
}

   void reDraw (bool guessed [] [10], int rows, int columns)
{
    // Format row and column headers
    cout<<"  0   1   2   3   4   5   6   7   8  9"<<endl;
    cout<<"0";
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {

        if ((j+1) % 10 == 0) 
            if ((i+1) == 10) {
                if (guessed [i] [j]) 
                    cout<<"X "<<endl;
                else 
                    cout<<"? "<<endl;
            }else{
                if (guessed [i] [j]) 
                    cout<<"X "<<endl<<i+1;
                else                
                    cout<<"? "<<endl<<i+1;
            }
        if ((j+1) % 10 != 0)
            if (guessed [j] [i]) 
                cout<<" X"<<"  ";
            else
                cout<<" ?"<<"  "; 

    }
}

}
void newBoard (int rows, int columns)
{

cout<<"  0   1   2   3   4   5   6   7   8  9"<<endl;
cout<<"0";
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {

        if ((j+1) % 10 == 0) 
            if ((i+1) == 10) {
                cout<<"? "<<endl;
            }else
                cout<<"? "<<endl<<i+1;
        if ((j+1) % 10 != 0)
            cout<<" ?"<<"  ";
    }

}


}