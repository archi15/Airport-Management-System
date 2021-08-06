#include<conio.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<unistd.h>
#include<time.h>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

const char l_destination[5][20]={"DELHI","MUMBAI","GOA","KOLKATA","CHENNAI"};	//local Destination
const char i_destination[11][20]={"LONDON","BERLIN","DUBAI","SINGAPORE","BEIJING","PARIS","SRILANKA","TOKYO","WASHINGTON","HAWAII","NEPAL" }; //International Destination
int lpayment(char origin[30], char destination[30]);
int ipayment(char origin[30], char destination[30]);

class passenger
	{
		private:
			const int bseats;
			const int eseats;
		protected:
			string firstname,lastname, phone, mealtype, passport, Address;
			int bus, eco, datedep, payment;
			char origin[30];
			char destination[30];
		public:		
			passenger(string f_name, string l_name, string phone_no, string add="N/A", string pass_no="N/A", int dd=000000): bseats(50), eseats(250)
				{
					datedep=dd;
					firstname=f_name;
					lastname=l_name;
					Address=add;
					phone=phone_no;
					passport=pass_no;
					bus = bseats;
					eco = eseats;
				}
			virtual bool ldest()=0;
			virtual bool idest(string pass)=0;
			virtual void seats()=0;
			virtual void Meals()=0;
			virtual void Registration()=0;
			virtual bool display()=0;    
	};

