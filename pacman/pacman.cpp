//
//		Date: Oct 20, 2014
//		Author: Utkarsh Maheshwari
//

#include<fstream.h>			//For file management
#include<conio.h>				//For clrscr() and getch()
#include<process.h>			//For exit()
#include<string.h>			//For working with strings
#include<stdlib.h>			//For standard library functions
#include<iomanip.h>			//For setw()
#include<dos.h>					//For delay()




//------------------------------Functions-----------------------------------

void setupGame();				//Instals game and prepares files for first run
void init();						//Initializes the game
void draw(int cont=1);	//Draws the game
void turn();						//Lets the user take his turn
void ghostMover(int);		//Moves the ghosts : Takes ghostID as its parameter
void welcome();					//Displays welcome screen
void gamepause();				//Pauses games and displays pause screen
void selector(int);			//Selects options : Takes choice as its parameter
void selectMap();				//Selects map
void loadMap();					//Loads the map
void lose();						//Called when user loses a game
void win();							//Called when user wins a game
void save();						//Saves game session
void load();						//Loads game session
void highScore();				//Displays high score
void saveScore(int);		//Saves score : Takes total score as its parameter
void howTo();						//Displays 'How to Play' instructions




//----------------------------Global Variables------------------------------

char board[20][20];			//Stores the value of the gameboard
int lives;							//Number of lives left
int moves;							//Moves made by the user
int posx;								//Position of users - x co-ordinate
int posy;								//Position of users - y co-ordinate
int cursor;							//Cursor direction
int boardsize;					//Size of the game board
char mapFile[20];				//Name of the map file
int ghosts;							//Number of ghosts
int score;							//Number of dots collected
int total;							//Total score




//-------------------------------Classes------------------------------------

class makeGhost{
    private:
        int id;

    public:
        makeGhost(int a, int b, int c)
        {
            px=a;
            py=b;
            id=c;
        }
        makeGhost()
        {
            px=0;
            py=0;
            prevState='1';
            moveState=0;
        }
        int px, py;
        int moveState;
        char prevState;
        void setPos(int a, int b, int c)
        {
            px=a;
            py=b;
            id=c;
        }
        void move()
        {
            ghostMover(id);
        }
};



//----------------------------Global Objects--------------------------------

makeGhost ghost[5];



// Main function
int main(){
    randomize();
    setupGame();
    clrscr();

    cout<<"\n\n";
    cout<<setw(35)<<"----::::PACMAN::::----\n\n";
    cout<<setw(34)<<"by Utkarsh Maheshwari\n";
    cout<<setw(36)<<"and Parth S. Patnaik\n\n\n";
    delay(1500);

    welcome();

    //cout<<"\n\nPress any key to exit...";
    //getch();
    return 0;
}



//-------------------------Function Definitions-----------------------------

void setupGame(){

    //Create atleast one map
    fstream file;
    fstream create;
    file.open("map1.map", ios::in);
    if(!file)
    {
        create.open("map1.map", ios::out);
        create<<"0000000000000000000002111111111111111110010101010000010100100101010111111101111001010101000001000100011111011111111111000101000100100100010001011111001001111110010010000010010000100100111111111100001001000010000001000010010000100011111111100111101111100010001001001110001000100010010010000011111000100100100000100010001001111111111000111010010010000010000010100111111111111111333000000000000000000000";
        create.close();
    }
    file.close();

    //Create savegame database
    file.open("savegame.db", ios::in);
    if(!file)
    {
        create.open("savegame.db", ios::out);
        create.close();
    }
    file.close();

    //Create Highscore file
    file.open("scores.db", ios::in);
    if(!file)
    {
        create.open("scores.db", ios::out);
        for(int a=0;a<5;a++)
        {
            create<<"Noname"<<endl;
            create<<0<<endl;
        }
        create.close();
    }
    file.close();

}



void init(){
    moves=0;
    lives=2;
    cursor=16;
    ghosts=0;
    score=0;

    boardsize=20;
    selectMap();
    loadMap();

    draw();
}



void draw(int cont){
    int dotsleft=0;

    clrscr();
    for(int a=0;a<boardsize;a++)
    {
        cout<<"\n  ";
        for(int b=0;b<boardsize;b++)
        {
            if(board[a][b]=='0')
            {
                cout<<"#";
            }
            if(board[a][b]=='1')
            {
                dotsleft++;
                cout<<".";
            }
            if(board[a][b]=='2')
            {
                cout<<(char)cursor;
                posx=a;
                posy=b;
            }
            if(board[a][b]=='3')
            {
                cout<<"X";
            }
            if(board[a][b]=='4')
            {
                cout<<" ";
            }
            cout<<" ";
        }
        if(a==3)
            cout<<"\t"<<"Lives left: \t"<<lives;
        if(a==5)
            cout<<"\t"<<"Dots collected:\t"<<score;
        if(a==7)
            cout<<"\t"<<"Dots left: \t"<<dotsleft;
        if(a==9)
            cout<<"\t"<<"Moves: \t\t"<<moves;
    }
    cout<<"\n\n";

    if(dotsleft==0)
    {
        win();
        exit(0);
    }
    if(cont)
        turn();
}



