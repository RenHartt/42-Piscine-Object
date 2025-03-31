#include <iostream>
#include "thuesdayDiscountCommand.hpp"
#include "packageReductionDiscountCommand.hpp"

int main() {
    Client client("John Doe");

    std::vector<Article> articles = {
        Article("Article 1", 50.0),
        Article("Article 2", 30.0),
        Article("Article 3", 80.0)
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

    Command* polymorphic_order = &big_order;
    std::cout << "Commande polymorphique (réduction pour total > 150€): " << std::endl;
    std::cout << *polymorphic_order << std::endl;

    return 0;
}