class booking:public passenger
	{
		protected:
			int i,j,n,m,k,NoOfSeats,choice;
		public:
			
			booking(string f,string l,string num,string add,string pass,int dd):passenger(f,l,add,num,pass,dd)
				{
					n=0;
					m=0;
				}
		
		bool ldest()
			{
				
				cout<<endl<<"These are the local destinations available: \n";
				for(i=0;i<5;i++)
					{
						for(j=0;j<20;j++)
							{
								cout<<l_destination[i][j];
							}
						cout<<"\n";
					}
		
				again:
				cout<<endl<<"Enter your origin: "; 
				cin>>origin;
				cout<<endl<<"Enter your destination: "; 
				cin>>destination;
				if(strcmpi(origin,destination)==0)
					{
						cout<<"Invalid Origin and Destination Enter again\n";
						goto again;
					}
				else
					{
						for(i=0;i<5;i++)
							{
								if(strcmpi(l_destination[i],origin)==0)
									n++;
							}
						for(j=0;j<5;j++)
							{
								if(strcmpi(l_destination[j],destination)==0) 
									m++;
							}
						if(m==1&&n==1)
							{
								payment = lpayment(origin, destination);
								cout<<endl<<"Price: "<<payment<<" INR/seat"<<endl;
								return true;
							}
						else 
							return false;
						
					}
			}
	
		bool idest(string pass)
			{
				passport = pass;
				cout<<endl<<"These are the international destinations available: \n";
				for(i=0;i<11;i++)
					{
						for(j=0;j<20;j++)
							{
								cout<<i_destination[i][j];
							}
						cout<<"\n";
					}
				again:
				cout<<endl<<"Enter your origin: "; 
				cin>>origin;
				cout<<endl<<"Enter your destination: ";
				cin>>destination;
				if(strcmpi(origin,destination)==0)
					{
						cout<<"Invalid Origin and Destination Enter again\n";
						goto again;
					}
				else
				{
					for(i=0;i<11;i++)
					{
						if(strcmpi(i_destination[i],origin)==0) 
							n++;
					}
					for(j=0;j<11;j++)
					{
						if(strcmpi(i_destination[j],destination)==0)
							m++;
					}
					if(m==1&&n==1)
					{
						payment = ipayment(origin, destination); 
						cout<<endl<<"Price: "<<payment<<" INR/seat"<<endl;
						return true;
					}
					else 
						return false;
				}
			}

		void seats()
			{
				bus_eco:
					if(bus>0||eco>0)
					{
						cout<<endl<<"1.Business Class\n2.Economy Class\n";
						cin>>k;
						switch(k)
						{
							case 1: 
							{
								cout<<endl<<"Business Class";
								cout<<endl<<"Enter the number of seats: ";
								cin>>NoOfSeats;
								payment=(payment*NoOfSeats)+5000;
								if(NoOfSeats<=bus)
								{
									cout<<endl<<"Seats are available.\n\n";
									bus=bus-NoOfSeats;
								}
								else
								{
									cout<<endl<<"Seats are not available.\n\n";
									cout<<"we have only "<<bus<<" seats available.\n"<<endl;
									cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
									cin>>k;
									if(k==1)
									{
										NoOfSeats = bus;
										payment=(payment*NoOfSeats)+5000;
									 	cout<<"Seats are booked\n\n";
									 	bus=0;
									}
									else
									{
										cout<<endl<<"Thank You!.\n";
										exit(0);
									}
								}
								break;
							}
							
						case 2:
							{
								cout<<endl<<"Economy Class";
								cout<<endl<<"Enter the number of seats: ";
								cin>>NoOfSeats;
								payment=(payment*NoOfSeats);
								if(NoOfSeats<=eco)
								{
									cout<<endl<<"Seats are available.\n\n";
									eco=eco-NoOfSeats;
								}
								else
								{
									cout<<endl<<"Seats are not available.\n\n";
									cout<<"we have only "<<eco<<" seats available.\n"<<endl;
									cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
									cin>>k;
									if(k==1)
									{
										NoOfSeats = eco;
										payment=(payment*NoOfSeats);
										cout<<endl<<"Seats are booked\n\n";
										eco=0;
									}
									else
									{
										cout<<endl<<"Thank You!.\n";
										exit(0);
									}
								}
								break;
							}
						
						default:
							{
								cout<<"Error!\n";
								goto bus_eco;
							}
					}
				}
				else
				{
					cout<<endl<<"Sorry no seats available\nHave a nice day!";
					exit(0);
				}
			}
	
		void Meals()
			{
				meal:
				int n;
				cout<<endl<<"Available meal types:\n1.Vegetarian\n2.Non-Vegetarian\n";
				cin>>n;
				if(n==1)
					mealtype="Vegetarian";
				else if(n==2)
					mealtype="Non Vegetarian";
				else
				{
					cout<<"ERROR!!!"<<endl;
					goto meal;
				}
			}

		void Registration()
			{
				int tkt;
				srand (time(NULL));  
				tkt = rand()%1000;
				if(k==1)
				{
					ofstream outfile;
					outfile.open("flight.txt");
					outfile<<"|TICKET INFORMATION:"<<endl<<endl
					<<"Name: "<<firstname<<" "<<lastname<<endl
					<<"Phone: "<<Address<<endl
					<<"Address: "<<phone<<endl
					<<"Passport Number: "<<passport<<endl
					<<"Origin: "<<origin
					<<endl<<"Destination: "<<destination
					<<endl<<"Food: "<<mealtype
					<<endl<<"Number of Seats: "<<NoOfSeats
					<<endl<<"Class: Business"
					<<endl<<"Date of departure: "<<datedep
					<<endl<<"Time: 4.00 PM"
					<<endl<<"Ticket: HF"<<tkt
					<<endl<<"Bill(in Indian rupees): "<<payment<<"/-"<<endl;				
					outfile.close();
				}
				else if(k==2)
				{
					ofstream outfile;
					outfile.open("flight.txt");
					outfile<<"|TICKET INFORMATION:"<<endl<<endl
					<<"Name: "<<firstname<<" "<<lastname<<endl
					<<"Phone: "<<Address<<endl
					<<"Address: "<<phone<<endl
					<<"Passport Number: "<<passport<<endl
					<<"Origin: "<<origin
					<<endl<<"Destination: "<<destination
					<<endl<<"Food: "<<mealtype
					<<endl<<"Number of Seats: "<<NoOfSeats
					<<endl<<"Class: Economy"
					<<endl<<"Date of departure: "<<datedep
					<<endl<<"Time: 4.00 PM"
					<<endl<<"Ticket: HF"<<tkt
					<<endl<<"Bill(in Indian rupees): "<<payment<<"/-"<<endl;
					outfile.close();
				}
			}
		
		bool display()
			{
				bool ans;
				system("cls");
				string temp;
				ifstream infile;
				infile.open("flight.txt");
				while(!infile.eof())
				{
					getline(infile,temp);
					cout<<temp<<endl;
				}
				ans = confirm();
				return ans;
			}
		
		bool confirm()
			{
				char ch;
				confirm:
				cout<<endl<<endl<<"Do you wish to confirm your ticket?(y/n): ";
				ch=getch();
				if(ch=='Y'||ch=='y')
				{
					cout<<endl<<endl<<"|STATUS CONFIRMED";
					ofstream outfile;
					outfile.open("flight.txt",ios::app);
					outfile<<endl<<"|STATUS CONFIRMED";
					outfile.close();
					return true;
				}
				else if(ch=='N'||ch=='n')
				{
					ofstream outfile;
					outfile.open("flight.txt",ios::app);
					outfile<<endl<<"|BOOKING CANCELLED";
					cout<<endl<<endl<<"|BOOKING CANCELLED"
					<<endl<<"Going back to main page";
					outfile.close();
					return false;
				}
				else
				{
					cout<<endl<<"ERROR!!!";
					goto confirm;
				}
			}
	};

