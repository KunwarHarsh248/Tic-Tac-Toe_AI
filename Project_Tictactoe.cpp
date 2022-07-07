#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// EE20BTECH11024 - Kunwar Harshvardhan Singh

char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char currentmarker;


void displayboard()
{   
    cout<<endl;
    for(int i=0;i<3;i++)
    {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << endl;
        cout << "-----------" << endl;
    }
    cout << endl;
}

bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (!(board[i][j]=='X' || board[i][j]=='O'))
				return true;
	return false;
}

struct location
{
    int r;
    int c;
};

location where(int slot)
{
    location a;
    int row,col;
    row = slot/3;

    if(slot%3 == 0)
    {
        row = row-1;
        col = 2;
    }
    else col= (slot%3)-1;
    a.r = row;
    a.c = col;
return a;
}

bool isvalid(int slot)
{
    location v = where(slot);
    if (!(board[v.r][v.c]=='X' || board[v.r][v.c]=='O')) return true;
    else return false;
}

void marker(int slot)
{
    location xy = where(slot);
    board[xy.r][xy.c] = currentmarker;
}

int winner(char board[3][3], char comp, char player)
{
    for(int i=0;i<3;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
        {
            if(board[i][0]==comp)
            {
                return 10;
            }
            else if(board[i][0]==player)
            {
                return -10;
            }
        }

        else if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
        {
            if(board[0][i]==comp)
            {
                return 10;
            }
            else if(board[0][i]==player)
            {
                return -10;
            }
        }
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) 
    {
        if(board[0][0]==comp)
        {
            return 10;
        }
        else if(board[0][0]==player)
        {
            return -10;
        }
    }
    else if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if(board[2][0]==comp)
        {
            return 10;
        }
        else if(board[2][0]==player)
        {
            return -10;
        }
    }
    return 0;
}

int minimax(char board[3][3], int depth, bool isMax, char comp, char player)
{
	int score = winner(board, comp, player);

	if (score == 10)
		return score;
	if (score == -10)
		return score;
	if (isMovesLeft(board)==false)
		return 0;
	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (!(board[i][j]=='X' || board[i][j]=='O'))
				{
                    char a = board[i][j]; 
					board[i][j] = comp;
					best = max( best,minimax(board, depth+1, !isMax, comp, player) );
					board[i][j] = a;
				}
			}
		}
		return best;
	}

	else
	{
		int best = 1000;

		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (!(board[i][j]=='X' || board[i][j]=='O'))
				{
                    char b = board[i][j];
					board[i][j] = player;
					best = min(best,minimax(board, depth+1, !isMax, comp, player));
					board[i][j] = b;
				}
			}
		}
		return best;
	}
}

int findBestMove(char board[3][3], char comp, char player)
{
	int val = -1000;
    int m,n;
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (!(board[i][j]=='X' || board[i][j]=='O'))
			{
				char c = board[i][j];
				board[i][j] = comp;
				int betterval = minimax(board, 0, false, comp, player);
				board[i][j] = c;

				if (betterval > val)
				{
					m = i;
					n = j;
					val = betterval;
				}
			}
		}
	}
	return 3*m+n+1;
}

void game()
{
    int i=0;
    char player,comp;
    cout << "You are playing tic tac toe game. \nChoose 'X' or 'O' marker. \nPlayer one choose your marker : " << endl;
    cin >> player; 
    int playerwon;

    if(player =='X')
    {
        comp = 'O';
    }
    else if(player =='O')
    {
        comp = 'X';
    }
    else cout << "Please select valid marker. Choose 'X' or 'O'." << endl;

    cout << "Player one your marker is " << player << endl;
    cout << "computers marker is " << comp << endl;
    displayboard();

    for(i;i<9;i++)
    {
        int slot;
        if(i%2==0) 
        {
            currentmarker = player; 
            cout << "It's player's turn. Enter your slot :";
            cin >> slot;
            while (!(isvalid(slot)))
            {
            cout << "It's not valid move. Please enter valid slot.";
            cin >> slot;   
            }
        }
        else 
        {
            currentmarker = comp;
            slot = findBestMove(board, comp, player);
        }
    
        marker(slot);
        displayboard();

        playerwon = winner(board, comp, player);
        if(playerwon == -10) {cout << "Player one is the winner. Congratulations!" << endl; break;}
        else if(playerwon == 10) {cout << "Computer is the winner. Congratulations!" << endl; break;}
        
    }
    if (playerwon == 0) cout << "It's a tie." << endl;
}

int main()
{
    game();
    return 0;
}
