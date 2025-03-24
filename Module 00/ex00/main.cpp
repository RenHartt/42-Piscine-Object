#include "Bank.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Bank bank(1000.0);
        std::cout << "Banque créée avec une liquidité de " << bank.getLiquidity() << "\n";

        long id1 = bank.createAccount(500.0);
        long id2 = bank.createAccount(200.0);
        long id3 = bank.createAccount(0.0);

        std::cout << "Comptes créés avec les IDs : " 
                  << id1 << ", " << id2 << ", " << id3 << "\n";

        bank.makeDeposit(id1, 100.0);
        std::cout << "Dépôt de 100 effectué sur le compte " << id1 << "\n";

        bank.makeWithdrawal(id2, 50.0);
        std::cout << "Retrait de 50 effectué sur le compte " << id2 << "\n";

        bank.giveLoan(id3, 300.0);
        std::cout << "Prêt de 300 octroyé sur le compte " << id3 << "\n";

        std::cout << "\nÉtat de la banque après opérations :\n" << bank << "\n";

        try {
            std::cout << "\nTentative de retrait excessif sur le compte " << id2 << "\n";
            bank.makeWithdrawal(id2, 1000.0);
        }
        catch (const Bank::InvalidOperation &e) {
            std::cerr << "Erreur (opération invalide) : " << e.what() << "\n";
        }

        try {
            std::cout << "\nAccès à un compte inexistant (ID 999) via operator[] :\n";
            bank[999];
        }
        catch (const Bank::InvalidIndex &e) {
            std::cerr << "Erreur (index invalide) : " << e.what() << "\n";
        }

        bank.deleteAccount(id2);
        std::cout << "\nCompte " << id2 << " supprimé.\n";

        try {
            std::cout << "\nTentative d'accès au compte supprimé " << id2 << " via operator[] :\n";
            bank[id2];
        }
        catch (const Bank::InvalidIndex &e) {
            std::cerr << "Erreur (compte supprimé) : " << e.what() << "\n";
        }

        std::cout << "\nÉtat final de la banque :\n" << bank << "\n";
    }
    catch (const std::exception &e) {
        std::cerr << "Exception non gérée : " << e.what() << "\n";
    }
    return 0;
}
