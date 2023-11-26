#include <iostream>
#include <string>
#include <vector>

class Account {
    private:
    std::string accountNumber;
    std::string accountHolder;
    int balance;

    public:
    Account(std::string accountNumber, std::string accountHolder, int balance) : accountNumber(accountNumber), accountHolder(accountHolder), balance(balance) {}
    
    virtual void displayDetails(std::ostream& os) const{
        os << "\t" << "Holder: " << accountHolder << std::endl;
        os << "\t" << "Balance: $" << balance << std::endl;
    }

    virtual void deposit(int amount){
        if (amount > 0){
        balance += amount;
        }else{
            std::cout << "Amount not greater than 0" << std::endl;
        }
    }
    virtual int withdraw(int amount){
        if (amount < balance && amount > 0) {
            balance -= amount;
            return amount;
        }else{
            std::cout << "You don't have enough money" << std::endl;
        }
    }
    Account operator+(Account& other){
        return Account(accountNumber, accountHolder, balance + other.balance);
    }

    int getbalance() const {
        return balance;
    }
    std::string getaccountNumber() const {
        return accountNumber;
    }
    std::string getaccountHolder() const {
        return accountHolder;
    }
};
std::ostream& operator<<(std::ostream& os, Account& account){
    account.displayDetails(os);
    return os;
}
class SavingsAccount : public Account {
    public:
    SavingsAccount(std::string accountNumber, std::string accountHolder, int balance) : Account(accountNumber, accountHolder, balance) {}
    
    void displayDetails(std::ostream& os) const override  {
        os << "Account Details for Savings Account (ID: " << getaccountNumber() << "):"<< std::endl;
        Account::displayDetails(os);
        os << '\n' << std::endl;
    }

    int withdraw(int amount) override {
        if (amount < getbalance() && amount > 0) {
            Account::withdraw(amount);
            return amount;
        }else{
            std::cout << "You don't have enough money" << std::endl;
        }
    }

};

class CurrentAccount : public Account {
    private:
    int overdraftLimit;

    public:
    CurrentAccount(std::string accountNumber, std::string accountHolder, int balance, int overdraftLimit) : Account(accountNumber, accountHolder, balance), overdraftLimit(overdraftLimit) {}

    void displayDetails(std::ostream& os) const override {
        os << "Account Details for Current Account (ID: " << getaccountNumber() << "):"<< std::endl;
        Account::displayDetails(os);
        os << "\t" << "Overdraft Limit: $" << overdraftLimit << '\n' << std::endl;
    }

    int withdraw(int amount) override {
        if (amount < getbalance() && amount > 0) {
            Account::withdraw(amount);
            return amount;
        }else{
            std::cout << "You don't have enough money" << std::endl;
        }
    }

    CurrentAccount operator+(SavingsAccount& other){
        return CurrentAccount(getaccountNumber(), getaccountHolder(), getbalance() + other.withdraw(300), overdraftLimit);
    }
};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails(std::cout);
    current.displayDetails(std::cout);

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "Account Details after deposit and withdrawal:" << std::endl;
    savings.displayDetails(std::cout);
    current.displayDetails(std::cout);

    // Transfer 300 from savings to current
    current = current + savings;
    
    std::cout << "Account Details after transfer:" << std::endl;
    savings.displayDetails(std::cout);
    current.displayDetails(std::cout);

    return 0;
}

