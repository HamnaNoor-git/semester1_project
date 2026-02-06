 #include<iostream>
#include<ctime>
#include<string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <windows.h> 
using namespace std;


//GLOBAL VARIABLE FOR COLOURS
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;


string names[10];
			    int scores[10];
			    int count;

char board1[10][10],
	 board2[10][10],
	 board[10][10],
	 orientation,
	 placement1,placement2;
	 
int row,coloumn;
	 
string name1,
	   name2;
	   
int shipColour1,shipColour2,
	colour1,colour2,
	shipSize;
	
bool overlap=false;	

//================================================================================
//                                 PROTOTYPE
//================================================================================
void setColor(int textColor, int bgColor);
void game();
int shipCount(char board[10][10]);
void setPlayerShips(char board[10][10]); 
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10], bool hideShips);
void clearScreen();
void setRandomShips(char board[10][10]);
void opponentBoard(char board1[10][10], char board2[10][10]);
void playerAttack(char opponentBoard[10][10], int &playerScore);
void showGameMenu();
void displayResult(int player1Score, int player2Score);
void clearBoard(char[10][10]);
void setCostumeShips(char board[10][10]);
void vsplayer(char board1[10][10], char board2[10][10]); 
void applyOrientation();
void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers);
int readBoard(string names[], int scores[]);
void saveLeaderboard(const string names[], const int scores[], int count);
void updateBoard(string playerName, int playerScore);
//================================================================================
//                                 FUNCTIONS
//================================================================================


//READ FROM FILE
int readBoard(string names[], int scores[])
{
    ifstream file("highscores.txt");
    int count = 0;
    
    if(file.is_open())
	{
        while(count<10 && file>> names[count]>> scores[count])
		{
            count++;
        }
        file.close();
    }
    return count;
}

//SAVE TO FILE
void saveLeaderboard(const string names[], const int scores[], int count)
{
    ofstream file("highscores.txt");
    
    if(file.is_open()) 
	{
        for(int i = 0; i < count; i++)
		{
            file<< names[i]<< " "<< scores[i]<< endl;
        }
        file.close();
    }
}

//DISPLAY LEADER BOARD
void showLeaderboard(const string playerNames[], const int scores[], int totalPlayers)
{
    clearScreen();
    setColor(3 , 0);
    cout << "\n=========================================" << endl;
    cout << "            TOP 10 PLAYERS" << endl;
    cout << "=========================================" << endl;
    setColor(7, 0);
    
    if(totalPlayers == 0)
	{
        cout << endl<<"No scores recorded yet. Be the first!" << endl;
    }
	else 
	{
        cout << endl<<"  RANK    PLAYER NAME         SCORE" << endl;
        cout << "-----------------------------------------" << endl;
        
        for(int i = 0; i < totalPlayers; i++) 
		{
            // Highlight top 3
            if(i == 0) 
            // Gold
			{setColor(14, 0);}
			// Silver 
            else if(i == 1) 
			{setColor(7, 0);}
			// Bronze 
            else if(i == 2) 
			{setColor(6, 0);}
			// White
            else 
			{setColor(15, 0);}
            
            cout << "  " << (i+1) << ".       " 
                 << playerNames[i] << "               " 
                 << scores[i] << endl;
        }
        setColor(7, 0);
    }
    
    cout << "\n-----------------------------------------" << endl;
    cout << "(Press any key to return to menu...)" << endl;
    getch();
}

//UPDATE NEW SCORE
void updateBoard(string playerName, int playerScore) 
{
    string names[10];
    int scores[10];
    int count = readBoard(names, scores);
    
    bool win;
	if((count < 10) || (playerScore > scores[count-1]))
	{
		win=true;
	}
	
    
    if(win)
	{
        //NEW PLAYERS
        if(count < 10) 
		{
            names[count] = playerName;
            scores[count] = playerScore;
            count++;
        } else {
            names[9] = playerName;
            scores[9] = playerScore;
        }
        
        // SORTING
        for(int i = 0; i < count - 1; i++) 
		{
            for(int j = 0; j < count - i - 1; j++) 
			{
                if(scores[j] < scores[j+1]) {
                    
                    int tempScore = scores[j];
                    scores[j] = scores[j+1];
                    scores[j+1] = tempScore;
                    
                   
                    string tempName = names[j];
                    names[j] = names[j+1];
                    names[j+1] = tempName;
                }
            }
        }
        //SAVES TO FILE
        saveLeaderboard(names, scores, count);
        
        setColor(5, 0);
        cout << endl<<"YOU MADE A NEW HIGH SCORE"<<endl;
        setColor(7, 0);
    }
}

