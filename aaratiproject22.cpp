#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class FlightReservationSystem {
private:
    static const int numFlights = 3; 
    static const int seatsPerFlight = 5; 
    queue<string> passengerNames[numFlights]; 
    queue<int> seatNumbers[numFlights]; 
    stack<string> cancelledNames[numFlights]; 
    stack<int> cancelledSeats[numFlights]; 
    bool seatMap[numFlights][seatsPerFlight]; 

public:
    FlightReservationSystem() {
        for (int i = 0; i < numFlights; i++) {
            for (int j = 0; j < seatsPerFlight; j++) {
                seatMap[i][j] = false; 
            }
        }
    }

    void bookTicket(int flightNo, string name, int seatNo) {
        if (flightNo < 1 || flightNo > numFlights) {
            cout << "Invalid flight number! Choose between 1-" << numFlights << ".\n";
            return;
        }
        flightNo--; 
        if (seatNo < 1 || seatNo > seatsPerFlight) {
            cout << "Invalid seat number! Choose between 1-" << seatsPerFlight << ".\n";
            return;
        }

        if (seatMap[flightNo][seatNo - 1]) {
            cout << "Seat " << seatNo << " on Flight " << (flightNo + 1) << " is already booked.\n";
            return;
        }

        passengerNames[flightNo].push(name);
        seatNumbers[flightNo].push(seatNo);
        seatMap[flightNo][seatNo - 1] = true;  
        cout << "Booking successful for " << name << " on Flight " << (flightNo + 1) << " at Seat No: " << seatNo << "\n";
    }

    void cancelTicket(int flightNo) {
        if (flightNo < 1 || flightNo > numFlights) {
            cout << "Invalid flight number! Choose between 1-" << numFlights << ".\n";
            return;
        }
        flightNo--; 

        if (!passengerNames[flightNo].empty()) {
            string name = passengerNames[flightNo].front();
            int seat = seatNumbers[flightNo].front();
            passengerNames[flightNo].pop();
            seatNumbers[flightNo].pop();

            cancelledNames[flightNo].push(name); 
            cancelledSeats[flightNo].push(seat); 

            seatMap[flightNo][seat - 1] = false;  
            cout << "Cancellation successful for " << name << " on Flight " << (flightNo + 1) << " at Seat No: " << seat << "\n";
        } else {
            cout << "No bookings to cancel for Flight " << (flightNo + 1) << ".\n";
        }
    }

    void displayBookings(int flightNo) {
        if (flightNo < 1 || flightNo > numFlights) {
            cout << "Invalid flight number! Choose between 1-" << numFlights << ".\n";
            return;
        }
        flightNo--; 

        queue<string> tempNames = passengerNames[flightNo];
        queue<int> tempSeats = seatNumbers[flightNo];

        if (tempNames.empty()) {
            cout << "No active bookings for Flight " << (flightNo + 1) << ".\n";
            return;
        }

        cout << "Current Bookings for Flight " << (flightNo + 1) << ":\n";
        while (!tempNames.empty()) {
            cout << "Name: " << tempNames.front() << " | Seat No: " << tempSeats.front() << endl;
            tempNames.pop();
            tempSeats.pop();
        }
    }

    void displayCancellations(int flightNo) {
        if (flightNo < 1 || flightNo > numFlights) {
            cout << "Invalid flight number! Choose between 1-" << numFlights << ".\n";
            return;
        }
        flightNo--; 

        stack<string> tempCancelledNames = cancelledNames[flightNo];
        stack<int> tempCancelledSeats = cancelledSeats[flightNo];

        if (tempCancelledNames.empty()) {
            cout << "No cancellations for Flight " << (flightNo + 1) << ".\n";
            return;
        }

        cout << "Cancelled Bookings for Flight " << (flightNo + 1) << ":\n";
        while (!tempCancelledNames.empty()) {
            cout << "Name: " << tempCancelledNames.top() << " | Seat No: " << tempCancelledSeats.top() << endl;
            tempCancelledNames.pop();
            tempCancelledSeats.pop();
        }
    }
};

int main() {
    FlightReservationSystem system;
    int choice, flightNo, seatNo;
    string name;

    do {
        cout << "\nAirline Reservation System\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. Show Bookings\n4. Show Cancellations\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Flight No (1-3): ";
                cin >> flightNo;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Seat No (1-5): ";
                cin >> seatNo;
                system.bookTicket(flightNo, name, seatNo);
                break;
            case 2:
                cout << "Enter Flight No (1-3): ";
                cin >> flightNo;
                system.cancelTicket(flightNo);
                break;
            case 3:
                cout << "Enter Flight No (1-3): ";
                cin >> flightNo;
                system.displayBookings(flightNo);
                break;
            case 4:
                cout << "Enter Flight No (1-3): ";
                cin >> flightNo;
                system.displayCancellations(flightNo);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}

