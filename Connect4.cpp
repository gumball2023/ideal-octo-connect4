#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll board[6][7];
ll weigh[6][7]={
	{3,4,5,7,5,4,3},
	{4,6,8,10,8,6,4},
	{5,7,11,13,11,7,5},
	{5,7,11,13,11,7,5},
	{4,6,8,10,8,6,4},
	{3,4,5,7,5,4,3}
};
struct Move{
    ll column, score;
};
ll Score()
{
    ll i,j,s=0;
    for(i=0;i<=5;i++)
    {
        for(j=0;j<=6;j++)
        {
        	if(board[i][j])
        	{
	            if(j<4&&board[i][j]==board[i][j+1]&&board[i][j]==board[i][j+2]&&board[i][j]==board[i][j+3])
	                return board[i][j]*1000;
	            if(i<3&&board[i][j]==board[i+1][j]&&board[i][j]==board[i+2][j]&&board[i][j]==board[i+3][j])
	                return board[i][j]*1000;
	            if(i<3&&j<4&&board[i][j]==board[i+1][j+1]&&board[i][j]==board[i+2][j+2]&&board[i][j]==board[i+3][j+3])
	                return board[i][j]*1000;
	            if(i<3&&j>2&&board[i][j]==board[i+1][j-1]&&board[i][j]==board[i+2][j-2]&&board[i][j]==board[i+3][j-3])
					return board[i][j]*1000;
				s+=board[i][j]*weigh[i][j];
			}
        }
    }
    return s;
}
void Place(ll co,ll piece)
{
    ll i;
    for(i=0;i<6;i++)
    {
        if(board[i][co]==0)
        {
		    board[i][co]=piece;
			return;
		}
    }
}
void Deplace(ll co)
{
    ll i;
    for(i=5;i>=0;i--)
    {
        if(board[i][co])
        {
		    board[i][co]=0;
			return;
		}
    }
}
Move BestMove(ll depth,ll piece)
{
	srand(time(NULL));
    /*Move a;
    a.column=rand()%7;
    a.score=0;
    return a;*/
    ll i;
    Move drop,cur;
    if(depth==9)
    {
		drop.column=0;
		drop.score=Score();
		return drop;
	}
	if(abs(Score())>100)
	{
		drop.column=0;
		drop.score=Score();
		return drop;
	}
	drop.score=-1e9*piece;
	for(i=0;i<7;i++)
	{
		if(board[5][i])
			continue;
		Place(i,piece);
		cur=BestMove(depth+1,piece*-1);
		cur.column=i;
		if(abs(cur.score)>100)
			cur.score-=abs(cur.score)/cur.score;
		Deplace(i);
		if((drop.score<cur.score)&&(piece>0))
			drop=cur;
		else if((drop.score>cur.score)&&(piece<0))
			drop=cur;
		else if(drop.score==cur.score&&(rand()%4==1))
			drop=cur;
	}
	//if(depth==1)cout<<drop.score<<endl;
	return drop;
}
int main()
{
    ll c,i,j;
    cout<<"Enter a number (1-7), and a token (O) will be dropped to the bottom of the corresponding column."<<endl;
    cout<<"Then Wolfy will drop a token (X) after a few seconds. The turn proceeds one by one like so."<<endl;
    cout<<"Once a player connects 4 of their tokens in a row, column or diagnal line, they wins."<<endl;
    for(i=5;i>=0;i--)
    {
        for(j=0;j<7;j++)
            cout<<'.';
        cout<<endl;
    }
    while(1)
    {
        /*system("cls");
        for(i=5;i>=0;i--)
        {
            for(j=0;j<7;j++)
            {
                if(board[i][j]==1)cout<<'O';
                if(board[i][j]==-1)cout<<'X';
                if(board[i][j]==0)cout<<'.';
            }
            cout<<endl;
        }*/
        while(1)
        {
	        cin>>c;
	        if(c<1||c>7)
	        	cout<<"A number between 1 and 7 please!"<<endl;
	        else if(board[5][c-1])
	        	cout<<"The column is filled up!"<<endl;
	        else break;
		}
		c--;
        Place(c,1);
		system("cls");
        for(i=5;i>=0;i--)
        {
            for(j=0;j<7;j++)
            {
                if(board[i][j]==1)cout<<'O';
                if(board[i][j]==-1)cout<<'X';
                if(board[i][j]==0)cout<<'.';
            }
            cout<<endl;
        }
        if(Score()==1000)
        {
		    
			cout<<"CLEAR";
            return 0;
        }
        c=BestMove(1,-1).column;
        Place(c,-1);
    	system("cls");
        for(i=5;i>=0;i--)
        {
            for(j=0;j<7;j++)
            {
                if(board[i][j]==1)cout<<'O';
                if(board[i][j]==-1)cout<<'X';
                if(board[i][j]==0)cout<<'.';
            }
            cout<<endl;
        }
        if(Score()==-1000)
        {
			cout<<"LOSE";
            return 0;
        }
    }
}
