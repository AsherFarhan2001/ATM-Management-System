//============================================================================
// Name        : Project.cpp
// Author      : Asher Farhan 	(19i-0618)
// Version     :
// Copyright   : 
// Description : Bank ATM in C++, Ansi-style
//============================================================================
#include<iostream>
#include<iomanip>
#include<string>
#include <unistd.h>
#include<fstream>
using namespace std;

int flag = 0;			// Global Variable

class Screen			// Screen Classs

{
	public :
		void displayWelcome();
		void EnterAccountNo();
		void EnterPinNo();
		void AccountVerify();
		void AccountnotVerify();
		void MainMenu();
		void balance();
		void WithdrawMenu();
		void depositamount();
};

void Screen :: displayWelcome()
{
	cout<<"\n================================================================================== "<<endl;
	cout<<"\n----------------------------  WELCOME TO THE ATM ------------------------------- "<<endl;
	cout<<"\n================================================================================== "<<endl;
}
void Screen :: EnterAccountNo()
{
	cout<<"\nPlease Enter Your Account No : "<<endl;
}
void Screen :: EnterPinNo()
{
	cout<<"\nPlease Enter Your PIN No : "<<endl;
}
void Screen :: AccountVerify()
{
	cout<<"\n------------------- Your Account has Been Verified --------------------- "<<endl;
}
void Screen :: AccountnotVerify()
{
	cout<<"\n------------------ Your Account has not Been Verified --------------------"<<endl;
}
void Screen :: MainMenu()
{
	cout<<"\n------------------- Main Menu -------------------- "<<endl;
	cout<<"\n1 - View my Balance "<<"\t\t2 - WithDraw Cash "<<endl;
	cout<<"\n3 - Deposit Cash "<<"\t\t4 - Exit "<<endl;
	cout<<"\nEnter a Choice : "<<endl;
}
void Screen :: balance()
{
	cout<<"\nYour Current Account Balance is = ";
}
void Screen :: WithdrawMenu()
{
	cout<<"\n---------------- WithDrawl Options ------------------- "<<endl;
	cout<<"\n1 - $20 "<<"\t\t2 - $40 "<<endl;
	cout<<"\n3 - $60 "<<"\t\t4 - $100 "<<endl;
	cout<<"\n5 - $200 "<<"\t\t6 - Cancel Transaction "<<endl;
	cout<<"\nChoose a WithDrawl Option (1 - 6) "<<endl;
}
void Screen :: depositamount()
{
	cout<<"\nEnter the Deposit Amount ( In CENTS ) or Press 0 to Cancel the Transaction : "<<endl;
}

class Keypad			// Keypad Class
{
	public :
		string getAccountNo();
		string getPinNo();
		int getMenuOption();
		int getDepositAmount();
		int getWithdrawlOption();
};

string Keypad :: getAccountNo()
{
	string accNo;
	getline(cin,accNo);
	return accNo;
}
string Keypad :: getPinNo()
{
	string pinNo;
	getline(cin,pinNo);
	return pinNo;
}
int Keypad :: getMenuOption()
{
	int meOp;
	cin>>meOp;
	return meOp;
}
int Keypad :: getWithdrawlOption()
{
	int wdop;
	cin>>wdop;
	return wdop;
}
int Keypad :: getDepositAmount()
{
	int deAm;
	cin>>deAm;
	return deAm;
}

class CashDispenser			// Cash Dispenser Class
{
	public :
		void returncash();
		int checkamount(int,int);
};

void CashDispenser :: returncash()
{
	cout<<"\n-------------- The Amount has been WithDrawled Successfully --------------- "<<endl;
	cout<<"\n        !!!!  Dont Forget to Take Your Amount.... Thanks   !!!!!    "<<endl;
}
int CashDispenser :: checkamount(int amount , int bal)
{
	int rem = 0;
	if(amount > bal)
	{
		rem = 1;
	}
	return rem;
}

class DepositSlot				// Deposit Slot Class
{
	public :
		int depositcash(int,double);
};

int DepositSlot :: depositcash(int bal , double amount)
{
	int rem = 0;
	int tem;
	tem = amount / 100;
	rem = bal + tem;
	return rem;
}

class Account		 // Account Class
{
	protected :
		string AccountNo;
		string PinNo;
		double BankBalance;

	public :
		void setAccountNo(string);
		void setPinNo(string);
		void setBankBalance(double);
		string getEnteredAccountNo() ;
		string getEnteredPinNo() ;
		int getEnteredBankBalance() ;
};

//-------------------------- Setter or Mutator Functions --------------------------

void Account :: setAccountNo(string accountNo)
{
	this -> AccountNo = accountNo;
}
void Account :: setPinNo(string pinNo)
{
	this -> PinNo = pinNo;
}
void Account :: setBankBalance(double balance)
{
	this -> BankBalance = balance;
}

// ------------------------- Accessor or Getter Functions -------------------

string Account :: getEnteredAccountNo()
{
	return AccountNo;
}
string Account :: getEnteredPinNo()
{
	return PinNo;
}
int Account :: getEnteredBankBalance()
{
	return BankBalance;
}

