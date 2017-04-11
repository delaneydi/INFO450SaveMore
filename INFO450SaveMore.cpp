// INFO450SaveMore.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

class bankAccount
{
protected:
	unsigned int accountNumber;
	static unsigned int accountGenerator;
	tm creation;
	float interestRate;
	float accountBalance;

public:
	virtual float monthlyInterest() = 0;
	virtual float orderChecks() = 0;

	bankAccount()
	{
		accountNumber = getAccountNumber();
		creation;
		interestRate = 0;
		accountBalance = 0;
	}

	bankAccount(int a, float i, float b)
	{
		accountNumber = a;
		interestRate = i;
		accountBalance = b;
	}

	void setAccountNumber(unsigned int n)
	{
	accountNumber = n;
	}

	int getAccountNumber()
	{
		accountNumber = accountGenerator;
		accountGenerator++;
	}

	void setInterestRate(float r)
	{
		interestRate = r;
	}

	virtual float getInterestRate()
	{
		return interestRate;
	}

	void setAccountBalance(float b)
	{
		accountBalance = b;
	}

	float getAccountBalance()
	{
		return accountBalance;
	}

	virtual bool withdraw(float b)
	{
		if (accountBalance < b)
			return -1;
		accountBalance = accountBalance - b;
		return 0;
	}

	virtual bool deposit(float d)
	{
		if (d < 0)
			return -1;
		accountBalance = accountBalance + d;
		return 0;
	}

	virtual void display()
	{
		cout << "Account Number:" << accountNumber << endl;
		cout << "Interest Rate:" << interestRate << endl;
		cout << "Balance:" << accountBalance << endl;
	}
};

unsigned int bankAccount::accountGenerator = 1;

class Savings :public bankAccount
{
public:
	Savings(int a, float i, float b) : bankAccount(a, i, b)
	{

	}
	float orderChecks()
	{
		return 0;
	}

	void setInterestRate()
	{
		float bal = getAccountBalance();
		if (bal < 10000)
		{
			bankAccount::setInterestRate(1);
		}
		else
		{
			bankAccount::setInterestRate(2);
		}
	}

	void setAccountBalance(float b)
	{
		bankAccount::setAccountBalance(b);
	}

	bool withdraw(float b)
	{
		bool  c = bankAccount::withdraw(b);
		b = bankAccount::withdraw(2);
		return b;
	}

	bool deposit(float d)
	{
		bool c = bankAccount::deposit(d);
		return d;
	}

	float monthlyInterest()
	{
		if (accountBalance < 10000)
		{
			interestRate = (1 + .01 / 12);
			accountBalance = accountBalance * interestRate;
			return interestRate;
		}
		if (accountBalance >= 10000)
		{
			interestRate = (1 + .02 / 12);
			accountBalance = accountBalance * interestRate;
			return interestRate;
		};
	}
};

class Checking :public bankAccount
{
public:
	Checking(int a, float i, float b) : bankAccount(a, i, b)
	{

	}

	void setAccountBalance(float b)
	{
		bankAccount::setAccountBalance(b);
	}

	void setInterestRate()
	{
		bankAccount::setInterestRate(0);
	}

	bool withdraw(float b)
	{
		if (bankAccount::withdraw(b))
		{
			if (getAccountBalance() < b)
				return bankAccount::withdraw(b);
		}
		return -1;
	}
	bool deposit(float d)
	{
		bool c = bankAccount::deposit(d);
		return d;
	}
	float orderChecks()
	{
		accountBalance = accountBalance - 15;
		return accountBalance;
	}
	float monthlyInterest()
	{
		return interestRate;
	}
};

class CD :public bankAccount
{
	int duration;
public:
	CD(int a, float i, float b, int t) :bankAccount(a, i, b)
	{
		duration = t;
		update();
	}

	float orderChecks()
	{
		return 0;
	}

	void update()
	{
		if (duration < 5)
		{
			bankAccount::setInterestRate(5);
		}
		else
		{
			bankAccount::setInterestRate(10);
		}
	}

	bool withdraw(float b)
	{

		float w = 10 * getAccountBalance() / 100;
		bankAccount::withdraw(w);
		return bankAccount::withdraw(b);
	}

	bool deposit(float d)
	{
		bool c = bankAccount::deposit(d);
		return d;
	}

	float getAccountBalance()
	{ 
		return accountBalance;
	}

	float monthlyInterest()
	{
		return 0;
	}
};

int main()
{
	bankAccount *ptr1;     
	bankAccount *ptr2;
	bankAccount *ptr3;

	ptr1 = new Savings(100, 0, 0);
	ptr2 = new CD(101, 0, 0, 3);
	ptr3 = new Checking(102, 0, 0);

	//create and deposit each account
	ptr1->deposit(10000);
	ptr2->deposit(600);
	ptr3->deposit(10000);
	cout << "Display Savings Account: " << endl;
	ptr1->display();
	cout << "Display Checking Account: " << endl;
	ptr2->display();
	cout << "Display CD Account: " << endl;
	ptr3->display();

	//monthly interest for savings and CD
	cout << "\n\n--------\n";
	cout << "Savings Interest: " << endl;
	ptr1->monthlyInterest();
	ptr3->monthlyInterest();
	ptr1->display();
	cout << "CD interest" << endl;
	ptr3->display();

	//order checks
	cout << "\n\n--------\n";
	cout << "Order Checks: " << endl;
	ptr2->orderChecks();
	ptr2->display();

	//withdraw Savings and Checking accounts
	cout << "\n\n--------\n";
	cout << "Checkings withdrawal" << endl;
	ptr2->withdraw(200);
	ptr1->withdraw(1000);
	ptr2->display();
	cout << "Savings Withdrawal:" << endl;
	ptr1->display();

	//early withdraw of CD
	cout << "\n" << endl;
	cout << "Withdraw CD:" << endl;
	ptr3->withdraw(2000);
	ptr3->display();
	cout << "\n" << endl;

	return 0;
}

