	       // COMPUTER PROJECT

// Source Code:


// Header files included-
#include<fstream.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<iomanip.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>

// Definition of class "student" begins.

class student {  public:
		 char admno[6],name[20],stbno[6];
		 int token;




		  void create_student()
		 {

		    clearviewport();
		    gotoxy(20,2);
		    cout<<"\nEntry for a new student\t";
		    cout<<"\n Enter the admission number\t";
		    cin>>admno;
		    cout<<"\nEnter the name of the student\t";
		    gets(name);
		    token=0;
		    stbno[0]= '/0';
		    cout<<"\nStudent record succesfully created\t";
		 }



		    void show_student()
		    {
		       cout<<"\n Admission no.  :"<<admno;
		       cout<<"\n Student name:  ";
		       puts(name);
		    }


		    void modify_student()
		    {
		       cout<<"\nAdmission no.  :"<<admno;
		       cout<<"\nModify student's name  ";
		       gets(name);
		    }

		    char* retadmno()
		    {
		     return admno;
		     }

		     char* retstbno()
		     {
		      return stbno;
		     }
		     int rettoken()
		     {
		      return token;
		     }
		     void addtoken()
		     {
		      token=1;
		     }
		     void resettoken()
		     {
		       token=0;
		     }
		     void getstbno(char t[])
		     {
			strcpy(stbno,t);
		     }
		     void report()
		     {
		       cout<<"\t"<<admno<<setw(25)<<name<<setw(15)<<token;
		     }


	      };

// Definition of class "library" begins.

class library  {    public:
		    char bno[6];
		    char bname[50],aname[20];

		    void create_book()
		    {  cout<<"\n New book entry";
		       cout<<"\n Enter the book number\t";
		       cin>>bno;
		       cout<<"\n Enter the name of the book\t";
		       gets(bname);
		       cout<<"\n Enter the name of the author\t";
		       gets(aname);
		       cout<<"\n Book created";

		    }

		    void show_book()
		    {  cout<<"\n Book no      : \t"<<bno;
		       cout<<"\n Book name    : \t";
		       puts(bname);
		       cout<<"\n Author's name: \t";
		       puts(aname);
		    }

		    void modify_book()
		    {  cout<<"\n Book no: \t"<<bno;
		       cout<<"\nNew name of book:\t";
		       gets(bname);
		       cout<<"\nNew author name: \t";
		       gets(aname);

		    }

		    char* return_bno()
		    {
		      return bno;
		    }

		    void report()
		    {
		      cout<<bno<<setw(20)<<bname<<setw(20)<<aname<<"\n";
		    }
		 };



//File and class objects have been declared for corresponding files and classes.



fstream fp,fp1;
library bk;
student st;




//Function to create a book.

void write_book()
{
  char ch;
  fp.open("book.dat",ios::app|ios::out|ios::binary);
  do
  {
   clearviewport();
   gotoxy(20,2);
   bk.create_book();
   fp.write((char*)&bk,sizeof(library));
   cout<<"\nDo you want to add more records?? (y/n)   ";
   cin>>ch;
   }while(ch=='y'||ch=='Y');
   fp.close();
}


// Function to create a student.

void write_student()
{  char ch;
   fp.open("student.dat",ios::app|ios::out);
   do
   {  clearviewport();
   gotoxy(20,2);
      st.create_student();
      fp.write((char*)&st,sizeof(student));
      cout<<"\nDo you want to write any more records?? (y/n)    ";
      cin>>ch;
   }while(ch=='y'|| ch=='Y');
fp.close();

}


// Function to display a specific book.


void display_spb(char n[])
{
   cout<<"\nBOOK DETAILS\n";
   int flag=0;
   fp.open("book.dat",ios::in) ;
   while(fp.read((char*)&bk,sizeof(library)))
   {
       if ((strcmpi(bk.return_bno(),n)==0))
       {
	    bk.show_book();
	    flag=1;
       }
   }
   fp.close();
   if (flag==0)
	 cout<<"\n\n Book doesn't exist   ";

 getch();
}


//Function to display specific student.