class Manage
	{
		private:
			string temp,y,c2;
			int option;
		public:
			int change()
			{	
				int i=0;
				
				ifstream file("flight.txt");
				if(file.is_open())
				{
				cout<<endl<<"Enter your Ticket Number or Press 0 to exit\nTicket Number: ";
				cin>>temp;
				if(temp=="0")
					return 1;
				string v("Ticket: "+temp);
	
				while(!file.eof())
				{
					getline(file,y);
					if(y==v)
					{
						file.seekg(0,ios::beg);
						while(!file.eof())
						{
							getline(file,temp);
							cout<<temp<<endl;
						}
						cout<<endl<<endl<<"1.Change date\n2.Cancel the flight\n3.Go Back\n";
						cin>>option;
						switch(option)
						{
							case 1:
							{
								file.seekg(0,ios::beg);
								ofstream ofile("temp.txt");
								cout<<endl<<"Enter the new date of departure(DDMMYYYY): ";
								cin>>c2;
								string c1("Date of departure: "+c2);
								while(!file.eof())
								{
									getline(file,y);
									if(i==11)
									{
										i++;
										ofile<<c1<<endl;
									}
									else
									{
										i++;
										ofile<<y<<endl;
									}
								}
								file.close();
								ofile.close();
								ofstream outfile;
								outfile.open("flight.txt");
								ifstream readfile("temp.txt");
								while(!readfile.eof())
								{
									getline(readfile,y);
									outfile<<y<<endl;
								}
								outfile.close();
								readfile.close();
								remove("temp.txt");
								cout<<endl<<"Date Changed!";
								sleep(3);
								return 1;
								break;
							}
						
							case 2:
							{
								file.close();
								ofstream ofli;
								ofli.open("flight.txt",ios::trunc);
								ofli.close();
								remove("flight.txt");
								system("cls");
								cout<<endl<<"Booking cancelled!\n\n";
								sleep(3);
								return 1;
								break;
							}
							case 3:
								system("cls");
								return 1;
						}
					}
				}
			}
			else if(!file.is_open())
			{
				cout<<endl<<endl<<"unable to find any record"<<endl;
				cout<<endl<<"going back to main page\n\n";
				file.close();
				return 1;
			}
		}
	};

