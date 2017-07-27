/* 
 * File:   main.cpp
 * Author: Christopher Ramirez-Alba
 * Created on July 26, 2017, 3:24 PM
 *Purpose: Project 2 Minesweep
 */
 
 //System Librariez
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

// use all of the things
using std::rand;
using std::srand;
using std::time;
using std::cout;
using std::cin;
using std::endl;
using std::right;
using std::left;
using std::setw;
using std::string;

// BOARD.h

class BOARD
{
public:
    BOARD(int rows, int column, float per);
    BOARD(int rows, int column);
    BOARD();
    virtual ~BOARD();

    static const int ROW_AMOUNT, COLUMN_AMOUNT;
    static const float CHANCE_DEFAULT;
    static const unsigned char MINE_MASK, UNCOVERED_MASK;
    static void random();

    void rndBord();
    bool Mine(int r, int c);
    bool Uncvrd(int r, int c);
    int USpace(int r, int c);
    int AdjMcnt(int r, int c);
    bool onBoard(int r, int c);
    char GetSqur(int r, int c);

    int GetRows();
    int Getcolumn();
    float Getprcnt();
    int GetMinCnt();
    int GetSfeCnt();

private:
    int rowcount, colcount;
    int minecount, safecount;

    float percentage;
    char * board;
    bool safedummy;

    void Init(int rows, int column, float per);
};

// MineSwp.h

class MineSwp : public BOARD
{
public:
    MineSwp();
    MineSwp(int rows, int column, float difficulty);
    MineSwp(int rows, int column, float difficulty, char mchar, char bchar, char uchar);

    static const char MINE_DEFAULT, BLANK_DEFAULT, UNKNOWN_DEFAULT;

    void PrintBoard();
    char GetCharForSpace(int r, int c);
    void Play();
    bool WonGame();
private:
    char minechar, blankchar, unknownchar;
    int cleared;

    void Init(char mchar, char bchar, char uchar);
};

// BOARD.cpp

const int BOARD::ROW_AMOUNT=10, BOARD::COLUMN_AMOUNT=10;
const float BOARD::CHANCE_DEFAULT=0.85;
const unsigned char BOARD::MINE_MASK=0x1, BOARD::UNCOVERED_MASK=0x2;

void BOARD::random()
{
    srand(time(NULL));
}

int BOARD::GetRows()
{
    return rowcount;
}

int BOARD::Getcolumn()
{
    return colcount;
}

float BOARD::Getprcnt()
{
    return percentage;
}

int BOARD::GetMinCnt()
{
    return minecount;
}

int BOARD::GetSfeCnt()
{
    return safecount;
}

BOARD::BOARD()
{
    Init(ROW_AMOUNT, COLUMN_AMOUNT, CHANCE_DEFAULT);
}

BOARD::BOARD(int rows, int column)
{
    Init(rows, column, CHANCE_DEFAULT);
}

BOARD::BOARD(int rows, int column, float per)
{
    Init(rows, column, per);
}

BOARD::~BOARD()
{
    delete[] board;
}

void BOARD::Init(int rows, int column, float per)
{
    minecount=0;
    safecount=rows * column;
    percentage=per;
    rowcount=rows;
    colcount=column;
    board=new char [rows * column];
    rndBord();
}

char BOARD::GetSqur(int r, int c)
{
    return board[r * colcount + c];
}

void BOARD::rndBord()
{
    for (int i=0, j=rowcount * colcount; i != j; ++i)
    {
        float r=(((float) rand()) / ((float) RAND_MAX));
        board[i]=(percentage < r);
        if (board[i]) ++minecount;
    }
    safecount -= minecount;
}

bool BOARD::onBoard(int r, int c)
{
    return (
               (r >= 0 && r < rowcount) &&
               (c >= 0 && c < colcount)
           );
}

bool BOARD::Mine(int r, int c)
{
    return (
               (onBoard(r, c)) &&
               (GetSqur(r, c) & MINE_MASK)
           );
}

bool BOARD::Uncvrd(int r, int c)
{
    return (
               (onBoard(r, c)) &&
               (GetSqur(r, c) & UNCOVERED_MASK)
           );
}