void display_sps(char n[])
{
   cout<<"\nSTUDENT DETAILS\n";
   int flag=0;
   fp.open("student.dat",ios::in);
   while(fp.read((char*)&st,sizeof(student)))
   {
       if ((strcmpi(st.retadmno(),n)==0))
       {
	    st.show_student();
	    flag=1;
       }
   }
   fp.close();
   if (flag==0)
     cout<<"\n\n Student doesn't exist   ";
   getch();


}

// Function to modify a book record.

void modify_book()
{
  char n[6];
  int found=0;
  clearviewport();
  gotoxy(20,2);
  cout<<" \n\n\t MODIFY BOOK RECORD";
  cout<<"\n\n\t Enter the book number ";
  cin>>n;
  fp.open("book.dat",ios::in|ios::out|ios::binary);
  cout<< "\nEnter the new record  ";
  while(fp.read((char*)&bk,sizeof(library)))
  {
     if(strcmpi(bk.return_bno(),n)==0)
     {
	  bk.modify_book();
	int pos=-1*sizeof(bk);
	fp.seekg(pos,ios::cur);
	fp.write((char*)&bk,sizeof(library));
	cout<<"\n\n Record updated!  ";
	found=1;
     }


  }

 fp.close();

 if(found==0)
       cout<<"\n\n Record not found \n";

 getch();

}

// Function to modify a student record.

void modify_student()
{
     char n[6];
     int found=0;
     clearviewport();
     gotoxy(20,2);
     cout<<"\n\n\t MODIFY STUDENT RECORDS.." ;
     cout<<"\n\n\t Enter the admission no...  ";
     cin>>n;
     fp.open("student.dat",ios::in|ios::out);
     while(fp.read((char*)&st,sizeof(student))&&found==0)

     {
	     if(strcmpi(st.retadmno(),n)==0)
	     {
		 st.show_student();
		 cout<<"\n Enter the new student details   ";
		 st.modify_student();
		 int pos=-1*sizeof(st);
		 fp.seekp(pos,ios::cur);
		 fp.write((char*)&st,sizeof(student));
		 cout<<"\n\n\t Record Updated   ";
		 found=1;
	      }
     }
     fp.close();
     if(found==0)
	cout<<"\n Record not found";
     getch();


}


// Function to delete a student record.

void delete_student()
{

   char n[6];
   int flag=0;
   clearviewport();
   gotoxy(20,2);
   cout<<"\n\n\t DELETE STUDENT RECORDS..  ";
   cout<<"\n\n Enter the admission number  ";
   cin>>n;
   fp.open("student.dat",ios::in|ios::out);
   fstream fp2;
   fp2.open("Temp.dat",ios::out);
   fp.seekp(0,ios::beg);
   while(fp.read((char*)&st,sizeof(student)))
   {
	if(strcmpi(st.retadmno(),n))
	    fp2.write((char*)&st,sizeof(student));

	else
	   flag=1;
   }
   fp2.close();
   fp.close();
   remove("student.dat");
   rename("Temp.dat","student.dat");
   if(flag==1)
     cout<<"\n\n\t Record succesfully deleted ";
   else
     cout<<"\n\n\t Record not found ";

   getch();

}



// Function to delete a book record.

void delete_book()
{
   char n[6];
    clearviewport();
    gotoxy(20,2);
    int flag=0;
   cout<<"\n\n\t DELETE BOOK..  ";
   cout<<"\n\n Enter the book number  ";
   cin>>n;
   fp.open("book.dat",ios::in|ios::out);
   fstream fp2;
   fp2.open("Temp.dat",ios::out);
   fp.seekp(0,ios::beg);
   while(fp.read((char*)&bk,sizeof(library)))
   {
	if(strcmp(bk.return_bno(),n)!=0)
	  {
	   fp2.write((char*)&bk,sizeof(library));
	   }
	   else flag=1;
   }
   fp2.close();
   fp.close();
   remove("book.dat");
  rename("Temp.dat","book.dat");

  if(flag==1)
    cout<<"\n\n\t Book record succesfully deleted   ";

    else{  cout<<"\nRecord not found\n";
       }
   getch();


}


// Function to display all students in the file.