class complain
	{
		private:
			string f_name, l_name, p_num;
			int choice;
			string sentence;
			string types;
			char ch;
		public:
			complain(string f,string l,string num)
			{
				f_name = f;
				l_name = l;
				p_num = num;
			}
			
			void type()
			{
				back:
				cout<<endl<<endl<<"Enter the type of complain you want to register:\n1.Airport Handling\n2.Baggage Delivery\n3.Booking and ticketing\n4.Other\n";
				cin>>choice;
				cin.ignore();
				cout<<"Enter your complain:\n";
				if(choice==1)
				{
					cout<<"Airport Handling: ";
					types = "Airport Handling: ";
				}
				else if(choice==2)
				{
					cout<<"Baggage Delivery: ";
					types = "Baggage Delivery: ";
				}
				else if(choice==3)
				{
					cout<<"Booking and Ticketing: ";
					types = "Booking and Ticketing: ";
				}
				else if(choice==4)
				{
					cout<<"Other: ";
					types = "Other: ";
				}
				getline(cin,sentence);
				cout<<endl<<"Do you want to edit your complain(y/n): ";
				cin>>ch;
				if(ch=='Y'||ch=='y')
					goto back;
				else
				{
					cout<<endl<<"Complain noted!\n";
					ofstream outfile;
					outfile.open("complain.txt");
					outfile<<"Name: "<<f_name<<" "<<l_name<<endl
					<<"Phone: "<<p_num<<endl
					<<"Complain:\n"<<types<<sentence;
					outfile.close();	
				}
			}
	};

class routes
	{
		public:
			bool print()
			{
				int i,j;
				char ch;
				cout<<"\n\n\n\n\tFollowing are the international flights available"<<endl;
				for(i=0;i<11;i++)
				{
					cout<<endl;
					for(j=0;j<11;j++)
					{
						if(i==j)
						{
							continue;
						}
						else
						{
							cout<<"Flight from "<<i_destination[i]<<" to "<<i_destination[j]<<endl;
						}
						
					}
				}
				cout<<"\n\n\n\n\tFollowing are the local flights available"<<endl;
				for(i=0;i<5;i++)
				{
					cout<<endl;
					for(j=0;j<5;j++)
					{
							if(i==j)
						{
							continue;
						}
						else
						{
							cout<<"Flight from "<<l_destination[i]<<" to "<<l_destination[j]<<endl;
						}
					}
				}
				cout<<endl<<"Do you want to book a flight(y/n) ";
				cin>>ch;
				if(ch=='Y'||ch=='y')
				{
					cout<<endl<<endl;
					return true;
				}
				else
					return false;
			}
			
	};
	
int main()
	{	
		cout<<"\n\t\t\t\t\tAIRPORT MANAGEMENT SYSTEM";
		cout<<"\nPress Enter to continue: ";
		getch();
	
		cout<<endl<<"\n\n\n\tWELCOME!!"<<endl;
		string f_name, l_name, add, pass_no,phone_no;
		int choice, datedep;
		bool ans;
		char ch;
	
		back2:
		cout<<endl<<"Press 1 for Booking"
		<<endl<<"Press 2 for Routes"
		<<endl<<"Press 3 for Complaint"
		<<endl<<"Press 4 for Manage"
		<<endl<<"Press 0 for Exit\n";
		cin>>choice;
		system("cls");
		switch(choice)
		{
			case 1:
				{
					my:
					cout<<"----------------------------BOOKING----------------------------\n";
					passenger *ptr;
					cout<<"Enter Your First Name: ";
					cin>>f_name;
					cin.ignore();
					cout<<"Enter Your Last Name: ";
					getline(cin,l_name);
					cout<<"Enter Your Address(Using Commas Only): ";
					getline(cin,add);
					cout<<"Enter Your Phone Number: ";
					cin>>phone_no;
					cout<<"Enter date of departure(DDMMYYYY): ";
					cin>>datedep;
					
					booking obj1(f_name,l_name,phone_no,add,pass_no,datedep);
					ptr = &obj1;
					
					back:
						
					cout<<endl<<"1.Local Destination\n2.International Destination\n3.Back\n4.Exit\n";
					cin>>choice;
					
					if(choice==1)
					{
						
						if(ptr->ldest()==false)
						{
							cout<<endl<<"We do not fly to this place\nPlease Choose again\n";
							goto back;
						}
						else
						{
							cout<<endl<<"Flight Available\n";
							ptr->seats();
							ptr->Meals();
							ptr->Registration();
							system("cls");
							ans = ptr->display();
							if(ans==false)
							{
								system("cls");
								goto back2;
							}
							else if(ans==true)
							{
								cout<<endl<<"Thanks for Flying With Us"<<endl;
								system("cls");
								goto back2;
							}
						}
					}
					else if(choice==2)
					{
						cout<<endl<<"Enter Your Passport Number: ";
						cin>>pass_no;
						ans = ptr->idest(pass_no);
						if(ans==false)
						{
							cout<<endl<<"We do not fly to this place\n";
							goto back;
						}
						else
						{
							cout<<endl<<"Flight Available\n";
							ptr->seats();
							ptr->Meals();
							ptr->Registration();
							system("cls");
							ans = ptr->display();
							if(ans==false)
							{
								system("cls");
								goto back2;
							}
							else if(ans==true)
							{
								cout<<endl<<"Thanks for Flying With Us"<<endl;
								system("cls");
								goto back2;
							}
						}
					}
					else if(choice==3)
					{
						system("cls");
						goto back2;
					}
					else
						exit(0);
					break;	
				}
				
				case 2:	
					{
						cout<<"----------------------------ROUTES----------------------------\n";
						routes obj;
						ans = obj.print();
						if(ans==true)
							goto my;
						else if(ans==false)
						{
							cout<<endl;
							system("cls");
							goto back2;
						}
						break;
					}
					
				case 3:	
					{
						cout<<"----------------------------COMPLAINT----------------------------\n";
						cout<<"Enter Your First Name: ";
						cin>>f_name;
						cin.ignore();
						cout<<"Enter Your Last Name: ";
						getline(cin,l_name);
						cout<<"Enter Your Phone Number: ";
						cin>>phone_no;
						complain obj(f_name,l_name,phone_no);
						obj.type();
						system("cls");
						goto back2;
						break;
					}
					
				case 4:
					{
						cout<<"----------------------------MANAGE----------------------------\n";
						Manage pass;
						chnge:
						choice= pass.change();
						if (choice==1)
						{
							system("cls");
							goto back2;
						}
						else
						{
							cout<<"No record found\n";
							goto chnge;
						}
							
						break;
					}
					
				case 0:	
					{
						exit(0);
					}
					
				default:
					cout<<endl<<endl<<"ERROR!!!";
					goto back2;
		}
	        return 0;
	}
	
