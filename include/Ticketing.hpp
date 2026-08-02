#ifndef TICKETING_HPP
#define TICKETING_HPP

#include <memory>
#include <vector>

#include "Ticket.hpp"

class TicketingSystem {
private:
    std::vector<std::unique_ptr<Ticket>> soldTickets;
    int serialCounter;

public:
    TicketingSystem();
    ~TicketingSystem() = default;
    TicketingSystem(const TicketingSystem& other);
    TicketingSystem& operator=(const TicketingSystem& other);

    void issueFullTicket(double price);
    void issueReducedTicket(double price, double discount);

    [[nodiscard]] double calculateRevenue() const;
};

#endif
