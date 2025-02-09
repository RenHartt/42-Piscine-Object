#include "Bank.hpp"
#include <limits>

Bank::Account* Bank::createAccount(double initialValue) {
    Account* account = new Account(initialValue);
    clientAccounts[account->id] = account;
    return account;
}

void Bank::deleteAccount(uintptr_t id) {
    auto it = clientAccounts.find(id);
    if (it == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    delete it->second;
    clientAccounts.erase(it);
}

void Bank::makeDeposit(uintptr_t id, double value) {
    auto it = clientAccounts.find(id);
    if (it == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = it->second;

    if (account->value > std::numeric_limits<double>::max() - value) {
        throw Bank::InvalidOperation();
    }
    double tax = std::round(value * 0.05);
    double net = value - tax;
    this->liquidity += tax;
    account->value += net;
}

void Bank::makeWithdrawal(uintptr_t id, double value) {
    auto it = clientAccounts.find(id);
    if (it == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = it->second;

    if (value > account->value) {
        throw Bank::InvalidOperation();
    }
    account->value -= value;
}

void Bank::giveLoan(uintptr_t id, double value) {
    auto it = clientAccounts.find(id);
    if (it == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    Account* account = it->second;

    if (value > this->liquidity || account->value > std::numeric_limits<double>::max() - value) {
        throw Bank::InvalidOperation();
    }
    account->value += value;
}

Bank::Account& Bank::operator[](uintptr_t id) {
    auto it = clientAccounts.find(id);
    if (it == clientAccounts.end()) {
        throw Bank::InvalidIndex();
    }
    return *(it->second);
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
    for (const auto& pair : p_bank.clientAccounts) {
        p_os << "[" << pair.second->id << "] - [" << pair.second->value << "]\n";
    }
    return p_os;
}