void turn(){
    char ch;
    int cont=1,nx,ny;
    nx=posx;
    ny=posy;
    ch=getch();

    switch(ch)
    {
        case('w'):
            if(board[posx-1][posy]!='0' && cursor!=31)
            {
                nx--;
                cursor=30;
            }
            else cont=0;
            break;

        case('s'):
            if(board[posx+1][posy]!='0' && cursor!=30)
            {
                nx++;
                cursor=31;
            }
            else cont=0;
            break;

        case('d'):
            if(board[posx][posy+1]!='0' && cursor!=17)
            {
                ny++;
                cursor=16;
            }
            else cont=0;
            break;

        case('a'):
            if(board[posx][posy-1]!='0' && cursor!=16)
            {
                ny--;
                cursor=17;
            }
            else cont=0;
            break;

        case(' '):
            gamepause();
            moves--;
            break;

        default:
            cont=0;
    }
    if(cont)
    {
        moves++;
        if(board[nx][ny]=='1')
        {
            score++;
        }
        board[posx][posy]='4';
        board[nx][ny]='2';

        for(int a=0;a<ghosts;a++)
        {
            ghost[a].move();
        }
    }
    draw();
    getch();
}



void ghostMover(int gID){
    int nx, ny;
    int cont;
    nx=ghost[gID].px;
    ny=ghost[gID].py;
    do
    {
        cont=0;
        if(board[nx+1][ny]!='0')
            cont++;
        if(board[nx-1][ny]!='0')
            cont++;
        if(board[nx][ny+1]!='0')
            cont++;
        if(board[nx][ny-1]!='0')
            cont++;

        if(cont>2)
        {
            ghost[gID].moveState=random(4);
        }

        if(ghost[gID].moveState==0)
            nx++;
        else if(ghost[gID].moveState==1)
            ny++;
        else if(ghost[gID].moveState==2)
            nx--;
        else if(ghost[gID].moveState==3)
            ny--;
        else
        {
            clrscr();
            cout<<"Error!";
            getch();
            exit(1);
        }

        if(board[nx][ny]=='0')
        {
            ghost[gID].moveState=random(4);
            nx=ghost[gID].px;
            ny=ghost[gID].py;
            continue;
        }
        break;
    }while(1);
    if(board[nx][ny]=='2')
    {
        board[nx][ny]='3';
        board[ghost[gID].px][ghost[gID].py]=ghost[gID].prevState;
        draw(0);
        lose();
    }
    else if(board[ghost[gID].px][ghost[gID].py]=='2')
    {
        board[ghost[gID].px][ghost[gID].py]='3';
        draw(0);
        lose();
    }
    else
    {
        if(ghost[gID].prevState=='3')
        {
            ghost[gID].prevState='1';
        }
        board[ghost[gID].px][ghost[gID].py]=ghost[gID].prevState;
        ghost[gID].prevState=board[nx][ny];
        board[nx][ny]='3';
        ghost[gID].px=nx;
        ghost[gID].py=ny;
    }
}



void welcome(){
    char ch=0;
    int a=10;

    while(ch!=' ' && ch!='\n')
    {
        clrscr();

        switch(ch)
        {
            case('w'):
                if(a==10)
                    a=14;
                else
                    a--;
                break;
            case('s'):
                if(a==14)
                    a=10;
                else
                    a++;
                break;
        }

        cout<<"\n\n";
        cout<<setw(35)<<"----::::PACMAN::::----\n\n";
        cout<<setw(34)<<"by Utkarsh Maheshwari\n";
        cout<<setw(36)<<"and Parth S. Patnaik\n\n\n";

        cout<<" Press \'space\' to select an option and \'w\' or \n\'s\' to move through choices\n\n";

        cout<<"\t";
        (a==10)? cout<<(char)16 : cout<<" ";
        cout<<" New Game\n"
            <<"\t";
        (a==11)? cout<<(char)16 : cout<<" ";
        cout<<" Load Game\n"
            <<"\t";
        (a==12)? cout<<(char)16 : cout<<" ";
        cout<<" Highscores\n"
            <<"\t";
        (a==13)? cout<<(char)16 : cout<<" ";
        cout<<" How to play\n"
            <<"\t";
        (a==14)? cout<<(char)16 : cout<<" ";
        cout<<" Exit\n";

        cout<<"\n\n";
        ch=getch();
    }
    selector(a);
}