int BOARD::USpace(int r, int c)
{
    int uncovered=0;
    while (onBoard(r, c) && !Uncvrd(r, c))
    {
        board[r * colcount + c] |= UNCOVERED_MASK;
        if (!(GetSqur(r, c) & MINE_MASK)) ++uncovered;
        else break;

        if (AdjMcnt(r, c) == 0)
        {
            uncovered += USpace(r + 0, c + 1);
            uncovered += USpace(r + 0, c - 1);
            uncovered += USpace(r + 1, c + 0);
            uncovered += USpace(r - 1, c + 0);
        }

        break;
    }
    return uncovered;
}

int BOARD::AdjMcnt(int r, int c)
{
    return Mine(r + 0, c + 1) +Mine(r + 0, c - 1)+ 
           Mine(r + 1, c + 0) +Mine(r - 1, c + 0)+
           Mine(r + 1, c + 1) +Mine(r - 1, c - 1)+
           Mine(r + 1, c - 1) +Mine(r - 1, c + 1);
}

// MineSwp.cpp

const char MineSwp::MINE_DEFAULT='X', MineSwp::BLANK_DEFAULT=' ', MineSwp::UNKNOWN_DEFAULT='?';

MineSwp::MineSwp() : BOARD()
{
    Init(MINE_DEFAULT, BLANK_DEFAULT, UNKNOWN_DEFAULT);
}

MineSwp::MineSwp(int rows, int column, float difficulty) : BOARD(rows, column, difficulty)
{
    Init(MINE_DEFAULT, BLANK_DEFAULT, UNKNOWN_DEFAULT);
}

MineSwp::MineSwp(int rows, int column, float difficulty, char mchar, char bchar, char uchar) : BOARD(rows, column, difficulty)
{
    Init(mchar, bchar, uchar);
}

void MineSwp::Init(char mchar, char bchar, char uchar)
{
    minechar=mchar;
    blankchar=bchar;
    unknownchar=uchar;
}

void MineSwp::PrintBoard()
{
    for (int i=0; i < Getcolumn(); ++i) cout<<setw(4)<<right<<i;
    cout<<left<<endl<<endl;
    for (int r=0; r < Getcolumn(); ++r)
    {
        cout<<setw(3)<<r;
        for (int c=0; c < GetRows(); ++c)
        {
            cout<<setw(4)<<GetCharForSpace(r, c);
        }
        cout<<endl;
    }
}

char MineSwp::GetCharForSpace(int r, int c)
{
    if (Uncvrd(r, c))
    {
        if (Mine(r, c))
            return minechar;
        int count=AdjMcnt(r, c);
        if (count == 0)
            return blankchar;
        else
            return '0' + count;
    }
    else
        return unknownchar;
}

void MineSwp::Play()
{
    int score=0;
    PrintBoard();
    cout<<"Total Bombs In This Game: "<<GetMinCnt()<<endl;

    while (true)
    {
        string dummy;
        int inputrow=-1, inputcol=-1;
        cout<<"Input Your ROW & COLUMN Guess Coordinate (i.e. 3 2): ";
        cin>>inputrow>>inputcol;
        if (!cin || Uncvrd(inputrow, inputcol) || !onBoard(inputrow, inputcol))
        {
            cout<<"Invalid Selection! ";
            if (!cin)
            {
                cin.clear();
                cin>>dummy;
            }
            continue;
        }

        int uncovered=USpace(inputrow, inputcol);
        PrintBoard();
        if (Mine(inputrow, inputcol))
        {
            cout<<endl<<endl<<"             -Game Over-"<<endl<<endl;
            break;
        }
        else
        {
            score += uncovered;
            cleared += uncovered;
            if (WonGame())
            {
                cout<<endl<<endl<<"             You Win!"<<endl<<endl;
                break;
            }

        }
    }
}

bool MineSwp::WonGame()
{
    return (cleared == GetSfeCnt());
}

// main.cpp

int main(int argc, char * argv[])
{
    BOARD::random();

    cout<<endl<<endl;

    while(true)
    {
        MineSwp m;
        m.Play();
        cout<<endl;
        break;
    }
    return 0;
}