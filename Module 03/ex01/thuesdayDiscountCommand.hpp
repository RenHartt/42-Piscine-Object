#pragma once

#include "command.hpp"

class ThuesdayDiscountCommand: public Command {
public:
    ThuesdayDiscountCommand(int id, const Client& client, const std::vector<Article>& articles)
        : Command(id, client, articles) {}

    double get_total_price() const {
        double total = Command::get_total_price();
        if (date.date.tm_wday == 2) { total *= 0.9; }
        return total;
    }
};