void gamepause(){
    char ch=0;
    int a=0;

    while(ch!=' ' && ch!='\n')
    {
        clrscr();

        switch(ch)
        {
            case('w'):
                if(a==0)
                    a=6;
                else
                    a--;
                break;
            case('s'):
                if(a==6)
                    a=0;
                else
                    a++;
                break;
        }

        cout<<"\n\n";
        cout<<setw(35)<<"----::::PACMAN::::----\n\n";
        cout<<setw(34)<<"by Utkarsh Maheshwari\n";
        cout<<setw(36)<<"and Parth S. Patnaik\n\n\n";

        cout<<" Press \'space\' to select an option and \'w\' or \n\'s\' to move through choices\n\n";

        cout<<"\t";
        (a==0)? cout<<(char)16 : cout<<" ";
        cout<<" Resume Game\n"
            <<"\t";
        (a==1)? cout<<(char)16 : cout<<" ";
        cout<<" New Game\n"
            <<"\t";
        (a==2)? cout<<(char)16 : cout<<" ";
        cout<<" Save Game\n"
            <<"\t";
        (a==3)? cout<<(char)16 : cout<<" ";
        cout<<" Load Game\n"
            <<"\t";
        (a==4)? cout<<(char)16 : cout<<" ";
        cout<<" Highscores\n"
            <<"\t";
        (a==5)? cout<<(char)16 : cout<<" ";
        cout<<" How to play\n"
            <<"\t";
        (a==6)? cout<<(char)16 : cout<<" ";
        cout<<" Exit\n";

        cout<<"\n\n";
        ch=getch();
    }
    selector(a);
}



void selector(int a){
    switch(a)
    {
        case(0):
            draw();
            break;
        case(1):
        case(10):
            init();
            break;
        case(2):
            save();
            break;
        case(3):
        case(11):
            load();
            break;
        case(4):
            highScore();
            break;
        case(12):
            highScore();
            welcome();
            break;
        case(5):
            howTo();
            break;
        case(13):
            howTo();
            welcome();
            break;
        case(6):
        case(14):
            clrscr();
            cout<<"\nDo you wish to exit?(Y/N)";
            char ch;
            ch=getch();
            if(ch=='y' || ch=='Y' || ch==' ')
            {
                exit(0);
            }
            if(a==14)
                welcome();
            break;

        default:
            cout<<"Error!";

    }
}



void selectMap(){
    clrscr();
    char n[1];
    cout<<"\n\n Enter map number: ";
    n[0]=getch();
    strcpy(mapFile,"map");
    strncat(mapFile,n,1);
    strcat(mapFile,".map");
}



void loadMap(){

    fstream map(mapFile,ios::in);
    if(!map)
    {
        clrscr();
        cout<<"\n\n Map does not exist!\n\nPress any key to continue...";
        getch();
        selectMap();
        loadMap();
        draw();
    }
    char ch;
    int i=0,j=0;
    while(i<boardsize)
    {
        map.get(ch);
        if(ch=='3')
        {
            ghost[ghosts].setPos(i,j,ghosts);
            ghosts++;
        }

        board[i][j]=ch;
        j++;
        if(j==boardsize)
        {
            j=0;
            i++;
        }
    }
    map.close();
}



void lose(){
    if(lives)
    {
        lives--;

        clrscr();
        int total=(score*49)-moves;
        cout<<"\n\n Lives left: "<<lives;
        cout<<"\n\n\n Total dots collected:\t"<<score<<" dots";
        cout<<"\n Total Moves taken:\t"<<moves<<" moves";
        cout<<"\n\n Your total score:\t"<<total<<" points.";

        cout<<"\n\n\n Press any key to retry...";
        getch();

        cursor=16;
        ghosts=0;
        loadMap();
        draw();
    }
    else
    {
        cout<<"You lose!";
        clrscr();
        int total=(score*49)-moves;
        cout<<"\n\n\n Total dots collected:\t"<<score<<" dots";
        cout<<"\n Total Moves taken:\t"<<moves<<" moves";
        cout<<"\n\n Your total score:\t"<<total<<" points.";

        saveScore(total);

        cout<<"\n Press any key to continue...";
        getch();

        highScore();
        welcome();
    }
}



void win(){
    clrscr();
    cout<<"\n\nYou won!\n";
    int total=(score*49)-moves+10000;
    saveScore(total);
    highScore();
    welcome();
}



