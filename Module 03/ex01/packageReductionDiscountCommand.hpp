#pragma once

#include "command.hpp"

class PackageReductionDiscountCommand: public Command {
    public:
        PackageReductionDiscountCommand(int id, const Client& client, const std::vector<Article>& articles)
            : Command(id, client, articles) {}

        double get_total_price() const {
            double total = Command::get_total_price();
            if (total > 150) { total -= 10; }
            return total;
        }
};