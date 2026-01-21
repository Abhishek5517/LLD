#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <memory>

using namespace std;

// Enum for vehicle type
enum class Vehicle { BIKE, CAR, LARGE };

// Parking slot
class ParkingSlot {
public:
    int slotNumber;
    Vehicle type;
    bool occupied;

    ParkingSlot(int slotNum) : slotNumber(slotNum), occupied(false) {}
};

// Ticket
class Ticket {
public:
    string ticketId;
    int floorNumber;
    ParkingSlot* slot; 
    chrono::system_clock::time_point parked_at;

    Ticket() : slot(nullptr) {}
};

// Floor
class Floor {
public:
    int floorNumber;
    vector<ParkingSlot> slots;
    unordered_map<string, Ticket> tickets;

    Floor(int floorNum, int slotCount) : floorNumber(floorNum) {
        for (int i = 0; i < slotCount; i++) {
            slots.emplace_back(i);
        }
    }

    vector<string> getTicket(Vehicle vehicle) {
        vector<string> ticketDetails;
        Ticket ticket = generateTicket(vehicle);
        if (ticket.ticketId.empty()) {
            ticketDetails.push_back("False");
            ticketDetails.push_back("Slot occupied");
        } else {
            tickets[ticket.ticketId] = ticket;
            ticketDetails.push_back("True");
            ticketDetails.push_back(ticket.ticketId);
        }
        return ticketDetails;
    }

    Ticket generateTicket(Vehicle vehicle) {
        Ticket newTicket;
        for (auto& slot : slots) {
            if (!slot.occupied) {
                slot.occupied = true;
                slot.type = vehicle;

                newTicket.floorNumber = floorNumber;
                newTicket.slot = &slot;
                newTicket.parked_at = chrono::system_clock::now();
                newTicket.ticketId = to_string(floorNumber) + "_" + to_string(slot.slotNumber);

                return newTicket;
            }
        }
        return newTicket; // empty ticket if no slot available
    }

    void removeTicket(const string& tId) {
        if (!tickets.count(tId)) return;

        Ticket& ticket = tickets[tId];
        if (ticket.slot) ticket.slot->occupied = false;

        tickets.erase(tId);
    }

    int getCost(const string& tId) {
        if (!tickets.count(tId)) return 0;

        Ticket& ticket = tickets[tId];
        auto now = chrono::system_clock::now();
        auto duration = now - ticket.parked_at;
        auto hours = chrono::duration_cast<chrono::hours>(duration).count();
        if (hours < 1) hours = 1; // minimum 1 hour

        switch (ticket.slot->type) {
            case Vehicle::BIKE:  return 60 * hours;
            case Vehicle::CAR:   return 100 * hours;
            case Vehicle::LARGE: return 120 * hours;
        }
        return 0;
    }
};

// Payment abstraction
class Payment {
public:
    virtual void pay(int cost) = 0;
};

class UPIPayment : public Payment {
public:
    void pay(int cost) override {
        cout << cost << " paid using UPI" << endl;
    }
};

class CardPayment : public Payment {
public:
    void pay(int cost) override {
        cout << cost << " paid using Card" << endl;
    }
};

// Parking system
class ParkingSystem {
public:
    vector<Floor> floors;

    ParkingSystem(int n, int slotsPerFloor) {
        for (int i = 0; i < n; i++) {
            floors.emplace_back(i, slotsPerFloor);
        }
    }
};


class User {
     public: 
     Ticket *ticket; 
     Payment *paying;
     Vehicle type;
     User(Vehicle vehicle , Payment *newPayment) : type(vehicle) , ticket(NULL), paying(newPayment)  {}
};

int main() {
    ParkingSystem parking(2, 10);
    User *u1 = new User(Vehicle::BIKE , new UPIPayment) ;
    

    auto a = parking.floors[0].getTicket(Vehicle::BIKE);
    cout << a[0] << " " << a[1] << endl;

    auto b = parking.floors[0].getTicket(Vehicle::CAR);
    cout << b[0] << " " << b[1] << endl;

    auto c = parking.floors[0].getTicket(Vehicle::LARGE);
    cout << c[0] << " " << c[1] << endl;

    // simulate payment
    int cost = parking.floors[0].getCost(a[1]);
    UPIPayment upi;
    upi.pay(cost);

    // remove ticket
    parking.floors[0].removeTicket(a[1]);

    return 0;
}
