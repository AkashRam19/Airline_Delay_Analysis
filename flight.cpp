/*
* Project 3: Airline Delay Detection System
* flight.cpp
*
* Team: Runtime Terrors
* Members: Chirag Narang, Keyur Patel, Akash Ram
* 
*/

#include <string>
#include <iostream>
#include <chrono> 

using namespace std;

class Flight {
private:
    string year;
    int month;
    string carrier;
    string carrierName;
    string airport;
    string airportName;
    double arrivingFlights;
    double delayedFlights;
    double cancelled;
    double diverted;
    double totalDelay;
    double carrierDelay;
    double weatherDelay;
    double NASDelay;
    double securityDelay;
    double lateAircraftDelay;

public:
    //Default Constructor
    Flight() {
        this->year = "0000";
        this->month = 1;
        this->carrier = "";
        this->carrierName = "";
        this->airport = "";
        this->airportName = "";
        this->arrivingFlights = 0.0;
        this->delayedFlights = 0.0;
        this->cancelled = 0.0;
        this->diverted = 0.0;
        this->totalDelay = 0.0;
        this->carrierDelay = 0.0;
        this->weatherDelay = 0.0;
        this->NASDelay = 0.0;
        this->securityDelay = 0.0;
        this->lateAircraftDelay = 0.0;
    }

    //Constructor
    Flight(string year, int month, string carrier, string carrierName, string airport, string airportName, double arrivingFlights, double delayedFlights, double cancelled, double diverted, double totalDelay, double carrierDelay, double weatherDelay, double NASDelay, double securityDelay, double lateAircraftDelay) {
        this->year = year;
        this->month = month;
        this->carrier = carrier;
        this->carrierName = carrierName;
        this->airport = airport;
        this->airportName = airportName;
        this->arrivingFlights = arrivingFlights;
        this->delayedFlights = delayedFlights;
        this->cancelled = cancelled;
        this->diverted = diverted;
        this->totalDelay = totalDelay;
        this->carrierDelay = carrierDelay;
        this->weatherDelay = weatherDelay;
        this->NASDelay = NASDelay;
        this->securityDelay = securityDelay;
        this->lateAircraftDelay = lateAircraftDelay;
    }

    //Getter functions for private variables
    string getYear() {
        return year;
    }

    int getMonth() {
        return month;
    }

    string getCarrier() {
        return carrier;
    }

    string getCarrierName() {
        return carrierName;
    }

    string getAirport() {
        return airport;
    }

    string getAirportName() {
        return airportName;
    }

    double getArrivingFlights() {
        return arrivingFlights;
    }

    double getDelayedFlights() {
        return delayedFlights;
    }

    double getCancelledFlights() {
        return cancelled;
    }

    double getDivertedFlights() {
        return diverted;
    }

    double getTotalDelay() {
        return totalDelay;
    }

    double getCarrierDelay() {
        return carrierDelay;
    }

    double getWeatherDelay() {
        return weatherDelay;
    }

    double getNASDelay() {
        return NASDelay;
    }

    double getSecurityDelay() {
        return securityDelay;
    }

    double getLateAircraftDelay() {
        return lateAircraftDelay;
    }

    //Prints all data on one line
    void print() {
        cout << year << " " << month << " " << carrier << " " << carrierName << " " << airport << " " << airportName << " " << arrivingFlights << " " << delayedFlights << " " << cancelled << " " << diverted << " " << totalDelay << " " << carrierDelay << " " << weatherDelay << " " << NASDelay << " " << securityDelay << " " << lateAircraftDelay << " " << endl;
    }
};