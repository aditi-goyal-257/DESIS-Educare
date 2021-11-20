
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include<string.h>
using namespace std;



// Candidate Class
class candidate{

  protected:
    int enrollno;
    char name[50];
    char degree[40];
    int year;
    char branch[50];
    char email[100];
    char secEmail[100];
    char contactNo[20];
    float cgpa;
    char resume[100];
   
 public:
  int getEnrollNo(){
    return enrollno;
  }
  void inputDetails();
  void outputDetails();
  void viewVisitingCompanies();
  // void viewVisitingCompaniesNext2days()  : To view the companies visiting in next 2 days -> Future Scope
  void registerForCompany();
  void viewRegisteredCompany();
     
};


//Coordinator Class

class coordinator: public candidate{
  
  private:

    int coordinatorId;
  
  public:
    static string password;
    void registerForCompany();
    void addVisitingCompany();
    void deleteVisitingCompany();

};
string coordinator::password = "coord";


//Admin Class

class admin{
  
  private:
    int adminId;


  public:
   static string password;
    //admin(int id){
    //  this->adminId = id;
    //}
    void addCandidate();
};

string admin::password = "admin";


class date{
public:
  int day;
  int month;
  int year;

void input(){
  cin>>day>>month>>year;
}
void output(){
  cout<<day<<" "<<month<<" "<<year;
}
};

// Format for date: 9 11 2021


//Company Class
class company{

  private:
    char compName[50];
    date visitingDate;
    char recruiterName[100];
    char recruiterEmail[50];
    char recruiterContactNo[20];
    char jobDescription[50];

 public:
  char* getName(){
        return compName;
  }
    void inputDetails();
    void outputDetails();
    void viewRegisteredCandidates();

};



// Candidate Class's Functions

void candidate::inputDetails(){
  cout<<"\n\n\t Enter Candidate Details";
  cout<<"\n\n\t Enrollment Number:  ";
  cin>>enrollno;
  cout<<"\n\t Name:  ";
  cin>>name;
  cout<<"\n\t Degree:  ";
  cin>>degree;
  cout<<"\n\t Year of Graduation:  ";
  cin>>year;
  cout<<"\n\t Branch:  ";
  cin>>branch;
  cout<<"\n\t Email-ID:  ";
  cin>>email;
  cout<<"\n\t Secondary Email-ID:  ";
  cin>>secEmail;
  cout<<"\n\t Contact Number:  ";
  cin>>contactNo;
  cout<<"\n\t CGPA:  ";
  cin>>cgpa;
  cout<<"\n\t Resume Link:  ";
  cin>>resume;
 
}


void candidate::outputDetails(){
  cout<<"\n\n\t Candidate Details";
  cout<<"\n\n\t Enrollment Number:  "<<enrollno;
  cout<<"\n\t Name:  "<<name;
  cout<<"\n\t Degree:  "<<degree;
  cout<<"\n\t Year of Graduation:  "<<year;
  cout<<"\n\t Branch:  "<<branch;
  cout<<"\n\t Email-ID:  "<<email;
  cout<<"\n\t Secondary Email-ID:  "<<secEmail;
  cout<<"\n\t Contact Number:  "<<contactNo;
  cout<<"\n\t CGPA:  "<<cgpa;
  cout<<"\n\t Resume Link:  "<<resume;
}

void candidate::viewVisitingCompanies(){
   
   company c;
   fstream file;
   file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);
  
   file.seekg(0);
   int k;
 while(1){
     file.read((char*)&c,sizeof(c));
      
      if(!file)
      break;
      c.outputDetails();
  }
 file.close();
}

void candidate::registerForCompany(){
   
  int eno; 
  char companyName[50];

  cout<<"\n\n\t Enter the name of the company you want to register for: ";
  cin>>companyName;

 
  fstream file;

  // check for valid candidate and company name -> future scope


// Adding student record to company file

  file.seekg(0);
  int k;


      // adding student info in the company file
      fstream file1;
      string tempname(companyName);
      string filename = tempname + ".txt";

      file1.open(filename, ios::app|ios::binary);
       candidate c = *this;
      file1.write((char*)&c,sizeof(c));
      file1.close();

//     ----------------------
// Adding company record to student file
   company cmp;
   file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);

   file.seekg(0);
 
 while(1){

     file.read((char*)&cmp,sizeof(cmp));
     
     if(!file)
      break;

     if(!strcmp(cmp.getName(),companyName)){
      
      fstream file1;
      string filename = to_string(enrollno) + ".txt";

      file1.open(filename, ios::app|ios::binary);
      file1.write((char*)&cmp,sizeof(cmp));
        file1.close();
     }
      
  }
 file.close();
