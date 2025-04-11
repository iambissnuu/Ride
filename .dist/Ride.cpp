#include <iostream>
#include <string>
#include <vector>

#include <cstdlib> 
#include <ctime> 
using namespace std;

// Base Ride class
class Ride {
protected:
    string rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;

public:
    Ride(string id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    virtual double fare() const = 0;

    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID
             << " | From: " << pickupLocation
             << " | To: " << dropoffLocation
             << " | Distance: " << distance
             << " miles | Fare: $" << fare() << endl;
    }

    virtual ~Ride() {}
};

// Standard Ride subclass
class StandardRide : public Ride {
public:
    StandardRide(string id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 1.5;
    }
};

// Premium Ride subclass
class PremiumRide : public Ride {
public:
    PremiumRide(string id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    double fare() const override {
        return distance * 3.0;
    }
};

// Driver class
class Driver {
private:
    string driverID;
    string name;
    double rating;
    vector<Ride*> assignedRides; // encapsulated list

public:
    Driver(string id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        cout << "\nDriver Info:\n";
        cout << "ID: " << driverID << " | Name: " << name << " | Rating: " << rating << endl;
        cout << "Assigned Rides: " << assignedRides.size() << endl;
    }
};

// Rider class
class Rider {
private:
    string riderID;
    string name;
    vector<Ride*> requestedRides; // encapsulated list

public:
    Rider(string id, string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        cout << "\nRide History for " << name << ":\n";
        for (const auto& ride : requestedRides) {
            ride->rideDetails(); // polymorphism
        }
    }
};

string getRandomLocation() {
    vector<string> locations = {"Downtown", "Airport", "Mall", "Hotel", "Park", "Station", "University"};
    return locations[rand() % locations.size()];
}

Ride* createRandomRide(int id) {
    string pickup = getRandomLocation();
    string dropoff = getRandomLocation();
    while (dropoff == pickup) {
        dropoff = getRandomLocation();
    }

    double dist = (rand() % 20) + 1;
    string rideID = "R" + to_string(100 + id);

    if (rand() % 2 == 0)
        return new StandardRide(rideID, pickup, dropoff, dist);
    else
        return new PremiumRide(rideID, pickup, dropoff, dist);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Driver driver("D101", "Alex", 4.8);
    Rider rider("U300", "Emma");

    for (int i = 0; i < 5; ++i) {
        Ride* ride = createRandomRide(i);
        driver.addRide(ride);
        rider.requestRide(ride);
    }

    driver.getDriverInfo();
    rider.viewRides();

    return 0;
}