void save(){
    char sname[20], name[20];
    int buffer;

    fstream file("savegames.db", ios::in);
    clrscr();
    cout<<"\n\n\n";
    if(!file)
    {
        cout<<"Error Opening File!...";
    }
    cout<<" Save as: ";
    cin>>name;
    while(1)
    {

        if(file.eof())
            break;

        file>>sname;
        if(!strcmp(name,sname))
        {
            clrscr();
            cout<<"\n\nSavegame exists...";
            cout<<"\n Overwrite?(y/n): ";
            if(getch()=='y')
            {
                break;
            }
            else
            {
                cout<<"\n\n Save as: ";
                cin>>name;
                file.seekg(0);
                continue;
            }
        }

        file>>buffer;
        file>>buffer;
        file>>buffer;
        file>>buffer;
        file>>sname;
    }
    file.close();

    file.open("savegames.db", ios::app | ios::out);
    if(!file)
    {
        cout<<"Can't read file!";
        getch();
        exit(1);
    }
    file<<name<<endl;
    file<<score<<endl;
    file<<lives<<endl;
    file<<moves<<endl;
    file<<cursor<<endl;
    file<<mapFile<<endl;

    file.close();

    fstream game(name, ios::out);
    for(int a=0;a<boardsize;a++)
        for(int b=0;b<boardsize;b++)
            game<<board[a][b];
    game.close();

    cout<<"\n Game Saved!";
    cout<<"\n Press any key to continue...";
    getch();
}



void load(){
    char name[20];
    char sname[20];
    char n[10];
    int buffer;
    int found=0;

    clrscr();
    fstream file("savegames.db", ios::in);
    if(!file)
    {
        cout<<"Can't read file!";
        getch();
        exit(1);
    }

    cout<<"\n\n Enter saved game name: ";
    cin>>name;
    while(!file.eof())
    {
        file>>sname;
        if(!strcmp(name,sname))
        {
            file>>score;
            file>>lives;
            file>>moves;
            file>>cursor;
            file>>n;
            found=1;
            break;
        }
        else
        {
            file>>buffer;
            file>>buffer;
            file>>buffer;
            file>>buffer;
            file>>sname;
        }
    }

    if(found==0)
    {
        cout<<"\nSavegame not found!...";
        getch();
    }
    else
    {
        file.close();
        ghosts=0;
        boardsize=20;
        strcpy(mapFile,name);
        loadMap();
        strcpy(mapFile,n);

        draw();
    }
}



void highScore(){
    clrscr();
    class scores
    {
        public:
            char name[30];
            int score;
    }item[5];

    cout<<"\n\n"<<setw(30)<<"::HIGHSCORES::";
    cout<<"\n\n\n";
    fstream high("scores.db", ios::in);
    if(high)
    {
        cout<<setw(20)<<"NAME";
        cout<<"     "<<"SCORE\n";
        for(int a=0;a<5;a++)
        {
            high>>item[a].name;
            high>>item[a].score;

            if(high.eof())
                break;
            cout<<"\n"<<setw(20)<<item[a].name;
            cout<<"  :  "<<item[a].score;
        }

    }
    else
    {
        cout<<"\n\nError opening file...";
    }
    high.close();

    cout<<"\n\nPress any key to continue...";
    getch();
}



void saveScore(int total){

    class scores
    {
        public:
            char name[30];
            int score;
    }item[5];

    fstream high("scores.db", ios::in);
    if(high)
    {
        for(int a=0;a<5;a++)
        {
            high>>item[a].name;
            high>>item[a].score;

            if(high.eof())
                break;
        }
        int b=0;
        while(b<a && total<item[b].score)
            b++;

        if(b!=a)
        {
            for(a=4;a>b;a--)
            {
                strcpy(item[a].name,item[a-1].name);
                item[a].score=item[a-1].score;
            }
            cout<<"\n\n Enter your name to save score: ";
            char name[30];
            cin>>item[b].name;
            item[b].score=total;

            fstream save("scores.db", ios::out);
            if(save)
            {
                for(a=0;a<5;a++)
                {
                    save<<item[a].name<<endl;
                    save<<item[a].score<<endl;
                }
                cout<<"\n High score saved!";
            }
            else
            {
                cout<<"Error saving!";
            }
            save.close();
        }
    }
    else
    {
        cout<<"\n\nError opening file...";
        getch();
    }
    high.close();

}



void howTo(){
    clrscr();
    cout<<"\n\n";

    cout<<" OBJECTIVE\n";
    cout<<"\tCollect all the dots.\n\n";

    cout<<" CHALLENGE\n";
    cout<<"\tAvoid or escape the ghosts maked with \'X\' and\n\tfinish the game in least number of moves\n\n";

    cout<<" CONTROLS\n";
    cout<<"\tw \t-> move up"<<endl
        <<"\ts \t-> move down"<<endl
        <<"\ta \t-> move left"<<endl
        <<"\td \t-> move right"<<endl
        <<"\tspace \t-> pause game"<<endl;

    getch();
}
