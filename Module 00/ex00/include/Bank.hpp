#pragma once

#include <iostream>
#include <map>
#include <cmath>
#include <stdint.h>
#include <exception>

struct Bank {
private:
    struct Account;
    long nextId;
    double liquidity;
    std::map<long, Account*> clientAccounts;

public:
    Bank(double liquidity = 0);
    ~Bank();

    double getLiquidity() const;
    void setLiquidity(double liquidity);

    Account const& operator[](long id);

    long createAccount(double initialValue);
    void deleteAccount(long id);

    void makeDeposit(long id, double value);
    void makeWithdrawal(long id, double value);
    void giveLoan(long id, double amount);

    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

    class InvalidOperation;
    class InvalidIndex;
};

struct Bank::Account {
private:
    Account(long id, double value = 0) : id(id), value(value) {}

    long id;
    double value;
    
    friend struct Bank;
    friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

public:
    long getId() const { return id; }
    double getValue() const { return value; }
};

class Bank::InvalidOperation : public std::exception {
public:
    virtual const char* what() const throw();
};

class Bank::InvalidIndex : public std::exception {
public:
    virtual const char* what() const throw();
};
