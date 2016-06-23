#include<stdio.h>
#include<conio.h>
#include <ctype.h>
#include<stdlib.h>
struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();
int listrecords();
int modifyrecords();
int deleterecords();
int searchrecords();
int payment();
char get;
int main()              //start
{	int password;
	int phonenumber;
	char choice;



	clrscr();  //clear

	printf("\n\n\n\n\n\n\n\n\n*****************************************************************************");
	printf("\n\t\t\tWELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM");
	printf("\n*******************************************************************************");
	//Sleep(2000);
	getch();        //take any input to continue
	clrscr();
	while (1)
	{
		clrscr();
		printf("\n Enter\n A : for adding new records.\n L : for list of records");
		printf("\n M : for modifying records.\n P : for payment");
		printf("\n S : for searching records.");
		printf("\n D : for deleting records.\n E : for exit\n");
		choice=getche();             //choice input
		choice=toupper(choice);      //case converting
		switch(choice)
		{
			case 'P':
				payment();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				modifyrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				deleterecords();break;
			case 'E':
				system("cls");
				printf("\n\n\n\n\t\t\t\tTHANK YOU FOR USING OUR SERVICE");
				getch();
			       //	Sleep(2000);
				exit(0);
				break;
			default:
				getch();
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;  //file pointer to f
	char test;
	f=fopen("c:/file.ojs","ab+");  //open file f file.ojs and enter the data
	if(f==0)
	{   f=fopen("c:/file.ojs","wb+"); //editing file
		system("cls");                          //
		printf("Please wait while we configure your computer\n\nLoading...");   //creating data file in c drive
		printf("/nPress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");                      // user data writing
		printf("\n Enter phone number:");    // ph no is
		scanf("%s",&s.phonenumber);
		printf("\n Enter name:");
		fflush(stdin);                     //file input name
		scanf("%[^\n]",&s.name);
		printf("\n Enter amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
	       //	system("cls");
		printf("\n 1 Record successfully added");
		printf("\n Press 'esc' key to exit \n\tor\n Any other key to add other record:");
		test=getche();
		if(test==27)    // if esc key ie 27th character then exit
			break;
	}
	fclose(f);              //file closed and data written
}
int listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("c:/file.ojs","rb"))==NULL)   //if file empty then check
	{        clrscr();
		printf("!!! NO DATA FOUND !!!\n Press any key to go back to Main Menu");
		  getch();
		return(0);
	}
	clrscr();
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)  //print till last data
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
return(0);
}
int deleterecords()
{
	FILE *f,*t;// t and f file checking for data
	int i=1;     // used i to check if any data found
	char phonenumber[20];
	if((t=fopen("c:/temp.ojs","w+"))==NULL)    //empty check
	{       clrscr();
		printf("!!! NO DATA FOUND !!!\n Press any key to go back to Main Menu");
		getch();
		return(0);
	}
	if((f=fopen("c:/file.ojs","rb"))==NULL)     //empty check
{        clrscr();
		printf("!!! NO DATA FOUND !!!\n Press any key to go back to Main Menu");
		  getch();
		return(0);
	}
	clrscr();
	printf("Enter the phone number to be deleted from the Database");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);    //scanf till enter ie new line = \n
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)  //struct phone no comp
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)// if NO data found then delete the temp file
	{       system("cls");
		printf("Phone number \"%s\" not found",phonenumber);
		remove("c:/file.ojs");
		rename("c:/temp.ojs","c:/file.ojs"); // change the temp fie to main file
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("c:/file.ojs");
	rename("c:/temp.ojs","c:/file.ojs"); //if data found then also change object file name
	getch();
	printf("The Number %s Successfully Deleted!!!!",phonenumber);
	fclose(f);
	fclose(t);
	getch();
return(0);
}
int searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int mark=1; //  use mark for record data checkiing
	f=fopen("c:/file.ojs","rb+");
	if(f==0)
	{        clrscr();
		printf("!!! NO DATA FOUND !!!\n Press any key to go back to Main Menu");
		  getch();
		return(0);
	}
	fflush(stdin);
	system("cls");
	printf("Enter Phone Number to search in our database");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)  // searching no
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			mark=0;
			break;
		}
		else if(mark==1)
		{	system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	getch();
	fclose(f);
return(0);
}
int modifyrecords()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("c:/file.ojs","rb+"))==NULL) //if file empty then go back
	{	printf("!! NO DATA FOUND !!\n\n\nPress any key to return to main menu");
		getch();
		return(0);
	}
	system("cls");
	printf("Enter phone number of the subscriber to modify:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			clrscr();
			printf("\n Enter phone number:");
			scanf("%s",&s.phonenumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
	return(0);
}
int payment()
{
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
	{       clrscr();
		printf("!!! NO DATA FOUND !!!\n Press any key to go back to Main Menu");
		getch();
		return(0);
	}
	clrscr();
	printf("Enter phone number of the subscriber for payment");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.phonenumber,phonenumber)==0)
		{
			system("cls");
			printf("\n Phone No.: %s",s.phonenumber);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;  //changing amount value
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("cls");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getch();
	fclose(f);
return(0);
}