void display_alls()
{
   clearviewport();
   gotoxy(20,2);
   fp.open("student.dat",ios::in);
   if(!fp)
   {
     cout<<"\nERROR! could not open file  ";
     getch();
     return;
   }

   cout<<"\n\n\t STUDENT LISTING\n\n";
   cout<<"_______________________________________________________\n";
   cout<<"Admission number"<<setw(16)<<"Name"<<setw(20)<<"Book Issued\n";
   cout<<"_______________________________________________________\n";
   while(fp.read((char*)&st,sizeof(student)))
     {
	st.report();
	cout<<"\n";
     }
   fp.close();
   getch();

}

// Function to display all books in the file.

void display_allb()
{

   clearviewport();
   gotoxy(20,2);
   fp.open("book.dat",ios::in);
   if(!fp)
   {
     cout<<"\nERROR! could not open file ";
     getch();
     return;
   }

   cout<<"\n\n\t BOOK LISTING\n\n";
   cout<<"_______________________________________________________\n";
   cout<<"Book number"<<setw(13)<<"Book name"<<setw(20)<<"Author\n";
   cout<<"_______________________________________________________\n";
   while(fp.read((char*)&bk,sizeof(library)))
     {
	bk.report();
     }
   fp.close();
   getch();

}

// Function to issue a book to a student.

void book_issue()
{

    char sn[6],bn[6];
    int found=0,flag=0;
    clearviewport();
    gotoxy(20,2);
    cout<<"\n\n\t\t Enter the student number\t";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student))&& found==0)
    {
	if(strcmpi(st.retadmno(),sn)==0)
	{
	     found=1;
	     st.show_student();
	     if(st.rettoken()==0)
	     {
		 cout<<"\n\n\t\t Enter the book number\t\t";
		 cin>>bn;
		 while(fp1.read((char*)&bk,sizeof(library))&& flag==0)
		 {   if(strcmpi(bk.return_bno(),bn)==0)
		     {   bk.show_book();
			 flag=1;
			 st.addtoken();
			 st.getstbno(bk.return_bno());
			 int pos=-1*sizeof(st);
			 fp.seekp(pos,ios::cur);
			 fp.write((char*)&st,sizeof(student));
			 cout<<"\n\n\t Book issued successfully " ;
		      }

		 }
	       if (flag==0)
		  cout<<"\n Book does not exist ";
		}

	  else
	     cout<<"\n You have not returned the previously issued book ";



	}
    }
 if(found==0)
      cout<<"\n Student record does not exist ";
 getch();
 fp.close();
 fp1.close();



}


//Function to return a book that has already been issued.

void book_return()

{

    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clearviewport();
    gotoxy(20,2);
    cout<<"\n\n\t BOOK RETURN";
    cout<<"\n\n\t\t Enter the student number\t";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student))&& found==0)
    {
	if(strcmpi(st.retadmno(),sn)==0)
	{
	     found=1;
	     st.show_student();
	     if(st.rettoken()==1)
	     {
		 cout<<"\n\n\t\t Enter the book number\t\t";
		 cin>>bn;
		 while(fp1.read((char*)&bk,sizeof(library))&& flag==0)
		 {   if(strcmpi(bk.return_bno(),bn)==0)
		     {   bk.show_book();
			 flag=1;
			 cout<<"\n\n\t Book returned in how many days?? \t";
			 cin>>day;
			 cout<<"\n\t  A fine of Rs. 5 per day( after 15 days ) will be charged\t";
			 if(day>15)
			 {
			   fine=(day-15)*5;
			   cout<<"\n\n\t Fine has to be paid to library of the amount\t  Rs."<<fine;

			 }
			 else
			 {
			   cout<<"\nYou do not have to pay any fine";
			 }
			 st.resettoken();
			 int pos=-1*sizeof(st);
			 fp.seekp(pos,ios::cur);
			 fp.write((char*)&st,sizeof(student));
			 cout<<"\n\n\t Book deposited successfully";
		      }

		 }
	       if (flag==0)
		  cout<<"\n Book does not exist";
		}

	  else
	     cout<<"\n You have not been issued a book ";



	}
    }
 if(found==0)
      cout<<"\n Student record does not exist";
 getch();
 fp.close();
 fp1.close();



}

//Introductory function


