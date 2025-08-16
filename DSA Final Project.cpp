#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Train {
    string name;
    string route;
    int price;
    int availableSeats;
    vector<int> seatNumbers;
};

struct Reservation {
    int seatNumber;
    string trainName;
    string passengerName;
    string fatherName;
    string phoneNumber;
    string cnic;
    string fromCity;
    string toCity;
    string travelDate;
};

vector<Train> trains = {
    {"Greenline", "Karachi to Islamabad", 8000, 50, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
    {"Awami Express", "Karachi to Rawalpindi", 8000, 50, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
    {"Tezz Gam", "Karachi to Rawalpindi", 8000, 50, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
    {"Karakaram Express", "Karachi to Lahore", 5000, 50, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
    {"Karachi Express", "Karachi to Lahore", 5000, 50, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
};

map<int, Reservation> reservations;
int currentSerial = 1;

bool login() {
    string email, password;
    while (true) {
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;

        
        if (email == "faizan" && password == "12345") {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Invalid email or password. Please try again.\n";
        }
    }
}

void showTrains() {
    cout << "Available Trains:\n";
    for (size_t i = 0; i < trains.size(); ++i) {
        cout << i + 1 << ". " << trains[i].name << " - " << trains[i].route << " - Rs." << trains[i].price << "\n";
    }
}

void makeReservation() {
    cout << "Welcome to TrackLine Train Booking Service\n" <<endl;

    cout << "Enter your Departure city: ";
    string fromCity;
    cin.ignore();
    getline(cin, fromCity);

    cout << "Enter your destination city: ";
    string toCity;
    getline(cin, toCity);

    cout << "Enter your travel date (DD/MM/YYYY): ";
    string travelDate;
    getline(cin, travelDate);

    showTrains();
    cout << "\nSelect a train (1-" << trains.size() << "): ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > trains.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    Train &selectedTrain = trains[choice - 1];

    if (selectedTrain.availableSeats <= 0) {
        cout << "Sorry, no seats available on this train.\n";
        return;
    }

    cout << "Enter your name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "Enter your father's name: ";
    string fatherName;
    getline(cin, fatherName);

    cout << "Enter your phone number: ";
    string phoneNumber;
    getline(cin, phoneNumber);

    cout << "Enter your CNIC: ";
    string cnic;
    getline(cin, cnic);

    cout << "Select a seat number from the following: \n";
    bool seatFound = false;
    int seatNumber;
    for (size_t i = 0; i < selectedTrain.seatNumbers.size(); ++i) {
        cout << selectedTrain.seatNumbers[i] << " ";
    }
    cout << "\nEnter seat number: ";
    cin >> seatNumber;

    
    for (size_t i = 0; i < selectedTrain.seatNumbers.size(); ++i) {
        if (selectedTrain.seatNumbers[i] == seatNumber) {
            seatFound = true;
            selectedTrain.seatNumbers.erase(selectedTrain.seatNumbers.begin() + i);
            break;
        }
    }

    if (!seatFound) {
        cout << "Invalid seat number!\n";
        return;
    }

    selectedTrain.availableSeats--;

    reservations[seatNumber] = {seatNumber, selectedTrain.name, name, fatherName, phoneNumber, cnic, fromCity, toCity, travelDate};
    cout << "Reservation successful!\n";
    cout << "\n*************** Ticket Details ***************\n";
    cout << "Train: " << selectedTrain.name << "\nRoute: " << selectedTrain.route << "\nPassenger Name: " << name << "\nFather's Name: " << fatherName << "\nPhone Number: " << phoneNumber << "\nCNIC: " << cnic << "\nFrom: " << fromCity << "\nTo: " << toCity << "\nDate: " << travelDate << "\nSeat Number: " << seatNumber << "\nPrice: Rs." << selectedTrain.price << "\n";
    cout << "********************\n";
}

void cancelReservation() {
    cout << "Enter your name: ";
    string name;
    cin.ignore();
    getline(cin, name);

    cout << "Enter train name: ";
    string trainName;
    getline(cin, trainName);

    cout << "Enter seat number: ";
    int seatNumber;
    cin >> seatNumber;

    if (reservations.find(seatNumber) != reservations.end() &&
        reservations[seatNumber].passengerName == name &&
        reservations[seatNumber].trainName == trainName) {

        Reservation res = reservations[seatNumber];

        for (auto &train : trains) {
            if (train.name == res.trainName) {
                train.seatNumbers.push_back(seatNumber);
                train.availableSeats++;
                break;
            }
        }

        reservations.erase(seatNumber);
        cout << "Your ticket for train " << trainName << " has been cancelled successfully.\n";
    } else {
        cout << "Your ticket for train " << trainName << " has been cancelled successfully.\n";
    }
}

void showMenu() {
    cout << "\nOnline Train Reservation System\n";
    cout << "1. Reserve a Seat\n";
    cout << "2. Cancel Reservation\n";
    cout << "3. View Available Trains\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    cout << "Welcome to F&F Train Booking Service\n";

    if (!login()) {
        return 0;
    }

    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                makeReservation();
                break;
            case 2:
                cancelReservation();
                break;
            case 3:
                showTrains();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
