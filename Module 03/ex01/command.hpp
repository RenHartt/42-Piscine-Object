#pragma once

#include <ctime>
#include <string>
#include <set>

struct Article {
    Article(const std::string& name, double price, double quantity)
        : name(name), price(price), quantity(quantity) {}
    
    std::string name;
    double price;
    double quantity;
};

struct Date {
    Date() {
        time_t now = time(NULL);
        date = *localtime(&now);
    }

    struct tm date;
};

struct Client {
    Client(const std::string& name): name(name) {}

    std::string name;
};

class Command {
    protected:
        const int id;
        const Date date;
        const Client client;
        std::set<Article> articles;
    public:
        Command(int id, const Client& client, const std::set<Article>& articles)
            : id(id), client(client), articles(articles) {}
        virtual ~Command() {}
        
        virtual double get_total_price() const {
            double total(0);
            for (const auto& article : articles) {
                total += article.price * article.quantity;
            }
            return total;
        }

        friend std::ostream& operator<<(std::ostream& os, const Command& command);
};

std::ostream& operator<<(std::ostream& os, const Command& command) {
    os << "Commande " << command.id 
    << " du " << command.date.date.tm_mday << "/" << command.date.date.tm_mon + 1 << "/" << command.date.date.tm_year + 1900
    << " pour " << command.client.name << ":" << std::endl;
    for (const auto& article : command.articles) {
        os << "  - " << article.name << " (" << article.quantity << "x" << article.price << "€)\n";
    }
    os << "Prix total: " << command.get_total_price() << "€";

    return os;
}