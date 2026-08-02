#ifndef TICKET_HPP
#define TICKET_HPP

#include <memory>
#include <string>

class Ticket {
protected:
    double basePrice;
    std::string serial;

public:
    Ticket(double price, std::string serial);
    virtual ~Ticket() = default;

    // Pure virtual: makes the class abstract
    [[nodiscard]] virtual std::unique_ptr<Ticket> clone() const = 0;

    [[nodiscard]] virtual double getFinalPrice() const = 0;
};

class FullTicket : public Ticket {
public:
    FullTicket(double price, std::string serial);
    [[nodiscard]] double getFinalPrice() const override;

    [[nodiscard]] std::unique_ptr<Ticket> clone() const override {
        return std::make_unique<FullTicket>(*this);
    }
};

class ReducedTicket : public Ticket {
private:
    double discountPercentage;

public:
    ReducedTicket(double price, std::string serial, double discount);
    [[nodiscard]] double getFinalPrice() const override;

    [[nodiscard]] std::unique_ptr<Ticket> clone() const override {
        return std::make_unique<ReducedTicket>(*this);
    }
};

#endif
