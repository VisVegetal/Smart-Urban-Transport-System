#include "../include/Ticket.hpp"

#include <utility>

Ticket::Ticket(double price, std::string serial) : basePrice(price), serial(std::move(serial)) {}
const std::string& Ticket::getSerial() const { return serial; }
std::string Ticket::getDetails() const { return "Serial: " + serial; }

FullTicket::FullTicket(double price, std::string serial) : Ticket(price, std::move(serial)) {}
double FullTicket::getFinalPrice() const { return basePrice; }

ReducedTicket::ReducedTicket(double price, std::string serial, double discount)
    : Ticket(price, std::move(serial)), discountPercentage(discount) {}
double ReducedTicket::getFinalPrice() const { return basePrice * (1.0 - discountPercentage); }
