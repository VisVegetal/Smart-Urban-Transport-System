#include "../include/Ticketing.hpp"

TicketingSystem::TicketingSystem() : serialCounter(1000) {}

TicketingSystem::TicketingSystem(const TicketingSystem& other) {
    this->serialCounter = other.serialCounter;
    this->soldTickets.clear();
    for (const auto& t : other.soldTickets) {
        if (t) {
            this->soldTickets.push_back(t->clone());
        }
    }
}

TicketingSystem& TicketingSystem::operator=(const TicketingSystem& other) {
    if (this != &other) {
        this->serialCounter = other.serialCounter;
        this->soldTickets.clear();
        for (const auto& t : other.soldTickets) {
            if (t) {
                this->soldTickets.push_back(t->clone());
            }
        }
    }
    return *this;
}

void TicketingSystem::issueFullTicket(double price) {
    std::string serial = "FULL-" + std::to_string(++serialCounter);
    soldTickets.push_back(std::make_unique<FullTicket>(price, serial));
}

void TicketingSystem::issueReducedTicket(double price, double discount) {
    std::string serial = "RED-" + std::to_string(++serialCounter);
    soldTickets.push_back(std::make_unique<ReducedTicket>(price, serial, discount));
}

double TicketingSystem::calculateRevenue() const {
    double total = 0;
    for (const auto& t : soldTickets) {
        total += t->getFinalPrice();
    }
    return total;
}