//       --------------------

 cout<<"\n\n\t Registration Done!";
}


void candidate::viewRegisteredCompany(){
  
   company c;
   fstream file;
   string filename = to_string(enrollno) + ".txt";
   file.open(filename, ios::ate|ios::in|ios::out|ios::binary);
   file.seekg(0);
   int k;
 while(1){
     file.read((char*)&c,sizeof(c));
      
      if(!file)
      break;

    c.outputDetails();
  }

 file.close();
}



//Coordinator Class's Functions

void coordinator::addVisitingCompany(){
    company c;
    c.inputDetails();
    fstream file;
  file.open("companies.txt", ios::app|ios::binary);
  file.write((char*)&c,sizeof(c));
    file.close();
    cout<<"\n\n\t Company's Record has been added to the database.";
    getch();
}


void coordinator::deleteVisitingCompany(){
   company allCompanies[100];
   fstream file;
   file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);
   char name[50];
   int l,found=0;
   cout<<"\n\n\t Enter Company Name: ";
   cin>>name;
   file.seekg(0);
   int k;
 for(k=0;;k++){
     file.read((char*)&allCompanies[k],sizeof(allCompanies[k]));
      if(!file)
      break;
  }
 file.close();

 file.open("companies.txt",ios::out|ios::binary);
  for(l=0;l<k;l++){

    if(!strcmp(name, allCompanies[l].getName())){
     found=1;
    }
    else
     file.write((char*)&allCompanies[l],sizeof(allCompanies[l]));
  }

    if(found==0)
        cout<<"\n\n\t Company does not exist in the database.";
    else
      cout<<"\n\n\t Company's Record has been deleted.";
  file.close();
  getch();

}

// overriding base's class function
void coordinator :: registerForCompany(){
   int eno; char cname[50];
  cout<<"\n\n\t Enter your Enrollment Number:  ";
  cin>>eno;

  cout<<"\n\t Enter the name of the company you want to register for: ";
  cin>>cname;

  coordinator c;
  fstream file;
  file.open("coordinators.txt",ios::ate|ios::in|ios::out|ios::binary);


  // check for valid candidate and company name -> future scope


// Adding student record to company file

  file.seekg(0);
  int k;
 while(1){
     file.read((char*)&c,sizeof(c));
     
      if(!file)
      break;
      
     if(c.getEnrollNo()==eno){

      fstream file1;
      string tempname(cname);
      string filename = tempname + ".txt";

      file1.open(filename, ios::app|ios::binary);
      file1.write((char*)&c,sizeof(c));
        file1.close();
     }
     
  }
 file.close();


// Adding company record to student file

company cmp;

  file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);

  file.seekg(0);
 
 while(1){
     file.read((char*)&cmp,sizeof(cmp));
     
      if(!file)
      break;
      
     if(!strcmp(cmp.getName(),cname)){

      fstream file1;
      string filename = to_string(eno) + ".txt";

      file1.open(filename, ios::app|ios::binary);
      file1.write((char*)&cmp,sizeof(cmp));
        file1.close();
     }
     
  }
 file.close();


 cout<<"\n\n\t Registration Done!";
}



// Admin Class's Functions

void admin::addCandidate(){

  cout<<"\n\n\t Is the student coordinating for tnp? (y/n):  ";
  char choice;
  cin>>choice;

  if(choice=='y'){
  
    coordinator c;
    c.inputDetails();
    fstream file;
  file.open("coordinators.txt", ios::app|ios::binary);
  file.write((char*)&c,sizeof(c));
    file.close();
    cout<<"\n\n\t Coordinator Record has been added to the database.";
    getch();


  }else{

    candidate c;
  c.inputDetails();
    fstream file;
  file.open("candidates.txt", ios::app|ios::binary);
  file.write((char*)&c,sizeof(c));
    file.close();
    cout<<"\n\n\t Candidate Record has been added to the database.";
    getch();
  }
  
}



// Comapny Class's Functions

void company::inputDetails(){
  cout<<"\n\n\t Enter Company Details";
  cout<<"\n\n\t   Name:  ";
  cin>>compName;
  cout<<"\n\t   Visiting Date:  ";
  visitingDate.input();
  cout<<"\n\t   Recruiter Name:  ";
  cin>>recruiterName;
  cout<<"\n\t   Recruiter Email-ID:  ";
  cin>>recruiterEmail;
  cout<<"\n\t   Recruiter Contact Number:  ";
  cin>>recruiterContactNo;
  cout<<"\n\t   Job Description:  ";
  cin>>jobDescription;
}

