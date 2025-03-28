#include <iostream>
#include "command.hpp"
#include "thuesdayDiscountCommand.hpp"
#include "packageReductionDiscountCommand.hpp"

int main() {
    Client client("John Doe");

    std::set<Article> articles = {
        Article("Laptop", 1000.0, 1),
        Article("Mouse", 50.0, 2)
    };

    Command base_order(1, client, articles);
    std::cout << "Commande standard: " << std::endl;
    std::cout << base_order << std::endl;

    ThuesdayDiscountCommand tuesday_order(2, client, articles);
    std::cout << "Commande avec réduction du mardi: " << std::endl;
    std::cout << tuesday_order << std::endl;

    PackageReductionDiscountCommand big_order(3, client, articles);
    std::cout << "Commande avec réduction pour total > 150€: " << std::endl;
    std::cout << big_order << std::endl;

    Command* polymorphic_order = &tuesday_order;
    std::cout << "Commande polymorphique (réduction du mardi si applicable): " << std::endl;
    std::cout << *polymorphic_order << std::endl;

    return 0;
}