///////////////////   Balance Inquiry Class inherited from Account Class  /////////////////////////

class BalanceInquiry : public Account
{
	private:
		Screen scr;				// Composition

	public:
		int InquireBalance();
		void displaybalance();
};
int BalanceInquiry :: InquireBalance()
{
	return BankBalance;
}
void BalanceInquiry :: displaybalance()
{
	scr.balance();
}

///////////////////   WithDrawl Class inherited from Account Class  /////////////////////////

class WithDrawl : public Account
{
	private :
		Screen scr;
		CashDispenser dispense;			// Composition

	public :
		void displaywithdrawl();
		int withdraw(int amount);
		int check(int amo);

};
void WithDrawl :: displaywithdrawl()
{
	scr.WithdrawMenu();
}
int WithDrawl :: withdraw(int amount)
{
	int temp;
	temp = getEnteredBankBalance() - amount;
	return temp;
}
int WithDrawl :: check(int amo)
{
	return dispense.checkamount(amo, getEnteredBankBalance());
}

///////////////////   Deposit Class inherited from Account Class  /////////////////////////

class Deposit : public Account
{
	private :
		DepositSlot Ds;				// Composition
		Screen scr;

	public :
		void displayamount();
		int depositamount(double);
};
void Deposit :: displayamount()
{
	scr.depositamount();
}
int Deposit :: depositamount(double amount)
{
	cout<<"\nYour Amount Has been Deposited Successfully "<<endl;
	return Ds.depositcash(getEnteredBankBalance() , amount);
}

///////////////////   ATM Class inherited from Account Class  /////////////////////////

class ATM : public Account
{
	private:
		Screen scr;
		Keypad key;
		CashDispenser cashdis;
		DepositSlot deposit;

	public:
		int getverifyAccountNo(string []);
		int getverifyPinNo(string []);
		void AccountVerifyMessage();
		void AccountnotVerifyMessage();

};
int ATM :: getverifyAccountNo(string account [4])
{
	flag = 0;
	int temp = 0;
	for(int i=0;i<4;i++)
	{
		if(getEnteredAccountNo() == account[i])
		{
			temp = 1;
			break;
		}
		flag++;
	}
	return temp;
}
int ATM :: getverifyPinNo(string PIN [4])
{
	int temp1 = 0;
	for(int i=0;i<4;i++)
	{
		if(getEnteredPinNo() == PIN[flag])
		{
			temp1 = 1;
			break;
		}
	}
	return temp1;
}
void ATM :: AccountVerifyMessage()
{
	scr.AccountVerify();
}
void ATM :: AccountnotVerifyMessage()
{
	scr.AccountnotVerify();
}

///////////////////////////////////////   DRIVER FUNCTION IMPLEMENTATION   //////////////////////////////////////

