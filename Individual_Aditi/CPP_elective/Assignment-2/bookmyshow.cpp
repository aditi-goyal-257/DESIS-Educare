#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include<bits/stdc++.h>

using namespace std;

int num_rows = 5;
int num_columns = 10;

class user{

    string name;
    
    public:

    user(string user_name){
        name = user_name;
        
    }

    void searchByTitle(string title);
    void searchByLanguage(string language);
    void searchByGenre(string genre);
    void searchByReleaseDate(string releaseDate);
    void searchByCity(string city);
    void listCities();
    void selectMovie(string title);
    void registerUser(string title, int reg);

};

void user::searchByCity(string city_name){
    Json::Value data;
    Json::Reader reader;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    set<string>movies;
    bool found = false;
    int index;
    
    for(int i=0;i<data.size();i++){
        if(data[i]["city"].asString() == city_name){
            found = true;
            index = i;
            break;
        }
    }

    if(!found){
        cout<<"SORRY! WE HAVE NO SHOWS IN THIS CITY :( \n";
        return;
    }

    Json::Value cinemas = data[index]["cinemas"];

    for(int i=0;i<cinemas.size();i++){
        for(int j=0;j<cinemas[i]["movies"].size(); j++){
            movies.insert(cinemas[i]["movies"][j]["movie_name"].asString());
        }
    }

    for(auto movie: movies){
        cout<<movie<<"\n";
    }
}
void user::searchByLanguage(string language){
    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    set<string> movies;

    bool found = false;
    
    for(int i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(int j=0;j<cinemas.size(); j++){

            for(int k = 0; k < cinemas[j]["movies"].size(); k++){
                string lang = cinemas[j]["movies"][k]["language"].asString();

                if(lang == language){
                    found = true;
                    movies.insert(cinemas[j]["movies"][k]["movie_name"].asString());
                }
            }
        }

    
    }

    if(!found){
        cout<<"SORRY! WE HAVE ANY SHOWS ANYWHERE  FOR THIS LANGUAGE :( \n";
        return;
    }
    cout<<"MOVIES ARE AS FOLLOWS:\n";
    for(auto movie: movies){
        cout<<movie<<"\n";
    }
}
void user::searchByGenre(string genre){
    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    set<string> movies;

    bool found = false;
    
    for(int i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(int j=0;j<cinemas.size(); j++){

            for(int k = 0; k < cinemas[j]["movies"].size(); k++){
                string gen = cinemas[j]["movies"][k]["genre"].asString();

                if(gen == genre){
                    found = true;
                    movies.insert(cinemas[j]["movies"][k]["movie_name"].asString());
                }
            }
        }

    
    }

    if(!found){
        cout<<"SORRY! WE HAVE ANY SHOWS ANYWHERE  FOR THIS GENRE :( \n";
        return;
    }
    cout<<"MOVIES ARE AS FOLLOWS:\n";
    for(auto movie: movies){
        cout<<movie<<"\n";
    }
    
}
void user::searchByReleaseDate(string releaseDate){
    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    set<string> movies;

    bool found = false;
    
    for(int i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(int j=0;j<cinemas.size(); j++){

            for(int k = 0; k < cinemas[j]["movies"].size(); k++){
                string date = cinemas[j]["movies"][k]["release_date"].asString();

                if(date == releaseDate){
                    found = true;
                    movies.insert(cinemas[j]["movies"][k]["movie_name"].asString());
                }
            }
        }

    
    }

    if(!found){
        cout<<"SORRY! WE HAVE ANY SHOWS ANYWHERE  FOR THIS RELEASE DATE:( \n";
        return;
    }
    cout<<"MOVIES ARE AS FOLLOWS:\n";
    for(auto movie: movies){
        cout<<movie<<"\n";
    }
}
void user::searchByTitle(string title){
    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

   
    bool found = false;
    
    for(int i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(int j=0;j<cinemas.size(); j++){

            for(int k = 0; k < cinemas[j]["movies"].size(); k++){
                string movie_name = cinemas[j]["movies"][k]["movie_name"].asString();

                if(movie_name == title){
                    found = true;
                    cout<<"YES! THE MOVIE IS PRESENT!\n";

                    return;

                }
            }
        }

    
    }

    if(!found){
        cout<<"SORRY! WE HAVE ANY SHOWS ANYWEHER FOR THIS MOVIE :( \n";
        return;
    }

}
void user::listCities(){
    Json::Value data;
    Json::Reader reader;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    cout<<data.size()<<" CITIES REGISTERED\n";

    for(int i=0;i<data.size();i++){
        cout<<data[i]["city"].asString()<<"\n";
    }

}
void user::registerUser(string title, int reg){

    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

    int count = 1;

    bool seats[num_rows*num_columns];
    bool found = false;

    int i,j,k,l;
    
    for(i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(j=0;j<cinemas.size(); j++){

            for(k = 0; k < cinemas[j]["movies"].size(); k++){
                string movie_name = cinemas[j]["movies"][k]["movie_name"].asString();

                if(movie_name == title){
                
                    for(l=0; l< cinemas[j]["movies"][k]["halls"].size(); l++){

                        if(count == reg){
                            found = true;

                            cout<<"THE SEATING ARRANGEMENT IS AS FOLLOWS: \n\n\n";

                            for(int m = 0; m <num_rows; m++){
                                for(int n= 0; n< num_columns; n++){
                                    string used = cinemas[j]["movies"][k]["halls"][l]["seats"][m*num_columns + n]["used"].asString();
                                    if(used == "True"){
                                        cout<<"   __X__   ";
                                        seats[m*num_columns + n] = true;
                                    }
                                    else{
                                        cout<<"   _____   ";
                                        seats[m*num_columns+n] = false;
                                    }
                                }
                                cout<<"\n";
                                if(m==0){
                                for(int n = 0; n< num_columns; n++){
                                    cout<<"     "<<m*num_columns+n<<"     ";
                                }
                                }
                                else{
                                    for(int n = 0; n< num_columns; n++){
                                    cout<<"    "<<m*num_columns+n<<"     ";
                                }
                                }
                                cout<<"\n\n\n";
                            }
                            break;

                        }
                        count+=1;



                    }
                    if(found){
                        break;
                    }
                }
                
            }

            if(found){
                break;
            }

        
        }
        if(found){
            break;
        }
    
    }
   
    int num, choice;
    vector<int>booked_seats;
   
    while(true){
        cout<<"PRESS 1 TO BOOK A SEAT\n";
        cout<<"PRESS 2 IF YOU DO NOT WANT TO BOOK ANY MORE SEATS!"<<endl;
        cin>>choice;
        if(choice == 1){
            cout<<"ENTER SEAT NUMBER YOU WANT TO BOOK!"<<endl;
            cin>>num;

            if(seats[num]){
                cout<<"THE SEAT IS ALREADY BOOKED!\n";
            }
            else{

                data[i]["cinemas"][j]["movies"][k]["halls"][l]["seats"][num]["used"] = "True";
                data[i]["cinemas"][j]["movies"][k]["halls"][l]["seats"][num]["user"] = this->name;


                cout<<"BOOKED THE SEAT!"<<endl;

                seats[num] = true;
                booked_seats.push_back(num);
            }

        }
        else if(choice == 2){
            cout<< "SEAT NUMBERS BOOKED: "<<endl;
            for(auto x: booked_seats){
                cout<<x<<" ";
            }
            cout<<endl;
            ofstream filep;
            filep.open("data.json");

            Json::StyledWriter writer;
            filep << writer.write(data);

            filep.close();

            return;
        }
        else{
            cout<<"INVALID CHOICE! TRY AGAIN";
        }

    }
    

    
}
void user::selectMovie(string title){

    Json::Value data;
    Json::Reader reader;
    Json::Value cinemas;

    ifstream data_file("data.json");
    reader.parse(data_file, data);

   
    bool found = false;

    int count = 1;

    
    for(int i=0;i<data.size();i++){

        cinemas = data[i]["cinemas"];

        for(int j=0;j<cinemas.size(); j++){

            for(int k = 0; k < cinemas[j]["movies"].size(); k++){
                string movie_name = cinemas[j]["movies"][k]["movie_name"].asString();

                if(movie_name == title){
                    found = true;
                    
                    for(int l=0; l< cinemas[j]["movies"][k]["halls"].size(); l++){

                        cout<<"<<<<<<<<< SHOW NUMBER "<<count<<" >>>>>>>>>>\n";
                        count+=1;

                        cout<<"CITY: "<<data[i]["city"]<<"\n";
                        cout<<"CINEMA: "<<data[i]["cinemas"][j]["cinema_name"]<<"\n";
                        cout<<"HALL NUMBER: "<<data[i]["cinemas"][j]["movies"][k]["halls"][l]["hall_num"]<<"\n";
                        cout<<"DATE: "<<data[i]["cinemas"][j]["movies"][k]["halls"][l]["date"]<<"\n";
                        cout<<"SLOT: "<<data[i]["cinemas"][j]["movies"][k]["halls"][l]["slot"]<<endl;
                       

                    }
                }
            }
        }

    
    }

    if(!found){
        cout<<"SORRY! WE HAVE ANY SHOWS ANYWEHER FOR THIS MOVIE :( "<<endl;
        return;
    }

    int reg;
    cout<<"ENTER SHOW NUMBER TO REGISTER FOR PARTICULAR SHOW"<<endl;
    cin>>reg;

    /*Add handling*/
    (*this).registerUser(title, reg);

}