int lpayment(char origin[30], char destination[30])
{
	int payment;
	if((strcmpi(origin,"DELHI")==0)||(strcmpi(origin,"GOA")==0)&&(strcmpi(destination,"DELHI")==0)||(strcmpi(destination,"GOA")==0))
		return payment=8000;
	else if((strcmpi(origin,"DELHI")==0)||(strcmpi(origin,"MUMBAI")==0)&&(strcmpi(destination,"DELHI")==0)||(strcmpi(destination,"MUMBAI")==0))
		return payment=4000;
	else if((strcmpi(origin,"DELHI")==0)||(strcmpi(origin,"KOLKATA")==0)&&(strcmpi(destination,"DELHI")==0)||(strcmpi(destination,"KOLKATA")==0))
		return payment=10000;
	else if((strcmpi(origin,"DELHI")==0)||(strcmpi(origin,"CHENNAI")==0)&&(strcmpi(destination,"DELHI")==0)||(strcmpi(destination,"CHENNAI")==0))
		return payment=5000;
	else if((strcmpi(origin,"GOA")==0)||(strcmpi(origin,"MUMBAI")==0)&&(strcmpi(destination,"GOA")==0)||(strcmpi(destination,"MUMBAI")==0))
		return payment=3000;
	else if((strcmpi(origin,"GOA")==0)||(strcmpi(origin,"KOLKATA")==0)&&(strcmpi(destination,"GOA")==0)||(strcmpi(destination,"KOLKATA")==0))
		return payment=6000;
	else if((strcmpi(origin,"GOA")==0)||(strcmpi(origin,"CHENNAI")==0)&&(strcmpi(destination,"GOA")==0)||(strcmpi(destination,"CHENNAI")==0))
		return payment=9000;
	else if((strcmpi(origin,"MUMBAI")==0)||(strcmpi(origin,"KOLKATA")==0)&&(strcmpi(destination,"MUMBAI")==0)||(strcmpi(destination,"KOLKATA")==0))
		return payment=7000;
	else if((strcmpi(origin,"MUMBAI")==0)||(strcmpi(origin,"CHENNAI")==0)&&(strcmpi(destination,"MUMBAI")==0)||(strcmpi(destination,"CHENNAI")==0))
		return payment=2000;
}