int main()
{
	string acc,pin;
	int bal = 100;

	// Account details of user 1
	string useracc1 = "21345";
	string userpin1 = "54312";
	int userbal1 = 9000;

	// Account Details of User 2
	string useracc2 = "73983";
	string userpin2 = "38937";
	int userbal2 = 7000;

	// Account Details of User 3
	string useracc3 = "92807";
	string userpin3 = "70829";
	int userbal3 = 5000;
	string name;
	cout<<"--------------------- Creating New Account --------------------- "<<endl;
	cout<<"\nEnter your Full Name : "<<endl;
	getline(cin,name);
	cout<<"\nEnter the Account No : "<<endl;
	getline(cin,acc);
	cout<<"\nEnter the Pin : "<<endl;
	getline(cin,pin);
	cout<<"\nYour Account has Been Successfully Created "<<endl;
	ofstream ofile,ofile1,ofile2;
	ifstream ifile,ifile1,ifile2;
	ofile.open("Account No.txt");
	ifile.open("Account No.txt");
	ofile1.open("Pin No.txt");
	ifile1.open("Pin No.txt");
	ofile2.open("Account Balance.txt");
	ifile2.open("Account Balance.txt");
	ofile<<acc<<endl;
	ofile<<useracc1<<endl;
	ofile<<useracc2<<endl;
	ofile<<useracc3<<endl;
	ofile1<<pin<<endl;
	ofile1<<userpin1<<endl;
	ofile1<<userpin2<<endl;
	ofile1<<userpin3<<endl;
	ofile2<<bal<<endl;
	ofile2<<userbal1<<endl;
	ofile2<<userbal2<<endl;
	ofile2<<userbal3<<endl;
	Screen S;
	Keypad K;
	Account A;
	ATM atm;
	BalanceInquiry BI;
	WithDrawl Wd;
	CashDispenser Cd;
	Deposit D;
	string account[4],Apin[4];
	int balance[4];
	int Averify;
	int Pverify;
	int opt;
	double accbal;
	int count2 = 0;
	while(! ifile2.eof())			// reading balance from file
	{
			ifile2>>balance[count2];
			count2++;
	}
	do
	{
		S.displayWelcome();
		S.EnterAccountNo();
		string accNo = K.getAccountNo();
		atm.setAccountNo(accNo);
		S.EnterPinNo();
		string PinNo = K.getPinNo();
		atm.setPinNo(PinNo);
		int count = 0,count1 = 0;
		while(! ifile.eof())					// reading account no from file
		{
			ifile>>account[count];
			count++;
		}
		while(! ifile1.eof())				// reading pin no from file
		{
			ifile1>>Apin[count1];
			count1++;
		}
		Averify = atm.getverifyAccountNo(account);
		Pverify = atm.getverifyPinNo(Apin);
		if(Averify == 1 && Pverify == 1)
		{
			accbal = balance[flag];
			atm.setBankBalance(accbal);
			atm.AccountVerifyMessage();
			S.MainMenu();
			opt = K.getMenuOption();
			while(opt == 1 || opt == 2 || opt == 3)			// Loop for Processing Main Menu
			{
				accbal = balance[flag];
				if(opt == 1)
				{
					BI.setBankBalance(accbal);
					BI.displaybalance();
					cout<<BI.InquireBalance()<<endl;
				}
				if(opt == 2)
				{
					int temp;
					do						// Loop for Processing WithDrawl Menu
					{
						int opt1;
						Wd.displaywithdrawl();
						opt1 = K.getWithdrawlOption();
						if(opt1 == 1)
						{
							int amo;
							int res;
							Wd.setBankBalance(accbal);
							amo = 20;
							temp = Wd.check(amo);
							if(temp == 1)
							{
								cout<<"\nERROR... The Withdrawl Amount is Greater than the Bank Balance "<<endl;
							}
							else if(temp == 0)
							{
								res = Wd.withdraw(amo);
								Cd.returncash();
								balance[flag] = res;
							}

						}
						else if(opt1 == 2)
						{
							int amo;
							int res;
							Wd.setBankBalance(accbal);
							amo = 40;
							temp = Wd.check(amo);
							if(temp == 1)
							{
								cout<<"\nERROR... The Withdrawl Amount is Greater than the Bank Balance "<<endl;
							}
							else if(temp == 0)
							{
								res = Wd.withdraw(amo);
								Cd.returncash();
								balance[flag] = res;
							}
						}
						else if(opt1 == 3)
						{
							int amo;
							int res;
							Wd.setBankBalance(accbal);
							amo = 60;
							temp = Wd.check(amo);
							if(temp == 1)
							{
								cout<<"\nERROR... The Withdrawl Amount is Greater than the Bank Balance "<<endl;
							}
							else if(temp == 0)
							{
								res = Wd.withdraw(amo);
								Cd.returncash();
								balance[flag] = res;
							}
						}
						else if(opt1 == 4)
						{
							int amo;
							int res;
							Wd.setBankBalance(accbal);
							amo = 100;
							temp = Wd.check(amo);
							if(temp == 1)
							{
								cout<<"\nERROR... The Withdrawl Amount is Greater than the Bank Balance "<<endl;
							}
							else if(temp == 0)
							{
								res = Wd.withdraw(amo);
								Cd.returncash();
								balance[flag] = res;
							}
						}
						else if(opt1 == 5)
						{
							int amo;
							int res;
							Wd.setBankBalance(accbal);
							amo = 200;
							temp = Wd.check(amo);
							if(temp == 1)
							{
								cout<<"\nERROR... The Withdrawl Amount is Greater than the Bank Balance "<<endl;
							}
							else if(temp == 0)
							{
								res = Wd.withdraw(amo);
								Cd.returncash();
								balance[flag] = res;
							}
						}
						else if(opt1 == 6)
						{
							temp = 0;
							cout<<"\n------- Your Transaction has been Cancelled --------- "<<endl;
						}

					}	while(temp == 1);

				}
				else if(opt == 3)
				{
					double a;
					int b;
					D.setBankBalance(accbal);
					D.displayamount();
					a = K.getDepositAmount();
					if(a == 0)
					{
						cout<<"\n---------- The Transaction Has Been Cancelled ------------ "<<endl;
					}
					if(a != 0)
					{
						cout<<"\nEntering the Deposit Envelope in the Deposit Slot "<<endl;
						sleep(2);
						b = D.depositamount(a);
						balance[flag] = b;
					}
				}
				S.MainMenu();
				opt = K.getMenuOption();
			}
			cout<<"\n!!! ------------------  Updating the Bank Data Base --------------------  !!! "<<endl;
			cout<<"\n ------------------------- THANK YOU ------------------------------- "<<endl;
			ofile2<<"\nThe Updated Accounts Balance are : "<<endl;

			for(int i=0;i<4;i++)										// Writing the Updated Accounts Balance in File
			{
				ofile2<<balance[i]<<endl;
			}
			cin.ignore();
		}
		else
		{
			atm.AccountnotVerifyMessage();
		}

	} while(Averify == 0 || Pverify == 0 || opt == 4);

	ofile.close();
	ofile1.close();
	ofile2.close();
	ifile.close();
	ifile1.close();
	ifile2.close();

	return 0;
}
