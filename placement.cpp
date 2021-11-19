#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
using namespace std;



// Candidate Class
class candidate{

  protected:
  	int enrollno;
    string name;
    string degree;
    int year;
    string branch;
    string email;
    string secEmail;
    string contactNo;
    float cgpa;
    string resume;

public:
    bool isCoordinator;

// the big ques: array or file?
   
 public:
 	int getEnrollNo(){
 		return enrollno;
 	}
 	void inputDetails();
 	void outputDetails();
 	void viewVisitingCompanies();
    // void viewVisitingCompaniesNext2days()  optional, we'll do later
    void registerForCompany();
    void viewRegisteredCompany();
     
};




//Coordinator Class

class coordinator: public candidate{
  
  private:

  	int coordinatorId;
  
  public:
  	static string password;
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
  	//	this->adminId = id;
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

// Format: 9 11 2021

//Company Class
class company{

  private:
  	string compName;
    date visitingDate;
    string recruiterName;
    string recruiterEmail;
    string recruiterContactNo;
    string jobDescription;

 public:
 	string getName(){
        return compName;
 	}
    void inputDetails();
    void outputDetails();
    void viewRegisteredCandidates();

};





// Candidate Class's Functions

void candidate::inputDetails(){
  cout<<"\n\n Enter Candidate Details";
  cout<<"\n\n   Enrollment Number:  ";
  cin>>enrollno;
  cout<<"\n\n   Name:  ";
  cin>>name;
  cout<<"\n   Degree:  ";
  cin>>degree;
  cout<<"\n   Year of Graduation:  ";
  cin>>year;
  cout<<"\n\n   Branch:  ";
  cin>>branch;
  cout<<"\n\n   Email-ID:  ";
  cin>>email;
  cout<<"\n\n   Secondary Email-ID:  ";
  cin>>secEmail;
  cout<<"\n\n   Contact Number:  ";
  cin>>contactNo;
  cout<<"\n\n   CGPA:  ";
  cin>>cgpa;
  cout<<"\n\n   Resume Link:  ";
  cin>>resume;
 
}


void candidate::outputDetails(){
  cout<<"\nCandidate Details";
  cout<<"\n Enrollment Number:  "<<enrollno;
  cout<<"\n Name:  "<<name;
  cout<<"\n Degree:  "<<degree;
  cout<<"\n Year of Graduation:  "<<year;
  cout<<"\n Branch:  "<<branch;
  cout<<"\n Email-ID:  "<<email;
  cout<<"\n Secondary Email-ID:  "<<secEmail;
  cout<<"\n Contact Number:  "<<contactNo;
  cout<<"\n CGPA:  "<<cgpa;
  cout<<"\n Resume Link:  "<<resume;
}

void candidate::viewVisitingCompanies(){
   
   company c;
   fstream file;
   file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);
   //string name,l,found=0;
  // cout<<"\n\n Enter Company Name: ";
   //cin>>name;
   file.seekg(0);
   int k;
 while(1){
     file.read((char*)&c,sizeof(c));
      c.outputDetails();
      if(!file)
      break;
  }
 file.close();
}


//friend function
void candidate::registerForCompany(){
   
  int eno; string cname;
  cout<<"\n Enter your Enrollment Number:  ";
  cin>>eno;

  cout<<"\n Enter the name of the company you want to register for: ";
  cin>>cname;

  candidate c;
  fstream file;
  file.open("candidates.txt",ios::ate|ios::in|ios::out|ios::binary);


  // check for valid candidate and company name


// Adding student record to company file

  file.seekg(0);
  int k;
 while(1){
     file.read((char*)&c,sizeof(c));
     if(c.getEnrollNo()==eno){

     	fstream file1;
     	string filename = cname + ".txt";

     	file1.open(filename, ios::app|ios::binary);
	    file1.write((char*)&c,sizeof(c));
        file1.close();
     }
      if(!file)
      break;
  }
 file.close();



// Adding company record to student file

company cmp;
// fstream file;
  file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);

  file.seekg(0);
 
 while(1){
     file.read((char*)&cmp,sizeof(cmp));
     if(cmp.getName()==cname){

     	fstream file1;
     	string filename = to_string(eno) + ".txt";

     	file1.open(filename, ios::app|ios::binary);
	    file1.write((char*)&cmp,sizeof(cmp));
        file1.close();
     }
      if(!file)
      break;
  }
 file.close();


 cout<<"\n\n Registration Done!";
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
      c.outputDetails();
      if(!file)
      break;
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
    cout<<"\n\n\tCompany's Record has been added to the database.";
    getch();
}

void coordinator::deleteVisitingCompany(){
   company allCompanies[100];
   fstream file;
   file.open("companies.txt",ios::ate|ios::in|ios::out|ios::binary);
   string name;
   int l,found=0;
   cout<<"\n\n Enter Company Name: ";
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

    if(name==allCompanies[l].getName()){
     found=1;
    }
    else
     file.write((char*)&allCompanies[l],sizeof(allCompanies[l]));
  }

    if(found==0)
        cout<<"\n\n\tCompany does not exist in the database.";
    else
    	cout<<"\n\n\t Company's Record has been deleted.";
  file.close();
  getch();

}


// Admin Class's Functions

void admin::addCandidate(){

  cout<<"\n\n   Is the student coordinating for tnp? (y/n):  ";
  char choice;
  cin>>choice;

  if(choice=='y'){
  	//isCoordinator = true;
    
    coordinator c;
    c.inputDetails();
    fstream file;
	file.open("coordinators.txt", ios::app|ios::binary);
	file.write((char*)&c,sizeof(c));
    file.close();
    cout<<"\n\n\tCoordinator Record has been added to the database.";
    getch();


  }else{
  	//isCoordinator = false;

  	candidate c;
	c.inputDetails();
    fstream file;
	file.open("candidates.txt", ios::app|ios::binary);
	file.write((char*)&c,sizeof(c));
    file.close();
    cout<<"\n\n\tCandidate Record has been added to the database.";
    getch();
  }
	
}



// Comapny Class's Functions

void company::inputDetails(){
  cout<<"\n\n Enter Company Details";
  cout<<"\n\n   Name:  ";
  cin>>compName;
  cout<<"\n   Visiting Date:  ";
  visitingDate.input();
  cout<<"\n   Recruiter Name:  ";
  cin>>recruiterName;
  cout<<"\n   Recruiter Email-ID:  ";
  cin>>recruiterEmail;
  cout<<"\n   Recruiter Contact Number:  ";
  cin>>recruiterContactNo;
  cout<<"\n   Job Description:  ";
  cin>>jobDescription;
}

void company::outputDetails(){
  cout<<"\n\n\nCompany Details";
  cout<<"\n\n Name:  "<<compName;
  cout<<"\n Visiting Date:  "; visitingDate.output();
  cout<<"\n Job Description:  "<<jobDescription;  
  cout<<"\n\n Recruiters Details";
  cout<<"\n Recruiter Name:  "<<recruiterName;
  cout<<"\n Recruiter Email-ID:  "<<recruiterEmail;
  cout<<"\t\t\t Recruiter Contact Number:  "<<recruiterContactNo;
 
}


void company::viewRegisteredCandidates(){
  
   candidate c;
   fstream file;
   string filename = compName + ".txt";
   file.open(filename, ios::ate|ios::in|ios::out|ios::binary);
   file.seekg(0);
   int k;
 while(1){
     file.read((char*)&c,sizeof(c));
      c.outputDetails();
      if(!file)
      break;
  }
 file.close();
}

int main(){

	admin a;
	a.addCandidate();
	return 0;

}