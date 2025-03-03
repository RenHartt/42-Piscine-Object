#include <iostream>
#include "command.hpp"
#include "thuesdayDiscountCommand.hpp"
#include "packageReductionDiscountCommand.hpp"

void print_total_price(const Command& command) {
    std::cout << "Total price: " << command.get_total_price() << " euros" << std::endl;
}

int main() {
    Client client("John Doe");

    std::set<Article> articles = {
        Article("Laptop", 1000.0, 1),  // 1 laptop à 1000€
        Article("Mouse", 50.0, 2)      // 2 souris à 50€ chacune
    };

    Command base_order(1, client, articles);
    std::cout << "Commande standard: ";
    print_total_price(base_order); // Attendu: 1100€

    ThuesdayDiscountCommand tuesday_order(2, client, articles);
    std::cout << "Commande avec réduction du mardi: ";
    print_total_price(tuesday_order); // Attendu: 990€ (10% de réduction si mardi)

    PackageReductionDiscountCommand big_order(3, client, articles);
    std::cout << "Commande avec réduction pour total > 150€: ";
    print_total_price(big_order); // Attendu: 1090€ (-10€ si total > 150€)

    Command* polymorphic_order = &tuesday_order;
    std::cout << "Commande polymorphique (réduction du mardi si applicable): ";
    print_total_price(*polymorphic_order);

    return 0;
}