void company::outputDetails(){

  cout<<"\n\n\n\t Company Details";
  cout<<"\n\n\t Name:  "<<compName;
  cout<<"\n\t Visiting Date:  "; visitingDate.output();
  cout<<"\n\t Job Description:  "<<jobDescription;  
  cout<<"\n\n\t Recruiters Details";
  cout<<"\n\t Recruiter Name:  "<<recruiterName;
  cout<<"\n\t Recruiter Email-ID:  "<<recruiterEmail;
  cout<<"\n\t Recruiter Contact Number:  "<<recruiterContactNo;
 
}


void company::viewRegisteredCandidates(){
  
   candidate c;
   fstream file;
   string tempname(compName);
   string filename = tempname + ".txt";
   file.open(filename, ios::ate|ios::in|ios::out|ios::binary);
   file.seekg(0);
   int k;
 while(1){
     file.read((char*)&c,sizeof(c));
      
      if(!file)
      break;
      
      c.outputDetails();
  }
 file.close();
}



// some utility functions -> to be used in menu driven code

//Utility function 1: searches for a candidate record in 'candidates' file and returns it 
candidate dataCandidateFromMemory(int eno){
  candidate c;
  fstream file;
  file.open("candidates.txt",ios::ate|ios::in|ios::out|ios::binary);
  file.seekg(0);
  
  while(1){
     file.read((char*)&c,sizeof(c));
      if(!file)
      break;
     if(c.getEnrollNo()==eno){
            return c;
     }
  }
  file.close();
  return c;
}

//Utility function 2: searches for a coordinator record in 'coordinators' file and returns it 
coordinator dataCoordinatorFromMemory(int eno){
  coordinator c;
  fstream file;
  file.open("coordinators.txt",ios::ate|ios::in|ios::out|ios::binary);
  file.seekg(0);
  
  while(1){
     file.read((char*)&c,sizeof(c));
     if(!file)
      break;
     if(c.getEnrollNo()==eno){
            return c;
     }
  }
  file.close();
  return c;
}

//Utility function 3: searches for a company record in 'companies' file and returns it 
company dataCompanyFromMemory(char* companyName){
  company c;
  fstream file;

  file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);
  file.seekg(0);
  
  while(1){
     file.read((char*)&c,sizeof(c));
     if(!file)
      break;
     if(!strcmp(companyName, c.getName())){
            return c;
     }
      
  }
  file.close();
  return c;
}


void menuForCandidate(candidate c){
    while(1){
     //clrscr();
      system ("CLS");
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\t<<<<<<<<<<<<<<<<<< Candidate OPTIONS >>>>>>>>>>>>>>>>>>>>>>>>\n";
      cout<<"\n\n\t 1. Show My Profile \n\n\t 2. View Visiting Companies \n\n\t 3. Register For a company \n\n\t 4. See companies for which you have registered \n\n\t 5. Exit to main menu\n\n"; 
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\tEnter choice:  ";int choice;
      cin>>choice;
      switch(choice){
          case 1: c.outputDetails(); getch();
                break;
          case 2: c.viewVisitingCompanies(); getch();
                  break;
          case 3: c.registerForCompany(); getch();
                break;
                
          case 4:   c.viewRegisteredCompany(); getch();
                break;
          case 5: return;
          default: cout<<"\n\n\tInvalid choice. Press any key to enter choice again.\n"; getch();
                   break;
      }
    }

}

void menuForCoordinator(coordinator c){
    while(1){
    //clrscr();
      system ("CLS");
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\t<<<<<<<<<<<<<<<<<< Coordinator OPTIONS >>>>>>>>>>>>>>>>>>>>>>>>\n";
      cout<<"\n\n\t 1. Show My Profile \n\n\t 2. View Visiting Companies \n\n\t 3. Register For a company \n\n\t 4. See companies for which you have registered \n\n\t 5. Add New Comapnies \n\n\t 6. Delete Companies from drive \n\n\t 7. Exit to main menu\n\n"; 
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      int choice;
      cout<<"\n\n\tEnter choice:  ";
      cin>>choice;
      switch(choice){
          case 1: c.outputDetails(); getch();
                break;
          case 2: c.viewVisitingCompanies(); getch();
                  break;
          case 3: c.registerForCompany(); getch();
                break;
                
          case 4:   c.viewRegisteredCompany(); getch();
                break;
          
           case 5:   c.addVisitingCompany(); getch();
                break;
          
           case 6:   c.deleteVisitingCompany(); getch();
                break;
           case 7: return;
           default: cout<<"\n\n\tInvalid choice. Press any key to enter choice again.\n"; getch();
                    break;
      }
    }

}