int ipayment(char origin[30], char destination[30])
{
	int payment;
	if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"BERLIN")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"BERLIN")==0))
		        return payment=30000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"DUBAI")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"DUBAI")==0))
		        return payment=20000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"SINGAPORE")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"SINGAPORE")==0))
		        return payment=40000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"BEIJING")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"BEIJING")==0))
		        return payment=70000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"PARIS")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"PARIS")==0))
		        return payment=10000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=100000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=40000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=40000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=40000;
	else if((strcmpi(origin,"LONDON")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"LONDON")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=20000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"DUBAI")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"DUBAI")==0))
		        return payment=35000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"SINGAPORE")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"SINGAPORE")==0))
		        return payment=70000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"BEIJING")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"BEIJING")==0))
		        return payment=60000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"PARIS")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"PARIS")==0))
		        return payment=12000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=150000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=65000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=150000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=35000;
	else if((strcmpi(origin,"BERLIN")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"BERLIN")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=30000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"SINGAPORE")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"SINGAPORE")==0))
		        return payment=15000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"BEIJING")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"BEIJING")==0))
		        return payment=4000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"PARIS")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"PARIS")==0))
		        return payment=20000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=60000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=60000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=20000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=15000;
	else if((strcmpi(origin,"DUBAI")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"DUBAI")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=15000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"BEIJING")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"BEIJING")==0))
		        return payment=90000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"PARIS")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"PARIS")==0))
		        return payment=50000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=150000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=110000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=85000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=5000;
	else if((strcmpi(origin,"SINGAPORE")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"SINGAPORE")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=40000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"PARIS")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"PARIS")==0))
		        return payment=30000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=85000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=30000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=80000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=45000;
	else if((strcmpi(origin,"BEIJING")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"BEIJING")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=70000;
	else if((strcmpi(origin,"PARIS")==0)||(strcmpi(origin,"SRILANKA")==0)&&(strcmpi(destination,"PARIS")==0)||(strcmpi(destination,"SRILANKA")==0))
		        return payment=150000;
	else if((strcmpi(origin,"PARIS")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"PARIS")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=40000;
	else if((strcmpi(origin,"PARIS")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"PARIS")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=55000;
	else if((strcmpi(origin,"PARIS")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"PARIS")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=35000;
	else if((strcmpi(origin,"PARIS")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"PARIS")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=65000;
	else if((strcmpi(origin,"SRILANKA")==0)||(strcmpi(origin,"TOKYO")==0)&&(strcmpi(destination,"SRILANKA")==0)||(strcmpi(destination,"TOKYO")==0))
		        return payment=90000;
	else if((strcmpi(origin,"SRILANKA")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"SRILANKA")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=150000;
	else if((strcmpi(origin,"SRILANKA")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"SRILANKA")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=120000;
	else if((strcmpi(origin,"SRILANKA")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"SRILANKA")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=150000;
	else if((strcmpi(origin,"TOKYO")==0)||(strcmpi(origin,"WASHINGTON")==0)&&(strcmpi(destination,"TOKYO")==0)||(strcmpi(destination,"WASHINGTON")==0))
		        return payment=75000;
	else if((strcmpi(origin,"TOKYO")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"TOKYO")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=30000;
	else if((strcmpi(origin,"TOKYO")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"TOKYO")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=120000;
	else if((strcmpi(origin,"WASHINGTON")==0)||(strcmpi(origin,"HAWAII")==0)&&(strcmpi(destination,"WASHINGTON")==0)||(strcmpi(destination,"HAWAII")==0))
		        return payment=65000;
	else if((strcmpi(origin,"WASHINGTON")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"WASHINGTON")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=100000;
	else if((strcmpi(origin,"HAWAII")==0)||(strcmpi(origin,"NEPAL")==0)&&(strcmpi(destination,"HAWAII")==0)||(strcmpi(destination,"NEPAL")==0))
		        return payment=40000;
}