//MENU 
void showGameMenu()
{
	int choice,mode;
	while(true)
	{	
		clearScreen();
	setColor(3, 0);
	cout << endl
		 << "========================================="
		 <<endl 
		 << "     WELCOME TO BATTLE SHIP GAME"
		 <<endl
		 << "=========================================";
	setColor(6, 0);
	cout << endl << endl
		 << "               MAIN MENU"
		 <<endl;
	setColor(1, 0);	 
	cout << "-----------------------------------------";
	setColor(15, 0);
	cout <<endl
		 << "1. Start a New Game"
		 <<endl
		 << "2. Instructions"
		 <<endl
		 << "3. View Leadership board"
		 << endl
		 << "4. Exit"
		 <<endl;
	setColor(1, 0);	
	cout << "-----------------------------------------"
		 <<endl;
	setColor(6, 0);		 
	cout << "Enter your choice (1-4): ";
	setColor(15, 0);
		 
	cin >> choice;
	void clearScreen();
	switch (choice)	
	{
		case 1:
			{
			cout<<endl<<"1. PLAYER VS PLAYER"
				<<endl
				<<"2. PLAYER VS COMPUTER"
				<<endl<<endl;
			setColor(6, 0);
			cout <<"Select Game Mode: ";	
			setColor(15, 0);	
			cin>>mode;
				
			switch(mode)
			{
				case 1:
				{
					cout << "Press any key to continue...."<<endl;
					getch();
					clearScreen();
					vsplayer(board1, board2);
					break;
				}
				case 2:
				{
					cout<<"computer mode";
					break;
				}	
				default:
				{
					setColor(15, 4);
					cout <<"INVALID INPUT!!!"<<endl;
					setColor(15, 0);
					getch();
					break;
				}	
			}	
				break;
			}
			
		case 2:
			{
				cout << "Press any key to continue...."<<endl;
				getch();
				clearScreen();
				setColor(1, 0);
				cout << "---------------------------------------------------"
					 << endl;
				setColor(6, 0);	 
				cout << "              INSTRUCTIONS"
					 << endl;
				setColor(1, 0);	 
				cout << "---------------------------------------------------";
				setColor(15, 0);		 
				cout << endl
					 << "1. Place your ships on the board."
					 << endl
					 << "2. You and the other player take turns firing shots"
					 << endl
					 << "3. 'O' means MISS, 'X' means HIT"
					 << endl
					 << "4. Sink all enenmy ships to win!"
					 << endl
					 << "5. Your score is based on the accuracy and speed."
					 << endl;
				setColor(1, 0);	 	 
				cout << "-----------------------------------------"
					 << endl<<endl;
				setColor(15, 0);	 
				cout << "(Presss any key to return to menu...)";
					 getch();
					
				break;	 
			}	
		case 3:
			{
				count= readBoard(names, scores);
    			showLeaderboard(names, scores, count);
				break;
			}	
		case 4:
			{
				setColor(4, 0);
				cout <<endl<< "Game exit!!";
				setColor(15, 0);
				return ;
			}
		default:
			{
				setColor(15, 4);
				cout <<"INVALID INPUT!!!"<<endl;
				getch();
				setColor(15, 0);
				break;
			}	
		}
	
	}
}

//FoOR CLEARING SCREEN
void clearScreen()
{
	system("CLS"); 
}

//CLEAR BOARD
void clearBoard(char board[10][10])
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			board[i][j]='~';
		}
	}
}