void menuForUser(user curr_user){
    system("clear");
    int choice;
    string line;
    char c;
    while(true){
        cout<<"\n\n <<<<<<<<<<<<<<<<<<< USER OPTIONS >>>>>>>>>>>>>>>>\n\n";
        cout<<"PRESS 1 FOR SEARCHING MOVIE BY TITLE\n";
        cout<<"PRESS 2 FOR SEARCHING MOVIE BY LANGUAGE\n";
        cout<<"PRESS 3 FOR SEARCHING MOVIE BY GENRE\n";
        cout<<"PRESS 4 FOR SEARCHING MOVIE BY RELEASE DATE\n";
        cout<<"PRESS 5 FOR SEARCHING MOVIE BY CITY NAME\n";
        cout<<"PRESS 6 FOR LISTING CITIES\n";
        cout<<"PRESS 7 FOR SELECTING A MOVIE\n";
        cout<<"PRESS 8 FOR EXITING"<<endl;
        
        cin>>choice;
        cin.ignore();
        system("clear");
        switch(choice){
            
            case 1:{
               cout<<"ENTER MOVIE TITLE"<<endl;
               getline(cin, line);
               curr_user.searchByTitle(line);
               break;
            }

            case 2:{
                cout<<"ENTER LANGUAGE IN WHICH YOU WANT MOVIES"<<endl;
                getline(cin, line);
                curr_user.searchByLanguage(line);
                break;
            }
            case 3:{
                cout<<"ENTER GENRE"<<endl;
                getline(cin, line);
                curr_user.searchByGenre(line);
                break;
            }
            case 4:{
                cout<<"ENTER RELEASE DATE"<<endl;
                getline(cin, line);
                curr_user.searchByReleaseDate(line);
                break;
            }
            case 5:{
                cout<<"ENTER CITY NAME"<<endl;
                getline(cin,line);
                curr_user.searchByCity(line);
                break;
            }
            case 6:{
                curr_user.listCities();
                break;
            }
            case 7:{
               cout<<"ENTER MOVIE TITLE"<<endl;
               getline(cin,line);
               curr_user.selectMovie(line);
               break;
            }
            case 8: {
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
        
        cout<<"\n\n <<<<<<<<<<<<<<<<<<<<<<<< WELCOME TO BOOK-MY-SHOW >>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
        cout<<"PRESS 1 TO BOOK FOR EXISITNG USER\n";
        cout<<"PRESS 2 FOR ADDING A NEW USER\n";
        cout<<"PRESS 3 FOR EXITING"<<endl;
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    menu();
    return 0;
}
