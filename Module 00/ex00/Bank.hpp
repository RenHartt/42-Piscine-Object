#pragma once

#include <iostream>
#include <map>
#include <cmath>
#include <stdint.h>

struct Bank {
    private:
        struct Account;

        double liquidity;
        std::map<uintptr_t, Account*> clientAccounts;
    
    public:
        Bank() : liquidity(0) {}
        Bank(double liquidity) : liquidity(liquidity) {}

        const double& getLiquidity() const { return liquidity; }
        void setLiquidity(double liquidity) { this->liquidity = liquidity; }

        Account& operator[](uintptr_t id);

        Account* createAccount(double initialValue);
        void deleteAccount(uintptr_t id);
    
        void makeDeposit(uintptr_t id, double value);
        void makeWithdrawal(uintptr_t id, double value);
        void giveLoan(uintptr_t id, double amount);

        friend std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank);

        class InvalidOperation;
        class InvalidIndex;
};

struct Bank::Account {
    private:
        Account(double value) : value(value) {
            id = reinterpret_cast<uintptr_t>(this);
        }

        uintptr_t id;
        double value;

        friend std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank);

        friend struct Bank;
};

class Bank::InvalidOperation: public std::exception
{
	public:
		const char *what() const throw();
};

class Bank::InvalidIndex: public std::exception
{
	public:
		const char *what() const throw();
};