//USED FOR HIDING SHIPS
void printBoard(char board[10][10], bool hideShips)
{
    cout << "      0      1     2     3     4     5     6     7     8     9  " << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << "  " << i << " �"; 
        
        for(int j = 0; j < 10; j++)
        {
        	board[i][j];
            //THIS WILL HELP TO HIDE THE SHIPS
            if(hideShips && (board[i][j]=='S' || board[i][j]=='A' || board[i][j]=='B' || board[i][j]=='D' || board[i][j]=='P'))
            {
                setColor(7, 1); 
                cout << "  ~  "; 
                setColor(7, 0);
            }
            
            //WILL SHOW THE BOATS
            else if(board[i][j] == 'S' || board[i][j] == 'A' || board[i][j] == 'B' || board[i][j] == 'D' || board[i][j] == 'P') 
            {
                setColor(7, shipColour1); 
                cout << "  " << board[i][j] << "  "; 
                setColor(7, 0);
            }
            //ATTACK HIT
            else if(board[i][j] == 'X') 
            {
                setColor(15, 12); 
                cout << "  X  "; 
                setColor(7, 0);
            }
            //ATTACK MISS
            else if(board[i][j] == 'O') 
            {
                setColor(0, 8); 
                cout << "  O  "; 
                setColor(7, 0);
            }
            else
            {
                setColor(7, 1); 
                cout << "  ~  "; 
                setColor(7, 0);
            }
            cout << "�";
        }
        cout << endl;
        cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

//INITIAL BOARD
void initializeBoard(char board[10][10])
{
    cout << "      0      1     2     3     4     5     6     7     8     9  " << endl;
    cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;

    //BOARD PRINTING
    for(int i = 0; i < 10; i++)
    {
        cout << "  " << i << " �";     
        for(int j = 0; j < 10; j++)
        {
        	//SHIP-S
            if(board[i][j] == 'S') 
            {
                setColor(7, shipColour1); 
                cout << "  S  "; 
                setColor(7, 0);
            }
            //SHIP-A
            else if(board[i][j] == 'A') 
            {
                setColor(7, shipColour1); 
                cout << "  A  "; 
                setColor(7, 0);
            }
            //SHIP-B
            else if(board[i][j] == 'B') 
            {
                setColor(7, shipColour1); 
                cout << "  B  "; 
                setColor(7, 0);
            }
            //SHIP-D
            else if(board[i][j] == 'D') 
            {
                setColor(7, shipColour1); 
                cout << "  D  "; 
                setColor(7, 0);
            }
            //SHIP-P
            else if(board[i][j] == 'P') 
            {
                setColor(7, shipColour1); 
                cout << "  P  "; 
                setColor(7, 0);
            }
            //ATTACK HIT
            else if(board[i][j] == 'X')
            {
                setColor(15, 12); 
                cout << "  X  "; 
                setColor(7, 0);
            }
            //ATTCK MISS
            else if(board[i][j] == 'O')
            {
                setColor(0, 8); 
                cout << "  O  "; 
                setColor(7, 0);
            }
            else 
            {
                setColor(7, 1); 
                cout << "  ~  "; 
                setColor(7, 0);
            }
            cout << "�";
        }
        cout << endl;
        cout << "    +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

//PRINTING OF THE HUGE BOARD
void opponentBoard(char board1[10][10], char board2[10][10])
{
    cout << "     ENEMY BOARD                                            OPPONENT                                       PLAYER BOARD"
         << endl << endl
         << "  0 1 2 3 4 5 6 7 8 9             0     1     2     3     4     5     6     7     8     9              0 1 2 3 4 5 6 7 8 9"
         << endl
         << "                               +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+ " << endl;
    
    for(int i = 0; i < 10; i++)
    {
    	//LEFT
        cout << i << " ";
        for(int j = 0; j < 10; j++)
        {
            if(board1[i][j] == 'X') 
                cout << "X ";
            else if(board1[i][j] == 'O')  
                cout << "O ";
            else  
                cout << ". ";
        }
        
        //MIDDLE
        cout << "       " << i << "  ";
        for(int j = 0; j < 10; j++)
        {
            if(board2[i][j] == 'X') 
            {
                setColor(15, 12);  
                cout << "  X  ";
                setColor(7, 0);
            }
            else if(board2[i][j] == 'O')  
            {
                setColor(0, 8); 
                cout << "  O  ";
                setColor(7, 0);
            }
            else if(board2[i][j] == 'S' || board2[i][j] == 'A' || 
                    board2[i][j] == 'B' || board2[i][j] == 'D' || 
                    board2[i][j] == 'P')  
            {
                setColor(7, 1);  
                cout << "  ~  ";
                setColor(7, 0);
            }
            else 
            {
                setColor(7, 1);
                cout << "  ~  ";
                setColor(7, 0);
            }
            cout << "�";
        }
        
        //RIGHT
        cout << "         " << i << " ";
        for(int j = 0; j < 10; j++)
        {
            if(board2[i][j] == 'X')  
                cout << "X ";
            else if(board2[i][j] == 'O') 
                cout << "O ";
           
            else 
                cout << ". ";
        }
        cout << endl;
        
        cout << "                               +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

// SET COLOUR
void setColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);
}

//COSTOM COLOUR FOR SHIPS
void setCostumeShips(int colour)
{
	switch(colour)
	{
		case 1:
			{
				shipColour1=5;
				break;
			}
		case 2:
			{
				shipColour1=3;
				break;
			}	
		case 3:
			{
				shipColour1=6;
				break;
			}	
		case 4:
			{
				shipColour1=2;
				break;
			}
	}
}
void vsplayer(char board1[10][10], char board2[10][10])
{
		int player1Score=0,
		player2Score=0;	   
	
	setColor(1, 0);		   
	cout <<  endl
		 <<"-----------------------------------------------------------------------------"
		 << endl;
	setColor(6, 0);		 
	cout << "                              START NEW GAME"
		 << endl;
	setColor(1, 0);		 
	cout << "------------------------------------------------------------------------------"
		 << endl <<endl;
	setColor(6, 0);		 
	cout << "ENTER YOUR NAME (PLAYER 1:) ";
	setColor(15, 0);	
	cin >> name1;
	setColor(6, 0);	
	cout <<endl<< "ENTER YOUR NAME (PLAYER 2:) ";
	setColor(15, 0);
	cin >> name2;
	
	//PLAYER 1
	setColor(1, 0);	 	 
	cout << "-----------------------------------------"
		 << endl;	 
	setColor(6, 0);	
	cout <<endl<< "Battle ship colours!"
		 <<endl;
	setColor(1, 0);	 	 
	cout << "-----------------------------------------"
		 << endl;
	setColor(15, 0);	 
	cout << "1.Purple \n2.Cyan \n3.Yellow \n4.Green"
		 << endl<<endl;
	setColor(6, 0);		 
	cout << "Choose your battle ship colour (Player#1): ";
	setColor(15, 0);	
  	cin  >> colour1;
  	
		if(colour1<1 || colour1>4)
		{
		setColor(15, 4);
		cout << "invalid choice of colours!!";
		setColor(15, 0);
	    }
		while(colour1<1||colour1>4)
		{
			cout << "Choose your battle ship colour ... Again(Player#1): ";
			cin  >> colour1;
		}
		initializeBoard(board1);
			
		cout<<endl
			<<"what type of placement you want?(R=random M=manually)";
		cin>>placement1;
		if(placement1!='r' && placement1!='R' && placement1!='m' && placement1!='M' )
		{
			{
			setColor(15, 4);
			cout << "invalid input"
				 <<endl;
			setColor(15, 0);
		   }
			 while(placement1!='r' && placement1!='R' && placement1!='m' && placement1!='M' )
			 {
			 	cout<< "Enter your choice again: ";
			 	cin >> placement1;
			 }	 
		}
		
		if(placement1=='m' || placement1=='M')
		{
			setCostumeShips(colour1);
			setPlayerShips( board1);
			getch();////
		}	
		else if (placement1=='r' || placement1=='R')
		{
				setCostumeShips(colour1);
				setRandomShips(board1);
				cout <<name1<<"'s ship ramdomly placed :)"<<endl;
		}

			//PLAYER 2
			cout << "press any key..."<<endl;
			getch();
			clearScreen();
			setColor(1, 0);	
			cout << "-----------------------------------------"
				 << endl;
			setColor(6, 0);	
			cout <<endl<< "Battle ship colours!"
				 <<endl;
			setColor(1, 0);	
			cout << "-----------------------------------------"
				 << endl;
			setColor(15, 0);	
			 cout<< "1.Purple \n2.Cyan \n3.Yellow \n4.Green"
			 << endl;
		setColor(6, 0);		 
		cout <<endl<< "Choose your battle ship colour (Player#2): ";
		setColor(15, 0);	
		cin  >> colour2;
	
		if(colour2<1 || colour2>4)
			{
			setColor(15, 4);		
			cout << "invalid choice of colours!!"<<endl;
			setColor(15, 0);	
			}
			while(colour2<1||colour2>4)
			{
				setColor(6, 0);	
				cout << "Choose your battle ship colour ... Again(Player#2): ";
				setColor(15, 0);	
				cin  >> colour2;
			}
			
			initializeBoard(board2);
			
			cout<<endl
				<<"what type of placement you want?(R=random M=manually)";
			cin>>placement2;
			if(placement2!='r' && placement2!='R' && placement2!='m' && placement2!='M' )
			{
				cout << "invalid input"
					 <<endl;
					 while(placement2!='r' && placement2!='R' && placement2!='m' && placement2!='M' )
					 {
					 	cout<< "Enter your choice again: ";
					 	cin >> placement2;
					 }	
					setCostumeShips(colour2);
					setPlayerShips( board2); 
			}	
				
			if(placement2=='m' || placement2=='M')
			{
				//MANUALL PLACEMENT
				setCostumeShips(colour2);
				setPlayerShips(board2);
				getch();
			}	
			else if (placement2=='r' || placement2=='R')
			{
				//RANDOM PLACEMENT
				setCostumeShips(colour2);
				setRandomShips(board2);
				cout <<name2<<"'s ship ramdomly placed :)"<<endl;
				getch();
			}	
			
			clearScreen();
			setColor(1, 0);	
			cout << "----------------------------------------------------------------------------"
				 << endl;
			setColor(6, 0);	
			cout <<endl<< "                       GAME STARTS!"
				 <<endl;
			setColor(1, 0);	
			cout << "----------------------------------------------------------------------------"
				 << endl;
			setColor(15, 0);
			cout<< "Each player will get turns equal to number of ships+1 per shot"
				<<endl<<endl;
			cout <<"Initially there are 6 turns and 5 ships"
				<<endl<<endl;
			cout <<"On hitting the ship score increases by 10 while missing it decreases by 1"
				<<endl<<endl;
			setColor(1, 0);		
			cout << "----------------------------------------------------------------------------"
				 << endl;
			setColor(15, 0);		
				
			cout<< "Press any key to continue....."<<endl;
			getch();
			clearScreen();
			
			bool turn=true;
			
			//GAME
			while(shipCount(board1) > 0 && shipCount(board2) > 0)
			{
				//PLAYER 1 
				if(turn) 
				{
					
					clearScreen();
					cout<<name1<<" turn"<<endl<<endl;
					
					int player1Shots = shipCount(board1)+1; //CALCULATING SHOTS
					
					setColor(3,0);
					cout<<name2<<" Board"<<endl;
					setColor(7,0);
					printBoard(board2, true);
					
					cout << "Your are having "<<player1Shots<< " shots"<<endl;
					for(int i=0; i<player1Shots; i++)
					{
						setColor(3,0);
						cout<<"Shot: "<<i+1<<endl;
						setColor(7,0);
						playerAttack(board2, player1Score);
						cout<<shipCount(board2)<<" ships remaining to be attacked"<<endl;
						
						setColor(6,0); 
						cout<<"Current score "<<player1Score<<endl;
						setColor(7,0); 
						
						
						if(shipCount(board2) == 0)
			            {
			            	cout<<"\a";
			            	setColor(5, 0);
			                cout <<name1<<" destroyed "<<name2<<" ships"<<endl<<endl;
			                setColor(15, 0);
			                break;
			            }
						
					}
					printBoard(board2, true);
					turn=false;			
				}
				//PLAYER 2
				if(!turn) 
				{
					getch();
					clearScreen();
					cout<<name2<<" turn"<<endl;
					
					int player2Shots = shipCount(board2)+1; //CALCULATING SHOTS
					
					setColor(3,0);
					cout<<name1<<" Board"<<endl;
					setColor(7,0);
					printBoard(board1, true);
					
					cout << "Your are having "<<player2Shots<< " shots"<<endl;
					for(int j=0; j<player2Shots; j++)
					{
						setColor(3,0);
						cout<<"Shot: "<<j+1<<endl;
						setColor(7,0);
						playerAttack(board1, player2Score);
						cout<<shipCount(board1)<<" ships remaining to be attacked"<<endl;
						
						setColor(6,0); 
						cout<<"Current score "<<player2Score<<endl;
						setColor(7,0); 
						
						
						if(shipCount(board1) == 0)
			            {
			            	cout<<"\a";
			            	setColor(5, 0);
			                cout <<name2<<" destroyed "<<name1<<" ships"<<endl<<endl;
			                setColor(15, 0);
			                break;
			            }
			            
					}
					printBoard(board1, true);
					turn= true;
				}
				getch();
				clearScreen();
				opponentBoard( board1, board2);
				getch();
			}
			
			cout<<"Press any key to get results"<<endl;
			getch();
			clearScreen();
			displayResult( player1Score,  player2Score);
}

//ORIENTATION SET UP FOR EACH SHIP
void applyOrientation()
{
	cout <<"Enter row number: ";
			cin >> row;
			while(row!=0 && row!=1 && row!=2 && row!=3 && row!=4 && row!=5 && row!=6 && row!=7 && row!=8 && row!=9)
			{
				setColor(15, 4);
				cout << "invalid row"
					 <<endl;
				setColor(15, 0);	 
				cout <<"Choose your row ... Again: ";
				cin  >> row;
			}
			cout << "Enter coloumn number: ";
			cin >> coloumn;	
			while(coloumn!=0 && coloumn!=1 && coloumn!=2 && coloumn!=3 && coloumn!=4 && coloumn!=5 && coloumn!=6 && coloumn!=7 && coloumn!=8 && coloumn!=9)
			{
				setColor(15, 4);
				cout << "invalid coloumn"
					 <<endl;
				setColor(15, 0);	 
				cout <<"Choose your coloumn ... Again: ";
				cin  >> coloumn;
			}
			cout << "Enter H for horzontal ship setting and V for vertival :";
			cin >> orientation; 
			while(orientation!='h' && orientation!='H'&& orientation!='v'&& orientation!='V')
			{ 
				setColor(15, 4);
				cout<<"invalid orientation chosen, choose again: ";
				setColor(15, 0);
				cin >> orientation;
			}
}


void setPlayerShips(char board[10][10])
{
	for(int i=1; i<6; i++)
	{
		if(i==1)
		{
			shipSize=5;
			bool checkShip = false;
			while(!checkShip)
			{
			setColor(3, 0);
			cout << "Aircraft carrier (size 5)"
				 <<endl;
			setColor(15, 0); 

			 applyOrientation();
			 
			if (orientation=='h' || orientation=='H')
			{
				if(coloumn+shipSize-1<=9)
				{
					for(int i=coloumn; i<shipSize+coloumn; i++)
					{
						if(board[row][i]=='S'||board[row][i]=='A'||board[row][i]=='B'||board[row][i]=='P'||board[row][i]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[row][i]='A';
							overlap=false;
							checkShip=true;
						}
					}	
			    }
			    else
				{
					cout << "ship cant be fit in the board";
					continue;
				}
			}
			else if (orientation=='v' || orientation=='V')
			{
				if(row+shipSize-1<=9)
				{
					for(int i=row; i<shipSize+row; i++)
					{
						if(board[i][coloumn]=='S' || board[i][coloumn]=='A' || board[i][coloumn]=='B' ||board[i][coloumn]=='P'|| board[i][coloumn]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[i][coloumn]='S';
							overlap=false;
							checkShip=true;
						}
					}
				}
				else
				{
					cout << "ship cant be fit in the board";
					continue;
				}
			}
			
			initializeBoard( board);
		}
	}
		
		if(i==2)
		{
			bool checkShip = false;
			while(!checkShip)
			{
			
			cout << "press any key......."<<endl;
			getch();
			clearScreen();
			setColor(3, 0);
			shipSize=4;
			cout << "Battleship (size 4)"<<endl;
			setColor(15, 0);
			
			applyOrientation();
			
			if (orientation=='h' || orientation=='H')
			{
				if(coloumn+shipSize-1<=9)
				{
					for(int i=coloumn; i<shipSize+coloumn; i++)
					{
						if(board[row][i]=='S'||board[row][i]=='A'||board[row][i]=='B'||board[row][i]=='P'||board[row][i]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[row][i]='B';
							overlap=false;
							checkShip=true;
						}
					}	
			    }
			    else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			else if (orientation=='v' || orientation=='V')
			{
				if(row+shipSize-1<=9)
				{
					for(int i=row; i<shipSize+row; i++)
					{
						if(board[i][coloumn]=='S' || board[i][coloumn]=='A' || board[i][coloumn]=='B' ||board[i][coloumn]=='P'|| board[i][coloumn]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
						break;
						}
						else
						{
							board[i][coloumn]='B';
							overlap=false;
							checkShip=true;
						}
					}
				}
				else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			
			initializeBoard( board);
		}
	}
		if(i==3)
		{
			bool checkShip = false;
			while(!checkShip)
			{
			cout << "press any key......."<<endl;
			getch();
			clearScreen();
			setColor(3, 0);
			shipSize=3;
			cout << "Destroyer (size 3)"<<endl;
			setColor(15, 0);
			
			applyOrientation();
		if (orientation=='h' || orientation=='H')
			{
				if(coloumn+shipSize-1<=9)
				{
					for(int i=coloumn; i<shipSize+coloumn; i++)
					{
						if(board[row][i]=='S'||board[row][i]=='A'||board[row][i]=='B'||board[row][i]=='P'||board[row][i]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break; 
						}
						else
						{
							board[row][i]='D';
							overlap=false;
							checkShip=true;
						}
					}	
			    }
			    else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			else if (orientation=='v' || orientation=='V')
			{
				if(row+shipSize-1<=9)
				{
					for(int i=row; i<shipSize+row; i++)
					{
						if(board[i][coloumn]=='S' || board[i][coloumn]=='A' || board[i][coloumn]=='B' ||board[i][coloumn]=='P'|| board[i][coloumn]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[i][coloumn]='D';
							overlap=false;
							checkShip=true;
						}
					}
				}
				else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			
			initializeBoard( board);
		}}
		
		if(i==4)
		{
			bool checkShip = false;
			while(!checkShip)
			{
			cout << "press any key......."<<endl;
			getch();
			clearScreen();
			shipSize=3;
			setColor(3, 0);
			cout << "Submarine (size 3)"<<endl;
			setColor(15, 0);
			
			applyOrientation();
			
		if (orientation=='h' || orientation=='H')
			{
				if(coloumn+shipSize-1<=9)
				{
					for(int i=coloumn; i<shipSize+coloumn; i++)
					{
						if(board[row][i]=='S'||board[row][i]=='A'||board[row][i]=='B'||board[row][i]=='P'||board[row][i]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[row][i]='S';
							overlap=false;
							checkShip=true;
						}
					}	
			    }
			    else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			else if (orientation=='v' || orientation=='V')
			{
				if(row+shipSize-1<=9)
				{
					for(int i=row; i<shipSize+row; i++)
					{
						if(board[i][coloumn]=='S' || board[i][coloumn]=='A' || board[i][coloumn]=='B' ||board[i][coloumn]=='P'|| board[i][coloumn]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[i][coloumn]='S';
							overlap=false;
							checkShip=true;
						}
					}
				}
				else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			
			initializeBoard( board);
		}
	}
		
		if(i==5)
		{
			bool checkShip = false;
			while(!checkShip)
			{
			cout << "press any key......."<<endl;
			getch();
			clearScreen();
			shipSize=2;
			setColor(3, 0);
			cout << "Patrol Boat (size 2)"<<endl;
			setColor(15, 0);
			
			applyOrientation();
			
		if (orientation=='h' || orientation=='H')
			{
				if(coloumn+shipSize-1<=9)
				{
					for(int i=coloumn; i<shipSize+coloumn; i++)
					{
						if(board[row][i]=='S'||board[row][i]=='A'||board[row][i]=='B'||board[row][i]=='P'||board[row][i]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[row][i]='P';
							overlap=false;
							checkShip=true;
						}
					}	
			    }
			    	else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			else if (orientation=='v' || orientation=='V')
			{
				if(row+shipSize-1<=9)
				{
					for(int i=row; i<shipSize+row; i++)
					{
						if(board[i][coloumn]=='S' || board[i][coloumn]=='A' || board[i][coloumn]=='B' ||board[i][coloumn]=='P'|| board[i][coloumn]=='D')
						{
							overlap=true;
							cout << "Boat over lap!!! press key to place ship again..."<<endl;
							break;
						}
						else
						{
							board[i][coloumn]='P';
							overlap=false;
							checkShip=true;
						}
					}
				}
				else
				{
					cout << "ship cant be fit in the board"<<endl;
					continue;
				}
			}
			
			initializeBoard( board);
	
	}}
} 
}

//FUNCTION TO ADJUST SHIPS AT RANDOM POSITIONS
void setRandomShips(char board[10][10])
{
	clearBoard(board); // Clear board before placing ships
	clearScreen();
	
	for(int i=1; i<6; i++)
	{
		if(i==1)
		{
			shipSize=5;
			bool checkShip = false;
			while(!checkShip)
			{
				row = rand()%10;
				coloumn = rand()%10;
				orientation = rand()%2; 
			 
			 	// HORIZONTAL
				if (orientation==0) 
				{
					if(coloumn+shipSize-1<=9)
					{
						overlap = false; 
						for(int j=coloumn; j<shipSize+coloumn; j++)
						{
							if(board[row][j]=='S'||board[row][j]=='A'||board[row][j]=='B'||board[row][j]=='P'||board[row][j]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)//CHECK OVERLAP
						{
							for(int j=coloumn; j<shipSize+coloumn; j++)
							{
								board[row][j]='A';
							}
							checkShip=true;
						}
					}
				}
				//VERTICAL
				else if (orientation==1) 
				{
					if(row+shipSize-1<=9)
					{
						overlap = false; 
						
						for(int j=row; j<shipSize+row; j++)
						{
							if(board[j][coloumn]=='S' || board[j][coloumn]=='A' || board[j][coloumn]=='B' ||board[j][coloumn]=='P'|| board[j][coloumn]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						// CHECK OVERLAP
						if(!overlap)
						{
							for(int j=row; j<shipSize+row; j++)
							{
								board[j][coloumn]='A';
							}
							checkShip=true;
						}
					}
				}
			}
		}
		
		if(i==2)
		{
			shipSize=4; // Battleship
			bool checkShip = false;
			while(!checkShip)
			{
				row = rand()%10;
				coloumn = rand()%10;
				orientation = rand()%2;
			
				if (orientation==0) 
				{
					if(coloumn+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=coloumn; j<shipSize+coloumn; j++)
						{
							if(board[row][j]=='S'||board[row][j]=='A'||board[row][j]=='B'||board[row][j]=='P'||board[row][j]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=coloumn; j<shipSize+coloumn; j++)
							{
								board[row][j]='B';
							}
							checkShip=true;
						}
					}
				}
				else if (orientation==1) 
				{
					if(row+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=row; j<shipSize+row; j++)
						{
							if(board[j][coloumn]=='S' || board[j][coloumn]=='A' || board[j][coloumn]=='B' ||board[j][coloumn]=='P'|| board[j][coloumn]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=row; j<shipSize+row; j++)
							{
								board[j][coloumn]='B';
							}
							checkShip=true;
						}
					}
				}
			}
		}
		
		if(i==3)
		{
			shipSize=3; 
			bool checkShip = false;
			while(!checkShip)
			{
				row = rand()%10;
				coloumn = rand()%10;
				orientation = rand()%2;
				
				if (orientation==0)
				{
					if(coloumn+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=coloumn; j<shipSize+coloumn; j++)
						{
							if(board[row][j]=='S'||board[row][j]=='A'||board[row][j]=='B'||board[row][j]=='P'||board[row][j]=='D')
							{
								overlap=true;
								break; 
							}
						}
						
						if(!overlap)
						{
							for(int j=coloumn; j<shipSize+coloumn; j++)
							{
								board[row][j]='D';
							}
							checkShip=true;
						}
					}
				}
				else if (orientation==1)
				{
					if(row+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=row; j<shipSize+row; j++)
						{
							if(board[j][coloumn]=='S' || board[j][coloumn]=='A' || board[j][coloumn]=='B' ||board[j][coloumn]=='P'|| board[j][coloumn]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=row; j<shipSize+row; j++)
							{
								board[j][coloumn]='D';
							}
							checkShip=true;
						}
					}
				}
			}
		}
		
		if(i==4)
		{
			shipSize=3; 
			bool checkShip = false;
			while(!checkShip)
			{
				row = rand()%10;
				coloumn = rand()%10;
				orientation = rand()%2;
			
				if (orientation==0)
				{
					if(coloumn+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=coloumn; j<shipSize+coloumn; j++)
						{
							if(board[row][j]=='S'||board[row][j]=='A'||board[row][j]=='B'||board[row][j]=='P'||board[row][j]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=coloumn; j<shipSize+coloumn; j++)
							{
								board[row][j]='S';
							}
							checkShip=true;
						}
					}
				}
				else if (orientation==1)
				{
					if(row+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=row; j<shipSize+row; j++)
						{
							if(board[j][coloumn]=='S' || board[j][coloumn]=='A' || board[j][coloumn]=='B' ||board[j][coloumn]=='P'|| board[j][coloumn]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=row; j<shipSize+row; j++)
							{
								board[j][coloumn]='S';
							}
							checkShip=true;
						}
					}
				}
			}
		}
		
		if(i==5)
		{
			shipSize=2; 
			bool checkShip = false;
			while(!checkShip)
			{
				row = rand()%10;
				coloumn = rand()%10;
				orientation = rand()%2;
			
				if (orientation==0)
				{
					if(coloumn+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=coloumn; j<shipSize+coloumn; j++)
						{
							if(board[row][j]=='S'||board[row][j]=='A'||board[row][j]=='B'||board[row][j]=='P'||board[row][j]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=coloumn; j<shipSize+coloumn; j++)
							{
								board[row][j]='P';
							}
							checkShip=true;
						}
					}
				}
				else if (orientation==1)
				{
					if(row+shipSize-1<=9)
					{
						overlap = false;
						
						for(int j=row; j<shipSize+row; j++)
						{
							if(board[j][coloumn]=='S' || board[j][coloumn]=='A' || board[j][coloumn]=='B' ||board[j][coloumn]=='P'|| board[j][coloumn]=='D')
							{
								overlap=true;
								break;
							}
						}
						
						if(!overlap)
						{
							for(int j=row; j<shipSize+row; j++)
							{
								board[j][coloumn]='P';
							}
							checkShip=true;
						}
					}
				}
			}
		}
	}

	initializeBoard(board);
}


//FUNCTION FOR THE PLAYER ATTCK ON THE SHIPS
void playerAttack(char opponentBoard[10][10] , int &playerScore)
{
	bool alreadyAttacked=true;

	while(alreadyAttacked)
	{
		//SELECTION OF ROWS
		cout <<"Enter row number: ";
		cin >> row;
				
		while(row!=0 && row!=1 && row!=2 && row!=3 && row!=4 && row!=5 && row!=6 && row!=7 && row!=8 && row!=9)
		{
			setColor(15, 4);
			cout << "invalid row"
				 <<endl;
			setColor(15, 0);	 
			cout <<"Choose your row ... Again: ";
			cin  >> row;
		}
		
		//SELECTION OF COLOUMN
		cout << "Enter coloumn number: ";
		cin >> coloumn;	
		while(coloumn!=0 && coloumn!=1 && coloumn!=2 && coloumn!=3 && coloumn!=4 && coloumn!=5 && coloumn!=6 && coloumn!=7 && coloumn!=8 && coloumn!=9)
		{
			setColor(15, 4);
			cout << "invalid coloumn"
				 <<endl;
			setColor(15, 0);	 
			cout <<"Choose your coloumn ... Again: ";
			cin  >> coloumn;
		}
		//CHECK IF THE POSITION IS ALREADY ATTACKED OR NOT
		if(opponentBoard[row][coloumn]=='X' || opponentBoard[row][coloumn]=='O')
		{
			cout << "this position was Already attacked";
			alreadyAttacked=true;
		}
		else
		{
			alreadyAttacked=false;
		}
	}
		
		//UPDATING THE TABLE AFTER ATTACK
		if(opponentBoard[row][coloumn]=='S' || opponentBoard[row][coloumn]=='A' || 
		   opponentBoard[row][coloumn]=='B' || opponentBoard[row][coloumn]=='P' || 
		   opponentBoard[row][coloumn]=='D')
		{
			opponentBoard[row][coloumn]='X';
			setColor(2,0); 
			cout <<"IT WAS A HIT!!"
				 <<endl;
			setColor(7,0); 	 
			cout<<"+10 points"
				 <<endl;
			playerScore+=10;	 
		}
		else
		{
			opponentBoard[row][coloumn]='O';
			setColor(4,0); 
			cout <<"IT WAS A MISS!!"
				 <<endl;
			setColor(7,0); 
			cout<<"-1 points"
				 <<endl;
			playerScore-=1;
		}
}

//DISPLAY WORD FUNCTION TO BE DISPLAYED AFTER THE PLAYER WIN OR LOOSE THE GAME ALONG WITH IT ALSO UPDATE LEADERBOARD
void displayResult(int player1Score, int player2Score)
{
		 setColor(1, 0);	
			cout << "----------------------------------------------------------------------------"
				 << endl;
			setColor(6, 0);	
			cout <<endl<< "                       RESULTS!"
				 <<endl;
			setColor(1, 0);	
			cout << "----------------------------------------------------------------------------"
				 << endl;
			setColor(15, 0);
			cout << name1 <<"'s Score: " << player1Score
				 << endl
				 << name2 <<"'s Score: " << player2Score<<endl;
		 
	if(player1Score>player2Score)
	{
		setColor(2, 0);
		cout<<"Congragulations "<<name1<<" WON THE GAME"<<endl;
		setColor(4, 0);
		cout<<"SADLY "<<name2<<" LOSS THE GAME"<<endl;
		setColor(15, 0);
        updateBoard(name1, player1Score);
		
	}
	else if(player1Score<player2Score)
	{
		setColor(2, 0);
		cout<<"Congragulations "<<name2<<" WON"<<endl;
		setColor(4, 0);
		cout<<"SADLY "<<name1<<" LOSS THE GAME"<<endl;
		setColor(15, 0);
        updateBoard(name2, player2Score);
	}
	else
	{
		cout<<"IT WAS A DRAW"<<endl;
	}
	
	cout << "Press any key to return to main menu..."<<endl;
	getch();	 
		 
}

//COUNTING THE SHIPS SO THAT IS WOULD BE EASIER TO MAINTAIN THE SHOTS
int shipCount(char board[10][10])
{
	bool shipA=false,
		 shipB=false,
		 shipD=false,
		 shipS=false,
		 shipP=false;
		 
	int count=0;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(board[i][j]=='A')
			{
				shipA=true;
			}
			if(board[i][j]=='B')
			{
				shipB=true;
			}
			if(board[i][j]=='D')
			{
				shipD=true;
			}
			if(board[i][j]=='S')
			{
				shipS=true;
			}
			if(board[i][j]=='P')
			{
				shipP=true;
			}
		}
	}
	
	if(shipA)
	{count++;}
	
	if(shipB)
	{count++;}	
	
	if(shipD)
	{count++;}	
	
	if(shipS)
	{count++;}	
	
	if(shipP)
	{count++;}		 
	
	return count;
}

//COVER PAGE
void game()
{	
	setColor(3, 0);
	cout<<"--------------------------------------------------------------------------------------"<<endl
		<<"--------------------------------------------------------------------------------------"<<endl<<endl;
	setColor(6, 0);
	cout<<"                     B A T T L E   S H I P   G A M E "<<endl<<endl;
	cout << "                                  __/___            "<<endl;
    cout << "                            _____/______|           "<<endl;
    cout << "                    _______/_____\\_______\\_____     "<<endl;
    cout << "                    \\              < < <       |    "<<endl;
    cout << "                    ----------------------------"<<endl;
    cout << "                    ----------------------------"<<endl<<endl;
	setColor(3, 0);
	cout<<"--------------------------------------------------------------------------------------"<<endl
		<<"--------------------------------------------------------------------------------------"<<endl;
	setColor(7, 0);

	cout<<"                          NAME: HAMNA NOOR"<<endl
		<<"                         ROLL No. 251-3113"<<endl
		<<"                            CLASS: SE-D"<<endl;
	setColor(5, 0);
	cout<<"                 PROGRAMMING FUNDAMENTAL PROJECT"<<endl;
	setColor(7, 0);
	cout<<"                SUBMITTED TO: SIR BILAL KHALID DAR"<<endl 
		<<"                  DEPARTMENT OF COMPUTER SCIENCE"<<endl 
		<<"                          FAST NUCES"<<endl;
		setColor(3, 0);
	cout<<"--------------------------------------------------------------------------------------"<<endl
		<<"--------------------------------------------------------------------------------------"<<endl
		<<endl
		<<endl
		<<endl
		<<endl
		<<endl
		<<endl;
	setColor(7, 0);	
	cout<<"(press any key to continue........)";
		getch();
		
showGameMenu();		
	
}



//================================================================================
//                                 MAIN FUNCTION
//================================================================================
int main()
{
	srand(time(0));
//	showGameMenu();
	game();
}



