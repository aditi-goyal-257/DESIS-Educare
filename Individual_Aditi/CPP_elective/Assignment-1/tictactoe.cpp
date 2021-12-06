#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <ctime>


using namespace std;


#define MAX_MATCHES 1000


int solve(int x, int y, int z, int i){
    if(x==i && y==i && z==-1){
        return 2;
    }
    if(x==i && z==i && y==-1){
        return 1;
    }
    if(z==i && y==i && x==-1){
        return 0;
    }
    return -1;
}

class board{

    public:

    int val[9];
    int winner;
    time_t start_time;
    time_t stop_time;

    board(){
        start_time = time(NULL);
        for(int i=0;i<9;i++){
            val[i]= -1;
        }
        winner = -1;
    }
    int findWinner();
    int findEmpty();
    int pickNext();
    bool checkEmpty(int pos);
    void printState();
    void setWinner(int winner);
    void fillSquare(int pos, int val);
    void setEnd();
    time_t getGameTime();
};

class user:public board{

    char name[50];
    int matches_played;
    int matches_won;
    int matches_lost;

    time_t total_start;
    time_t total_end;
    
    board history[MAX_MATCHES];

    public:

    user(string user_name){
        total_start = time(NULL);
        for(int i=0;i<50;i++){
            name[i] = user_name[i];
        }
        matches_played = 0;
        matches_won = 0;
        matches_lost = 0;
    }
    
    void getDetails_short();
    void getDetails_long();
    void addGame(board* board);
    void startGame();
    void updateEnd();
    time_t getSessionTime();

    
};

void user::updateEnd(){
    this->total_end = time(NULL);
}

time_t user::getSessionTime(){
    return this->total_end - this->total_start;
}

time_t board::getGameTime(){
    return this->stop_time- this->start_time;
}

void board::setEnd(){
    this->stop_time = time(NULL);
}


void user::getDetails_short(){
    cout<<"TOTAL MATCHES PLAYED: "<<this->matches_played<<"\n";
    cout<<"TOTAL MATCHES WON: "<<this->matches_won<<"\n";
    cout<<"TOTAL MATCHES LOST: "<<this->matches_lost<<"\n";
    cout<<"TOTAL MATCHES DRAWN: "<<this->matches_played-this->matches_won-this->matches_lost<<"\n";
    printf("TOTAL TIME ACROSS ALL GAMES: %ld SECONDS\n", (*this).getSessionTime());
}
void user::getDetails_long(){

    cout<<"TOTAL MATCHES PLAYED: "<<this->matches_played<<"\n";
    cout<<"TOTAL MATCHES WON: "<<this->matches_won<<"\n";
    cout<<"TOTAL MATCHES LOST: "<<this->matches_lost<<"\n";
    cout<<"TOTAL MATCHES DRAWN: "<<this->matches_played-this->matches_won-this->matches_lost<<"\n";

    for(int i=0;i<this->matches_played;i++){

        cout<<"FINAL STATE OF GAME "<<i+1<<"\n";
        this->history[i].printState();

        if(this->history[i].winner == 1){
            cout<<"YOU HAD WON THE GAME\n";
        }
        else if(this->history[i].winner == 0){
            cout<<"THE COMPUTER WON THE GAME\n";
        }
        else{
            cout<<"THE GAME WAS A DRAW\n";
        }
        printf("TOTAL TIME FOR THIS GAME: %ld SECONDS\n", (this->history[i]).getGameTime());
    }

}
void user::addGame(board* board){
    for (int i=0;i<9;i++){
        (this->history[this->matches_played]).val[i] = board->val[i];
    }

    this->history[this->matches_played].winner = board->winner;
    this->history[this->matches_played].stop_time = board->stop_time;
    this->history[this->matches_played].start_time = board->start_time;

}

void board::fillSquare(int pos, int value){
    this->val[pos] = value;
}

