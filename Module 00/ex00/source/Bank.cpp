#include "Bank.hpp"
#include <limits>

Bank::Bank(double liquidity) : nextId(1), liquidity(liquidity) {}
Bank::~Bank() {
    for (std::map<long, Account*>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it) {
        delete it->second;
    }
}

double Bank::getLiquidity() const { return liquidity; }
void Bank::setLiquidity(double liquidity) { this->liquidity = liquidity; }

long Bank::createAccount(double initialValue) {
    Account* account = new Account(nextId, initialValue);
    clientAccounts[account->id] = account;
    ++nextId;
    return account->id;
}

void Bank::deleteAccount(long id) {
    if (clientAccounts.find(id) == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    delete clientAccounts[id];
    clientAccounts.erase(id);
}

void Bank::makeDeposit(long id, double value) {
    if (clientAccounts.find(id) == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = clientAccounts[id];

    if (account->value > std::numeric_limits<double>::max() - value || value < 0) {
        throw Bank::InvalidOperation();
    }
    double tax = round(value * 0.05);
    double net = value - tax;
    this->liquidity += tax;
    account->value += net;
}

void Bank::makeWithdrawal(long id, double value) {
    if (clientAccounts.find(id) == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = clientAccounts[id];

    if (value > account->value) {
        throw Bank::InvalidOperation();
    }
    account->value -= value;
}

void Bank::giveLoan(long id, double value) {
    if (clientAccounts.find(id) == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = clientAccounts[id];

    if (value > this->liquidity || account->value > std::numeric_limits<double>::max() - value || value < 0) {
        throw Bank::InvalidOperation();
    }
    account->value += value;
    this->liquidity -= value;
}

Bank::Account const& Bank::operator[](long id) {
    if (clientAccounts.find(id) == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    return *clientAccounts[id];
}

const char* Bank::InvalidOperation::what() const throw() {
    return "Invalid operation";
}

const char* Bank::InvalidIndex::what() const throw() {
    return "Invalid account ID";
}

std::ostream& operator<<(std::ostream& p_os, const Bank& p_bank) {
    p_os << "Bank informations:\n";
    p_os << "Liquidity: " << p_bank.liquidity << "\n";
    for (std::map<long, Bank::Account*>::const_iterator it = p_bank.clientAccounts.begin(); it != p_bank.clientAccounts.end(); ++it) {
        const Bank::Account* account = it->second;
        p_os << "Account " << account->getId() << ": " << account->getValue() << "\n";
    }
    return p_os;
}
