/*
Name: Tatum Morris
Date: 11/26/23
Assignment: Extra Credit Lab 3
*/

#include <iostream>
#include <iomanip>

class Account {     //This section of code contains the base class for the Account which contains various features 
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:     //These contains the properties and then gives the strings for the given information  
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    virtual ~Account() = default;

    virtual void displayDetails() const {       //This displays the account details useing the overloaded operator 
        std::cout << *this;  
    }

    virtual void deposit(double amount) {       //This method allows for the amount to be deposited in the account
        balance += amount;
    }

    virtual void withdraw(double amount) {      //This method allows for the amount to the withdrawn from the account
        if (balance >= amount) {
            balance -= amount;
        } else {
            std::cout << "Insufficient balance for withdrawal." << std::endl;
        }
    }

    virtual std::string getType() const = 0; 

    friend std::ostream& operator<<(std::ostream& os, const Account& account);
};

std::ostream& operator<<(std::ostream& os, const Account& account) {        //This section of code defines the << overload operator then uses it to print the output for the information in the correct formatted way for the account 
    os << "Account Details for " << account.getType() << " (ID: " << account.accountNumber << "):" << std::endl;
    os << "   Holder: " << account.accountHolder << std::endl;
    os << "   Balance: $" << std::fixed << std::setprecision(2) << account.balance << std::endl;
    return os;
}

class SavingsAccount : public Account {     //This section of code defines class SavingsAccount which is derived from the Account class that gives the private interest rate for the account. It also initializes the current account with the given information. The displayDetails is override to display the current details of the account and the << operator overloaded for output.
private:
    double interestRate;

public:
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const override {
        std::cout << *this;  

        std::cout << "   Interest Rate: " << interestRate * 100 << "%" << std::endl;
    }

    std::string getType() const override {
        return "Savings Account";
    }

    double getInterestRate() const {
        return interestRate;
    }
};

class CurrentAccount : public Account {     //This section of code defines class CurrentAccount which is derived from the Account class that gives the private overdraft limit for the account. It also initializes the current account with the given information. The displayDetails is override to display the current details of the account and the << operator overloaded for output.
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    void displayDetails() const override {
        std::cout << *this; 

        std::cout << "   Overdraft Limit: $" << overdraftLimit << std::endl;
    }

    std::string getType() const override {
        return "Current Account";
    }

    double getOverdraftLimit() const {      
        return overdraftLimit;
    }
};

class Transfer {        //This section of the code allows for various ammounts to be transferred from one account to another by withdrawing from the one account then depositing it in the other account      
public:
    static Account& transfer(Account& from, Account& to, double amount) {
        from.withdraw(amount);
        to.deposit(amount);
        return from;
    }
};

int main() {  //This section of code is what gives the information that is passed in for the banking account as well as calling the various classes to print the desired output.
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    std::cout << "Account Details before any transactions:" << std::endl;
    std::cout << std::endl;
    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
    std::cout << std::endl;

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "Account Details after deposit and withdrawal:" << std::endl;
    std::cout << std::endl;
    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
    std::cout << std::endl;

    Transfer::transfer(savings, current, 300);

    std::cout << "Account Details after transfer:" << std::endl;
    std::cout << std::endl;
    savings.displayDetails();
    std::cout << std::endl;
    current.displayDetails();
    std::cout << std::endl;

    return 0;
}

