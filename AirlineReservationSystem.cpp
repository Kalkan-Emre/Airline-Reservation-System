#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger newPassenger;
    newPassenger = Passenger(firstname, lastname);
    passengers.insert(newPassenger);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger newPassenger;
    newPassenger = Passenger(firstname, lastname);
    BSTNode<Passenger>* passenger_node = passengers.search(newPassenger);
    Passenger* result = (passenger_node!=NULL) ? &(passenger_node->data) : NULL;
    return result;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    Flight newFlight;
    newFlight = Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity,businessCapacity);
    flights.insert(newFlight);
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight *> result;
    searchFlight_helper(flights.getRoot(), departureCity, arrivalCity, result);
    return result;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Flight * flight = searchFlight_helper2(flights.getRoot(),flightCode);
    Passenger * passenger = searchPassenger(firstname,lastname);
    if(passenger != NULL && flight!=NULL)
    {
        if(!flight->isCompleted())
        {
            if(ticketType == business && flight->getBusinessCapacity()!=0)
            {
                Ticket newTicket = Ticket(passenger, flight, ticketType);
                flight->addTicket(newTicket);
            }
            if(ticketType == economy && flight->getEconomyCapacity()!=0)
            {
                Ticket newTicket = Ticket(passenger, flight, ticketType);
                flight->addTicket(newTicket);
            }
        }
    }
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Flight * flight = searchFlight_helper2(flights.getRoot(),flightCode);
    Passenger * passenger = searchPassenger(firstname,lastname);
    if(passenger != NULL && flight!=NULL)
    {
        Ticket newTicket = Ticket(passenger, flight, ticketType);
        freeTicketRequests.enqueue(newTicket);
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    Flight * flight = searchFlight_helper2(flights.getRoot(),flightCode);
    for(int i = 0; i<freeTicketRequests.size();i++)
    {
        if(freeTicketRequests.peek().getFlight()->getFlightCode()==flightCode)
        {
            flight->addTicket(freeTicketRequests.dequeue());
        }
        else{
            freeTicketRequests.enqueue(freeTicketRequests.dequeue());
        }
    }
    flight->setCompleted(true);
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}

void AirlineReservationSystem::searchFlight_helper(BSTNode<Flight>* r, const std::string &departureCity, const std::string &arrivalCity,std::vector<Flight *> &v){
    if(r==NULL)
    {
        return;
    }
    else if(r->data.getArrivalCity()==arrivalCity && r->data.getDepartureCity() == departureCity)
    {
        v.push_back(&r->data);
    }
    searchFlight_helper(r->left, departureCity, arrivalCity, v);
    searchFlight_helper(r->right, departureCity, arrivalCity, v);
}


Flight * AirlineReservationSystem::searchFlight_helper2(BSTNode<Flight>* r, const std::string &flightCode){
    if(r==NULL)
    {
        return NULL;
    }
    else 
    {
        if(r->data.getFlightCode()==flightCode)
            return &(r->data);
        else if (r->data.getFlightCode()<flightCode)
            return searchFlight_helper2(r->right, flightCode);
        else if (r->data.getFlightCode()>flightCode)
            return searchFlight_helper2(r->left, flightCode);
    }
}