int board::findEmpty(){

    for(int i=0;i<9;i++){
        if(this->val[i] == -1){
            return i;
        }
    }

    return -1;

}
int board::pickNext(){
    /*Attack then defense*/
    for(int i=0;i<2;i++){

        /*rows*/


        for(int j=0;j<3;j++){
            int k = solve(this->val[3*j], this->val[3*j+1], this->val[3*j+2], i);
            if(k!=-1){
                return 3*j+k;
            }
        }


        /*columns*/
        for(int j=0;j<3;j++){
            int k = solve(this->val[j], this->val[3+j], this->val[6+j], i);
            if(k!=-1){
                return j+3*k;
            }
        }

        /*diagonals*/

        int arr[3] = {0, 4, 8};
        int k = solve(this->val[0], this->val[4], this->val[8], i);
        
        if(k!=-1){
            return arr[k];
        }

        k = solve(this->val[2], this->val[4], this->val[6], i);

        if(k!=-1){
            return (k+1)*2;
        }
    }

    int arr2[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

    for(int i=0;i<9;i++){
        if(this->val[arr2[i]] == -1){
            return arr2[i];
        }
    }

    return -1;
    
}

int board::findWinner(){

    /*Rows*/
    for(int i=0;i<3;i++){
        if(this->val[3*i] == this->val[3*i+1] && this->val[3*i]== this->val[3*i+2] && this->val[3*i] != -1){
            return this->val[3*i];
        }
    }

    /*Columns*/
    for(int i=0;i<3;i++){
        if(this->val[i] == this->val[3+ i] && this->val[i] == this->val[i+6] && this->val[i]!=-1){
            return this->val[i];
        }
    }

    if(this->val[0]==this->val[4] && this->val[0]== this->val[8] && this->val[0]!=-1){
        return this->val[0];
    }
    if(this->val[2]==this->val[4] && this->val[2]== this->val[6] && this->val[2]!=-1){
        return this->val[2];
    }

    for(int i=0; i<9;i++){
        if(this->val[i] == -1){
            return -2;
        }
    }

    return -1;


}

void board::setWinner(int winner){
    this->winner = winner;
}

void board::printState(){
    char symbols[9];
    for(int i=0;i<9;i++){
        if(this->val[i]==-1){
            symbols[i] = ' ';
        }
        else if(this->val[i]==0){
            symbols[i] = 'O';
        }
        else{
            symbols[i] = 'X';
        }
    }
    cout<<"\n_________________________________________________\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"|\t"<<symbols[0]<<"\t|\t"<<symbols[1]<<"\t|\t"<< symbols[2]<<"\t|\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"_________________________________________________\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"|\t"<<symbols[3]<<"\t|\t"<<symbols[4]<<"\t|\t"<< symbols[5]<<"\t|\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"_________________________________________________\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"|\t"<<symbols[6]<<"\t|\t"<<symbols[7]<<"\t|\t"<< symbols[8]<<"\t|\n";
    cout<<"|\t \t|\t \t|\t \t|\n";
    cout<<"_________________________________________________\n";

}

bool board::checkEmpty(int pos){
    if(this->val[pos]== -1){
        return true;
    }
    return false;
}

void user::startGame(){

    board curr_board;
    int turn = rand()%2;
    int pos;
    while(curr_board.findWinner()==-2){
        curr_board.printState();

        cout<<"X IS YOUR MARKER, O IS COMPUTER'S MARKER"<<"\n";

        pos = curr_board.findEmpty();

        if(pos == -1){
            break;
        }

        if(turn == 0){
            pos = curr_board.pickNext();
            cout<<"COMPUTER'S TURN!\n";
            curr_board.fillSquare(pos, turn);
        }
        else{

            cout<<"\n IT IS YOUR TURN! \n";
            cout<<" PRESS 1 TO FILL IN TOP ROW LEFT COLUMN \t  PRESS 2 TO FILL IN TOP ROW CENTER COLUMN \t PRESS 3 TO FILL IN TOP ROW RIGHT COLUMN \n";
            cout<<" PRESS 4 TO FILL IN CENTER ROW LEFT COLUMN \t  PRESS 5 TO FILL IN CENTER ROW CENTER COLUMN \t PRESS 6 TO FILL IN CENTER ROW RIGHT COLUMN \n";
            cout<<" PRESS 7 TO FILL IN BOTTOM ROW LEFT COLUMN \t  PRESS 8 TO FILL IN BOTTOM ROW CENTER COLUMN \t PRESS 9 TO FILL IN BOTTOM ROW RIGHT COLUMN \n";

            while(true){
                cin>> pos;
                if(pos < 1 || pos > 9){
                    cout<<"INVALID CHOICE! CHOOSE AGAIN\n";
                }
                else if(curr_board.checkEmpty(pos-1) == false){
                    cout<<"THE SQUARE IS ALREADY FILLED! CHOOSE AN EMPTY SQUARE!\n";
                }
                else{
                    break;
                }
            }
            curr_board.fillSquare(pos-1, turn);
        }

        cout<<"THE CURRENT BOARD LOOKS LIKE\n";

        
        turn = 1-turn;

    }

    curr_board.printState();
    
    int winner = curr_board.findWinner();
    curr_board.setWinner(winner);
    curr_board.setEnd();
    if(winner == 0){
        cout<<"OOPS! THE COMPUTER WON!"<<endl;
        this->matches_lost+=1;
    }
    else if(winner == 1){
        cout<<"CONGRATULATIONS! YOU WIN!"<<endl;
        this->matches_won+=1;
    }

    else{
        cout<<"IT IS A DRAW"<<endl;
    }
    (*this).addGame(&curr_board);
    this->matches_played+=1;
    (*this).updateEnd();
}

void menuForUser(user curr_user){
    system("clear");
    int choice;
    char c;
    while(true){
        cout<<"\n\n <<<<<<<<<<<<<<<<<<< USER OPTIONS >>>>>>>>>>>>>>>>\n\n";
        cout<<"PRESS 1 FOR A NEW GAME\n";
        cout<<"PRESS 2 FOR SHORT STATISTICS\n";
        cout<<"PRESS 3 FOR LONG STATISTICS\n";
        cout<<"PRESS 4 FOR LOGOUT"<<endl;
        
        cin>>choice;
        system("clear");
        switch(choice){
            case 1:{
               curr_user.startGame();
               break;

            }

            case 2:{
                curr_user.getDetails_short();
                break;
            }
            case 3:{
                curr_user.getDetails_long();
                break;
            }
            case 4: {
                return;
            }
            default:{
                cout<< "INVALID CHOICE! PRESS ANY KEY TO CONTINUE"<<endl;
                cin>>c;
                break;
            }
        }

    }
}

void menu(){
    int choice, user_num;
    string user_name;
    char filename[] = "users.txt";
    fstream fs;
    string line;
    char c;
    
    while(true){
        
        cout<<"\n\n <<<<<<<<<<<<<<<<<<<<<<<< WELCOME TO TIC-TAC-TOE >>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
        cout<<"PRESS 1 TO BEGIN A NEW GAME FOR EXISITNG USER\n";
        cout<<"PRESS 2 FOR ADDING A NEW USER\n";
        cout<<"PRESS 3 FOR EXITING THE GAME"<<endl;
        cin>>choice;

        system("clear");

        switch (choice){

            case 1:{
                cout<<"ENTER USER NAME"<<endl;
                cin>>user_name;
                fs.open(filename,fstream::out | fstream::in);
                bool found = false;
                while(getline(fs, line)){
                    if(line == user_name){
                        found = true;
                        break;
                    }
                }
                fs.close();

                if(found){
                    user curr_user(user_name); 
                    menuForUser(curr_user);
                }
                else{
                    cout<<"ERROR: THE USER WITH THIS NAME IS NOT FOUND! REGISTER AS A NEW USER FIRST! PRESS ANY KEY TO CONTINUE"<<endl;
                    cin>>c;
                }
                break;

            }

            case 2:{
                cout<<"ENTER THE NAME WITH WHICH YOU WANT TO REGISTER"<<endl;
                cin>>user_name;
                fs.open(filename,fstream::out | fstream::in);
                bool found = false;
                while(getline(fs, line)){
                    if(line == user_name){
                        found = true;
                        break;
                    }
                }
                fs.close();

                if(found){
                    cout<<"THE USER WITH THIS NAME ALREADY EXISTS! CHOOSE A NEW USER NAME! PRESS ANY KEY TO CONTINUE"<<endl;
                    cin>>c;
                }
                else{
                    fs.open(filename, fstream::app| fstream::in);
                    user_name = user_name + "\n";
                    fs.write(user_name.data(), user_name.size());
                    fs.close();
                    cout<<"USER ADDED SUCCESSFULLY"<<endl;
                }

                break;

            }

            case 3:{
                cout<<"BYE! EXITING NOW!"<<endl;
                return;
            }

            default:{

                cout<< "INVALID CHOICE! PRESS ANY KEY TO CONTINUE"<<endl;
                cin>>c;
                break;
            }

        
        }

    }
}

int main(){
    menu();
    return 0;
}