void introductory()
{
  int gdriver=DETECT,gmode;
  initgraph(&gdriver,&gmode,"..//BGI");


  int x;
  x=(getmaxx()/2)-305;
  setbkcolor(BLACK);
  settextstyle(9,0,4);
  setcolor(GREEN);
  outtextxy(x,100," LIBRARY");
  gotoxy(30,14);
  outtextxy(x+220,100," MANAGEMENT");
  setcolor(GREEN);
  line(0,90,480,90);
  line(150,180,900,180);
  setcolor(GREEN);
  setlinestyle(1,1,4);
  line(312,90,345,180);
  setcolor(RED);
  settextstyle(2,0,7);
  outtextxy(40,290,"\n\n Made by: HARISH GANESAN");
  outtextxy(40,330,"\n\n School: GEAR Innovative Intl School\n ");
  getch();


}


// Function to display the administrator menu.

void admin_menu()
{
   clearviewport();
   char choice;
   cout<<"\t ADMINISTRATOR MENU";
   cout<<"\n\ta.CREATE STUDENT";
   cout<<"\n\n\tb.DISPLAY ALL STUDENTS";
   cout<<"\n\n\tc.DISPLAY SPECIFIC STUDENT";
   cout<<"\n\n\td.MODIFY STUDENT";
   cout<<"\n\n\te.DELETE STUDENT\n";
   cout<<"___________________________________________________________________________";
   cout<<"\n\n\tf.CREATE BOOK";
   cout<<"\n\n\tg.DISPLAY ALL BOOKS";
   cout<<"\n\n\th.DISPLAY SPECIFIC BOOK";
   cout<<"\n\n\ti.MODIFY BOOK";
   cout<<"\n\n\tj.DELETE BOOK";
   cout<<" \n__________________________________________________________________________";

   cout<<"\n\n\tk.BACK TO MAIN MENU";

   cout<<"\n\n\t Please enter your choice (a-k) :\t\t";
   cin>>choice;
   switch(choice)
   {
      case 'a':
      clearviewport();
      gotoxy(20,2);
      write_student();
      break;

      case 'b':
      display_alls();
      break;

      case 'c':
      char num[6];
      clearviewport();
      gotoxy(20,2);
      cout<<"\n\n\t Please enter the admission no. of the student\t\t";
      cin>>num;
      display_sps(num);
      break;

      case 'd':
      modify_student();
      break;

      case 'e':
      delete_student();
      break;

      case 'f':
      clearviewport();
      gotoxy(20,2);
      write_book();
      break;

      case 'g':
      display_allb();
      break;

      case 'h':
      clearviewport();
      gotoxy(20,2);
      cout<<"\n\n\t Please enter the book number\t\t";
      cin>>num;
      display_spb(num);
      break;

      case 'i':
      modify_book();
      break;

      case 'j':
      delete_book();
      break;

      case 'k':
      return;

      default:
      cout<<"\nEnter a valid option\n";
      getch();
      cout<<"\a\a";
   }
   admin_menu();

}

// Main Function

void main()
{
  int z;
  char ch=0;
  introductory();
  delay(1000);
  do{
      clearviewport();
      setbkcolor(BLACK);
      settextstyle(0,0,3);
      setcolor(LIGHTBLUE);
      outtextxy (200,7d0," MAIN MENU");
      settextstyle(0,0,2);
      delay(350);
      outtextxy (200,130," 1. BOOK ISSUE");
      delay(350);
      outtextxy (200,180," 2. BOOK RETURN");
      delay(350);
      outtextxy (200,230," 3. ADMIN MENU");
      delay(350);
      outtextxy (200,280," 4. EXIT");
      delay(350);
      z=(getmaxx()/2)-150;
      outtextxy(z,371,"Enter your choice(1-4)   :");

      gotoxy(50,24);

      cin>>ch;

      switch(ch)
      {

	 case '1':
	 clearviewport();
	 gotoxy(20,2);
	 book_issue();
	 break;


	 case '2':
	 book_return();
	 break;

	 case '3':
	 admin_menu();
	 break;

	 case '4':
	 exit(0);

	 default: outtextxy(z,400,"Enter a valid option");
	 getch();

      }

      }while(ch!=4);

closegraph();

}


// END OF PROJECT.