void menuForAdmin(){

    while(1){
     // clrscr();
      system ("CLS");
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\t<<<<<<<<<<<<<<<<<< ADMIN OPTIONS >>>>>>>>>>>>>>>>>>>>>>>>\n";
      cout<<"\n\n\t 1. Add Candidates\n\n\t 2. Exit to main menu\n\n";
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\tEnter choice: ";
      int choice;
      cin>>choice;
      switch(choice){
          case 1: 
                admin a;
                a.addCandidate(); getch();
                break;
          case 2:
                return;
                break;
          default:
                cout<<"Invalid choice. Press any key to enter choice again.\n"; getch();
                break;
        }
    }

}

void menuForCompany(company c){
    while(1){
      //clrscr();
      system ("CLS");
       cout<<"\t________________________________________________\n";
      cout<<"\t________________________________________________\n" ;
      cout<<"\n\n\t<<<<<<<<<<<<<<<<<< COMPANY OPTIONS >>>>>>>>>>>>>>>>>>>>>>>>\n";
      cout<<"\n\n\t 1. View Registered Candidates\n\n\t 2. Exit to main menu\n\n";
       cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
            cout<<"\n\n\tEnter choice:  ";
      int choice;
      cin>>choice;
      switch(choice){
          case 1: 
                c.viewRegisteredCandidates(); getch();
                break;
          case 2:
                return;
                break;
          default:
                cout<<"\n\n\tInvalid choice. Press any key to enter choice again.\n"; getch();
                break;
        }
    }
}


void menu(){
  int choice;
  for(;;){
    system ("CLS");
    //clrscr();
    string inputPass; int enrollmentNo;   char companyName[50];
    cout<<"\n\n\t<<<<<<<<<<<<<<<<<< MENU >>>>>>>>>>>>>>>>>>>>>>>>\n";

            cout<<"\t________________________________________________\n";
            cout<<"\t________________________________________________\n" ;
            cout<<"\n\tWho are you?\n";
     cout<<"\n\n\t 1. Admin\n\n\t 2. Candidate\n\n\t 3. Coordinator \n\n\t 4. Recruiter\n\n\t 5. I want to exit\n\n";
     cout<<"\t________________________________________________\n";
     cout<<"\t________________________________________________\n" ;
     cout<<"\n\n\t Enter your choice:  ";
    cin>>choice;
    switch(choice){
      case 1:{ //string inputPass;
              cout<<"\n\n\t Enter password for admin:  ";
              cin>>inputPass;
              if(inputPass!=admin::password){
                cout<<"\n\n\t Wrong Password! Please try again."; getch();
                break;
              }
              menuForAdmin();
              break;
            }
      case 2:  {cout<<"\n\n\t Enter your enrollment No :  ";  
                                                         //show();
               cin>>enrollmentNo;
               
               //cout<<"Enter password for Candidate :\n";
               //cin>>inputPass;
               //if(inputPass!=password){
                  //cout<<"Wrong Password! Please try again."
                 // break;
              //}
              
               candidate currCandidate = dataCandidateFromMemory(enrollmentNo);
               menuForCandidate(currCandidate);

               break;
               }
      case 3: { int enrollno;
              cout<<"\n\n\t Enter your enrollment No: ";                                              
               cin>>enrollno;
               
               cout<<"\n\n\t Enter password for Coordinator: ";
               cin>>inputPass;
               if(inputPass!=coordinator::password){
                  cout<<"\n\n\t Wrong Password! Please try again.";
                  getch();
                  break;
              }
              
               coordinator currCoordinator = dataCoordinatorFromMemory(enrollno);
               menuForCoordinator(currCoordinator);                 

              break;
            }
      case 4: { cout<<"\n\n\t Enter password: ";
              
              cin>>companyName;
              company currCompany = dataCompanyFromMemory(companyName);
              menuForCompany(currCompany);
              break;}
      case 5:                             
              cout<<endl<<endl; 
              return;
       default: 
              cout<<"\n\n\t Invalid choice. Press any key to enter choice again.\n"; getch();
              break;

      }
    }
}

int main(){
    menu();
    cout<<"\n\n\t Thank You!\n\n\n";
    return 0;
}


//Congo! 

