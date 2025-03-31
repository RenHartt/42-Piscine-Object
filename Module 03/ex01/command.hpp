#pragma once

#include <ctime>
#include <string>
#include <vector>

struct Article {
    Article(const std::string& name = "", double price = 0, double quantity = 1)
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
    int id;
    Date date;
    Client client;
    std::vector<Article> articles;
public:
    Command(int id, const Client& client, const std::vector<Article>& articles)
        : id(id), client(client), articles(articles) {}
    virtual ~Command() {}
    
    int get_id() const { return id; }
    const Date& get_date() const { return date; }
    const Client& get_client() const { return client; }
    const std::vector<Article>& get_articles() const { return articles; }

    virtual double get_total_price() const {
        double total(0);
        for (const auto& article : articles) {
            total += article.price * article.quantity;
        }
        return total;
    }
};

std::ostream& operator<<(std::ostream& os, const Command& command) {
    
    os << "Commande " << command.get_id() << " " << std::endl;
    os << "Client: " << command.get_client().name << std::endl;
    os << "Date: " << command.get_date().date.tm_mday << "/"
    << (command.get_date().date.tm_mon + 1) << "/"
    << (command.get_date().date.tm_year + 1900) << std::endl;
    os << "Articles:" << std::endl;
    for (const auto& article : command.get_articles()) {
        os << " - " << article.name << ": " << article.price << "€ x " << article.quantity << std::endl;
    }
    os << "Total: " << command.get_total_price() << "€" << std::endl;

    return os;
}