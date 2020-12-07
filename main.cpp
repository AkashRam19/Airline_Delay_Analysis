/*
* Project 3: Airline Delay Detection System
* main.cpp
* 
* Team: Runtime Terrors
* Members: Chirag Narang, Keyur Patel, Akash Ram
* 
* References:
*  - https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
*  - Lecture slides
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include "Flight.cpp"


//Global Map Variable, Maps month name with month number
unordered_map<string, int> monthAbrev = {
    {"January", 1},
    {"February", 2},
    {"March", 3},
    {"April", 4},
    {"May", 5},
    {"June", 6},
    {"July", 7},
    {"August", 8},
    {"September", 9},
    {"October", 10},
    {"November", 11},
    {"December", 12}
};

//Global Airline Variable, Maps airline code with airline name
unordered_map<string, string> airlines = {
    {"TZ","ATA Airlines"},
    {"FL","AirTran Airways"},
    {"AS","Alaska Airlines"},
    {"G4","Allegiant Air"},
    {"AQ","Aloha Airlines"},
    {"HP","America West Airlines"},
    {"AA","American Airlines"},
    {"MQ","American Eagle Airlines"},
    {"DH","Atlantic Coast Airlines"},
    {"EV","Atlantic Southeast Airlines"},
    {"OH","Comair"},
    {"CO","Continential Airlines"},
    {"DL","Delta Airlines"},
    {"9E","Endeavor Air"},
    {"MQ","Enovy Air"},
    {"EV","ExpressJet Airlines"},
    {"XE","ExpressJet Airlines"},
    {"F9","Frontier Airlines"},
    {"HA","Hawaiian Airlines"},
    {"DH","Independence Air"},
    {"B6","JetBlue Airways"},
    {"YV","Mesa Airlines"},
    {"NW","Northwest Airlines"},
    {"YX","Republic Airlines"},
    {"OO","Skywest Airlines"},
    {"WN","Southwest Airlines"},
    {"NK","Spirit Airlines"},
    {"US","US Airways"},
    {"UA","United Airlines"},
    {"VX","Virgin America"}
};

/*
* Comparison Methods:
* Used to compare to data entries together.
*/

//Methods for comparing two flights based on Airline, Airport, and Month
bool isGreaterAirline(Flight f1, Flight f2) {
    if (f1.getCarrier() > f2.getCarrier()) {
        return true;
    }
    else if (f1.getCarrier() == f2.getCarrier()) {
        if (f1.getAirport() > f2.getAirport()) {
            return true;
        }
        else if (f1.getAirport() == f2.getAirport()) {
            if (f1.getMonth() > f2.getMonth()) {
                return true;
            }
        }
    }
    return false;
}

//Method for comparing two flights based on Airport, Airline, and Month
bool isGreaterAirport(Flight f1, Flight f2) {
    if (f1.getAirport() > f2.getAirport()) {
        return true;
    }
    else if (f1.getAirport() == f2.getAirport()) {
        if (f1.getCarrier() > f2.getCarrier()) {
            return true;
        }
        else if (f1.getCarrier() == f2.getCarrier()) {
            if (f1.getMonth() > f2.getMonth()) {
                return true;
            }
        }
    }
    return false;
}

//Method for comparing two flights based on Month, Airline, and Airport
bool isGreaterMonth(Flight f1, Flight f2) {
    if (f1.getMonth() > f2.getMonth()) {
        return true;
    }
    else if (f1.getMonth() == f2.getMonth()) {
        if (f1.getCarrier() > f2.getCarrier()) {
            return true;
        }
        else if (f1.getCarrier() == f2.getCarrier()) {
            if (f1.getAirport() > f2.getAirport()) {
                return true;
            }
        }
    }
    return false;
}

/********************************************************************************************/

/*
* insertionSort()
* Completes an insertion sort of data.
* Input option controls if data is sorted by:
* 1. Airline
* 2. Airport
* 3. Month
* 
* Source: Lecture
*/
void insertionSort(vector<Flight>& data, int size, int option) {
    Flight key;
    int j;
    for (int i = 1; i < size; i++) {
        key = data.at(i);
        j = i - 1;

        switch (option) {
        case 1: {
            while (j >= 0 && isGreaterAirline(data.at(j), key)) {
                data.at(j + 1) = data.at(j);
                j--;
            }
            break;
        }
        case 2: {
            while (j >= 0 && isGreaterAirport(data.at(j), key)) {
                data.at(j + 1) = data.at(j);
                j--;
            }
            break;
        }
        case 3: {
            while (j >= 0 && isGreaterMonth(data.at(j), key)) {
                data.at(j + 1) = data.at(j);
                j--;
            }
            break;
        }
        }

        data.at(j + 1) = key;
        //cout << "insertion sort: iteration " << i << endl;
    }
}

/*
* heapifyAirport(), heapifyAirline(), heapifyMonth()
* Runs heapify based on airport, airline, or month
* Recursive method called until everything after root is in a heap structure.
* 
* Source: Lecture
*/
void heapifyAirport(vector<Flight>& data, int length, int root) {
    int smallest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    //if left child is smaller than the root
    if (leftChild < length && isGreaterAirport(data.at(leftChild), data.at(smallest))) {
        smallest = leftChild;
    }
    //if right child is smaller than the root
    if (rightChild < length && isGreaterAirport(data.at(rightChild), data.at(smallest))) {
        smallest = rightChild;
    }
    //swap smallest with the root if they are not the same
    if (smallest != root) {
        Flight temp = data.at(root);
        data.at(root) = data.at(smallest);
        data.at(smallest) = temp;

        //repeat on the subtree
        heapifyAirport(data, length, smallest);
    }
}

void heapifyAirline(vector<Flight>& data, int length, int root) {
    int smallest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    //if left child is smaller than the root
    if (leftChild < length && isGreaterAirline(data.at(leftChild), data.at(smallest))) {
        smallest = leftChild;
    }
    //if right child is smaller than the root
    if (rightChild < length && isGreaterAirline(data.at(rightChild), data.at(smallest))) {
        smallest = rightChild;
    }
    //swap smallest with the root if they are not the same
    if (smallest != root) {
        Flight temp = data.at(root);
        data.at(root) = data.at(smallest);
        data.at(smallest) = temp;

        //repeat on the subtree
        heapifyAirline(data, length, smallest);
    }
}

void heapifyMonth(vector<Flight>& data, int length, int root) {
    int smallest = root;
    int leftChild = 2 * root + 1;
    int rightChild = 2 * root + 2;

    //if left child is smaller than the root
    if (leftChild < length && isGreaterMonth(data.at(leftChild), data.at(smallest))) {
        smallest = leftChild;
    }
    //if right child is smaller than the root
    if (rightChild < length && isGreaterMonth(data.at(rightChild), data.at(smallest))) {
        smallest = rightChild;
    }
    //swap smallest with the root if they are not the same
    if (smallest != root) {
        Flight temp = data.at(root);
        data.at(root) = data.at(smallest);
        data.at(smallest) = temp;

        //repeat on the subtree
        heapifyMonth(data, length, smallest);
    }
}


/*
* heapSort()
* Completes a heap sort of data. Calls heapify to build heap in place, and then sorts data. 
* Input option controls if data is sorted by:
* 1. Airline
* 2. Airport
* 3. Month
* 
* Source: Lecture
*/
void heapSort(vector<Flight>& data, int size, int option) {
    //rearrange the vector to form a heap
    for (int i = size / 2; i >= 0; i--) {
        switch (option) {
        case 1:
            heapifyAirline(data, size, i);
            break;
        case 2:
            heapifyAirport(data, size, i);
            break;
        case 3:
            heapifyMonth(data, size, i);
            break;
        }
    }

    //remove elements from heap
    for (int i = size - 1; i > 0; i--) {
        //move current root to the end of the vector
        Flight temp = data.at(i);
        data.at(i) = data.at(0);
        data.at(0) = temp;

        //call heapify on the smaller vector
        switch (option) {
        case 1:
            heapifyAirline(data, i, 0);
            break;
        case 2:
            heapifyAirport(data, i, 0);
            break;
        case 3:
            heapifyMonth(data, i, 0);
            break;
        }
    }
}

/*
* partitionAirline(), partitionAirport(), partitionMonth()
* Runs parition function iteratively. Move all values below partition value above, and all
* values below parition, above. Returns the index of partition. 
*
* Source: Lecture
*/
int partitionAirline(vector<Flight>& flights, int low, int high) {
    Flight pivot = flights[low];
    int up = low;
    int down = high;

    //Swaps values above and below
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (isGreaterAirline(flights[up], pivot))
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (isGreaterAirline(pivot, flights[down]))
                break;
            down--;
        }
        if (up < down) {
            Flight temp = flights[up];
            flights[up] = flights[down];
            flights[down] = temp;
        }
    }

    Flight temp = flights[low];
    flights[low] = flights[down];
    flights[down] = temp;
    return down;
}

int partitionAirport(vector<Flight>& flights, int low, int high) {
    Flight pivot = flights[low];
    int up = low;
    int down = high;

    //Swaps values above and below
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (isGreaterAirport(flights[up], pivot))
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (isGreaterAirport(pivot, flights[down]))
                break;
            down--;
        }
        if (up < down) {
            Flight temp = flights[up];
            flights[up] = flights[down];
            flights[down] = temp;
        }
    }

    Flight temp = flights[low];
    flights[low] = flights[down];
    flights[down] = temp;
    return down;
}

int partitionMonth(vector<Flight>& flights, int low, int high) {
    Flight pivot = flights[low];
    int up = low;
    int down = high;

    //Swaps values above and below
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (isGreaterMonth(flights[up], pivot))
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (isGreaterMonth(pivot, flights[down]))
                break;
            down--;
        }
        if (up < down) {
            Flight temp = flights[up];
            flights[up] = flights[down];
            flights[down] = temp;
        }
    }

    Flight temp = flights[low];
    flights[low] = flights[down];
    flights[down] = temp;
    return down;
}

/*
* quickSort()
* Completes a quick sort of data. Calls partition function based on input.
* Recursively quicksorts above and below pivot, until data is sorted
* Input option controls if data is sorted by:
* 1. Airline
* 2. Airport
* 3. Month
*
* Source: Lecture
*/
void quickSort(vector<Flight>& flights, int low, int high, int option) {
    if (low < high) {
        int pivot;
        switch (option) {
        case 1:
            pivot = partitionAirline(flights, low, high);
            break;
        case 2:
            pivot = partitionAirport(flights, low, high);
            break;
        case 3:
            pivot = partitionMonth(flights, low, high);
            break;
        }
        quickSort(flights, low, pivot - 1, option);
        quickSort(flights, pivot + 1, high, option);
    }
}

/*
* merge()
* Merges two subvectors of the original vector using start, mid and end as markers
* for the sections to merge
* Input option controls if data is sorted by:
* 1. Airline
* 2. Airport
* 3. Month
*
* Source: Lecture
*/
void merge(vector<Flight>& flights, int start, int mid, int end, int option) {
    //Creates the two subvectors to be merged, leftHalf and rightHalf
    int left = mid - start + 1;
    int right = end - mid;

    vector<Flight> leftHalf, rightHalf;

    for (int i = 0; i < left; i++) {
        leftHalf.push_back(flights.at(start + i));
    }
    for (int j = 0; j < right; j++) {
        rightHalf.push_back(flights.at(mid + 1 + j));
    }

    //Merges the two subvectors into the original vector by comparing the elements of the two vectors
    //and adding the smaller one to the original vector
    int i, j, k;
    i = 0;
    j = 0;
    k = start;

    while (i < left && j < right) {
        bool compare;
        //Controls sorting option
        switch (option) {
        case 1:
            compare = isGreaterAirline(leftHalf.at(i), rightHalf.at(j));
            break;
        case 2:
            compare = isGreaterAirport(leftHalf.at(i), rightHalf.at(j));
            break;
        case 3:
            compare = isGreaterMonth(leftHalf.at(i), rightHalf.at(j));
            break;
        }
        if (!compare) {
            flights[k] = leftHalf[i];
            i++;
        }
        else {
            flights[k] = rightHalf[j];
            j++;
        }
        k++;
    }

    //Adds the remainder of the values in leftHalf and rightHalf to the original vector
    while (i < left) {
        flights[k] = leftHalf[i];
        i++;
        k++;
    }

    while (j < right) {
        flights[k] = rightHalf[j];
        j++;
        k++;
    }
}


/*
* mergeSort()
* Find mid of data and runs merge sort on two halves, merges the two 
* arrays together.
* Input option controls if data is sorted by:
* 1. Airline
* 2. Airport
* 3. Month
*
* Source: Lecture
*/
void mergeSort(vector<Flight>& flights, int start, int end, int option) {
    if (start < end) {
        int mid = start + (end - start) / 2;

        mergeSort(flights, start, mid, option);
        mergeSort(flights, mid + 1, end, option);
        merge(flights, start, mid, end, option);
    }
}

//Prints Main Menu
void printMainMenu() {
    cout << "Select an Option:" << endl;
    cout << "1. View by Airline" << endl;
    cout << "2. View by Airport" << endl;
    cout << "3. View by Month" << endl;
    cout << "4. Compare Sorting Methods" << endl;
    cout << "5. Exit" << endl;
}

//Prints Sorting option menu
void printSubMenu() {
    cout << "Please select the sorting method:" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Quick Sort" << endl;
    cout << "3. Heap Sort" << endl;
    cout << "4. Merge Sort" << endl;
}

/*
* binarySearchAirline(), binarySearchAirport(), binarySearchMonth()
* Completes a binary search to find the desired flight in the data. 
* Then traverses up and down the data to find entire range of values that have the 
* desired search option. 
*
* Source: Lecture
*/
pair<int, int> binarySearchAirline(vector<Flight>& flights, string airline) {
    int first = 0;
    int mid;
    int last = flights.size() - 1;
    bool found = false;

    //Iterative Binary Search, breaks when mid is found or not in data
    while (first <= last) {
        mid = (first + last) / 2;
        if (flights[mid].getCarrier() == airline) {
            found = true;
            break;
        }
        else if (flights[mid].getCarrier() < airline) {
            first = mid + 1;
        }
        else {
            last = mid - 1;
        }
    }

    //Returns -1,-1 if not in data
    if (!found) return { -1,-1 };

    //Traverses up and down data to find entire range
    int index = mid;
    while (index >= 0 && flights[index].getCarrier() == airline) {
        index--;
    }
    int start = index;

    index = mid;
    while (index < flights.size() && flights[index].getCarrier() == airline) {
        index++;
    }
    int end = index;

    return { start + 1, end };
}

pair<int, int> binarySearchAirport(vector<Flight>& flights, string airport) {
    int first = 0;
    int mid;
    int last = flights.size() - 1;
    bool found = false;

    //Iterative Binary Search, breaks when mid is found or not in data
    while (first <= last) {
        mid = (first + last) / 2;
        if (flights[mid].getAirport() == airport) {
            found = true;
            break;
        }
        else if (flights[mid].getAirport() < airport) {
            first = mid + 1;
        }
        else {
            last = mid - 1;
        }
    }

    //Returns -1,-1 if not in data
    if (!found) return { -1,-1 };

    //Traverses up and down data to find entire range
    int index = mid;
    while (index >= 0 && flights[index].getAirport() == airport) {
        index--;
    }
    int start = index;

    index = mid;
    while (index < flights.size() && flights[index].getAirport() == airport) {
        index++;
    }
    int end = index;

    return { start + 1, end };
}

pair<int, int> binarySearchMonth(vector<Flight>& flights, int month) {
    int first = 0;
    int mid;
    int last = flights.size() - 1;
    bool found = false;

    //Iterative Binary Search, breaks when mid is found or not in data
    while (first <= last) {
        mid = (first + last) / 2;
        if (flights[mid].getMonth() == month) {
            found = true;
            break;
        }
        else if (flights[mid].getMonth() < month) {
            first = mid + 1;
        }
        else {
            last = mid - 1;
        }
    }

    //Returns -1,-1 if not in data
    if (!found) return { -1,-1 };

    //Traverses up and down data to find entire range
    int index = mid;
    while (index >= 0 && flights[index].getMonth() == month) {
        index--;
    }
    int start = index;

    index = mid;
    while (index < flights.size() && flights[index].getMonth() == month) {
        index++;
    }
    int end = index;

    return { start + 1, end };
}

/*
* Given a vector of flights, returns a flight class that contains the total flights
* and delayed flights, as well as the average delay for all data in the vector
*/
Flight getAverage(vector<Flight>& flights) {
    double numFlights = 0;
    double numDelayedFlights = 0;
    double numCancelled = 0;
    double avgDelay = 0;
    double avgCarrierDelay = 0;
    double avgWeatherDelay = 0;
    double avgNASDelay = 0;
    double avgSecurityDelay = 0;
    double avgLateAircraftDelay = 0;
    for (auto line : flights) {
        numFlights += line.getArrivingFlights();
        numDelayedFlights += line.getDelayedFlights();
        numCancelled += line.getCancelledFlights();
        avgDelay += line.getTotalDelay();
        avgCarrierDelay += line.getCarrierDelay();
        avgWeatherDelay += line.getWeatherDelay();
        avgNASDelay += line.getNASDelay();
        avgSecurityDelay += line.getSecurityDelay();
        avgLateAircraftDelay += line.getLateAircraftDelay();
    }

    avgDelay /= numDelayedFlights;
    avgCarrierDelay /= numDelayedFlights;
    avgWeatherDelay /= numDelayedFlights;
    avgNASDelay /= numDelayedFlights;
    avgSecurityDelay /= numDelayedFlights;
    avgLateAircraftDelay /= numDelayedFlights;

    Flight average = Flight("", 0, "", "", "", "", numFlights, numDelayedFlights, numCancelled, 0, avgDelay, avgCarrierDelay, avgWeatherDelay, avgNASDelay, avgSecurityDelay, avgLateAircraftDelay);
    return average;
}

/*
* Prints average flight based on class structure from getAverage() class
* Print data with correct spacing
*/
void printAverage(Flight average) {
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "Total Flights: " << (int)average.getArrivingFlights() << endl << endl;
    cout << "Delayed Flight: " << (int)average.getDelayedFlights() << endl;
    cout << "Percent of Delayed Flights: " << average.getDelayedFlights() / average.getArrivingFlights() * 100 << "%" << endl << endl;
    cout << "Cancelled Flights: " << (int)average.getCancelledFlights() << endl;
    cout << "Percent of Cancelled Flights: " << average.getCancelledFlights() / average.getArrivingFlights() * 100 << "%" << endl;
    cout << endl;

    cout << "Delay Information Breakdown (minutes)" << endl;
    cout << "Average Delay: " << average.getTotalDelay() << endl;
    cout << "Carrier: " << average.getCarrierDelay() << endl;
    cout << "Weather: " << average.getWeatherDelay() << endl;
    cout << "NAS: " << average.getNASDelay() << endl;
    cout << "Security: " << average.getSecurityDelay() << endl;
    cout << "Late Aircraft: " << average.getLateAircraftDelay() << endl;
}

int main() {
    //Gathers input and opens file
    string filename;
    cout << "Enter in data loction: ";
    cin >> filename;
    fstream input;
    input.open(filename, ios::in);

    //create a vector to store the flight objects
    vector<Flight> data;
    string read;
    getline(input, read);

    //Store variable data from file
    string year;
    string month;
    string carrier;
    string carrierName;
    string airport;
    string airportName;
    string arrivingFlights;
    string delayedFlights;
    string cancelled;
    string diverted;
    string totalDelay;
    string carrierDelay;
    string weatherDelay;
    string NASDelay;
    string securityDelay;
    string lateAircraftDelay;

    //Reads in Entire file
    while (getline(input, year, ',')) {
        getline(input, month, ',');
        if (month == "") {
            month = "0";
        }
        getline(input, carrier, ',');
        if (carrier == "") {
            carrier = "0.0";
        }
        getline(input, carrierName, ',');
        if (carrierName == "") {
            carrierName = "0.0";
        }
        getline(input, airport, ',');
        if (airport == "") {
            airport = "0.0";
        }

        //Airport Name Formatting
        getline(input, airportName, ',');
        string temp;
        getline(input, temp, ',');
        airportName = airportName + temp;

        getline(input, arrivingFlights, ',');
        if (arrivingFlights == "") {
            arrivingFlights = "0.0";
        }
        getline(input, delayedFlights, ',');
        if (delayedFlights == "") {
            delayedFlights = "0.0";
        }

        //Unused Data
        getline(input, read, ',');
        getline(input, read, ',');
        getline(input, read, ',');
        getline(input, read, ',');
        getline(input, read, ',');

        getline(input, cancelled, ',');
        if (cancelled == "") {
            cancelled = "0.0";
        }

        getline(input, diverted, ',');
        if (diverted == "") {
            diverted = "0.0";
        }

        getline(input, totalDelay, ',');
        if (totalDelay == "") {
            totalDelay = "0.0";
        }

        getline(input, carrierDelay, ',');
        if (carrierDelay == "") {
            carrierDelay = "0.0";
        }

        getline(input, weatherDelay, ',');
        if (weatherDelay == "") {
            weatherDelay = "0.0";
        }

        getline(input, NASDelay, ',');
        if (NASDelay == "") {
            NASDelay = "0.0";
        }

        getline(input, securityDelay, ',');
        if (securityDelay == "") {
            securityDelay = "0.0";
        }

        getline(input, lateAircraftDelay, ',');
        if (lateAircraftDelay == "") {
            lateAircraftDelay = "0.0";
        }

        getline(input, temp);

        //Stores in vector
        data.push_back(Flight(year, stoi(month), carrier, carrierName, airport, airportName, stod(arrivingFlights), stod(delayedFlights), stod(cancelled), stod(diverted), stod(totalDelay), stod(carrierDelay), stod(weatherDelay), stod(NASDelay), stod(securityDelay), stod(lateAircraftDelay)));
    }

    input.close();
    auto copy = data;

    //Print UI
    cout << "Welcome to Airline Delay Anlaysis" << endl << endl;
    string option;
    bool exit = false;

    //Loops while user has not exited program
    while (!exit) {
        //Resets data each loop (unsorts) and takes in Main Menu Input
        printMainMenu();
        int option = 0;
        int suboption = 0;
        cout << "Input: ";
        cin >> option;
        cout << endl;
        data = copy;

        switch (option) {
        case 1:
        case 2:
        case 3: {
            //Times sorting funciton calls based on subopton input
            printSubMenu();
            cout << "Input: ";
            cin >> suboption;
            cout << endl;

            //Sorts based on based on option: 1-Airline, 2-Airport, 3-Month
            //Sorting method based on suboption: 1-Insertion, 2-Quick, 3-Heap, 4-Merge
            switch (suboption) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                insertionSort(data, data.size(), option);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Insertion sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl << endl;
                break;
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                quickSort(data, 0, data.size() - 1, option);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Quick sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl << endl;
                break;
            }
            case 3: {
                auto start = std::chrono::high_resolution_clock::now();
                heapSort(data, data.size(), option);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Heap sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl << endl;
                break;
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                mergeSort(data, 0, data.size() - 1, option);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Merge sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl << endl;
                break;
            }
            default:
                cout << "Please enter a valid option!" << endl;
            }

            //Takes in user input for searching the data based on 1-Airline, 2-Airport, 3-Month
            pair<int, int> search;
            switch (option) {
            case 1: {
                cout << "Please enter an Airline to search by (abbreviation): ";
                string airline;
                cin >> airline;
                string airlineName = airlines[airline];
                if (airlineName == "") airlineName = "DNE";
                airline = "\"" + airline + "\"";
                search = binarySearchAirline(data, airline);
                cout << "Displaying delay data for airline: " << airlineName << endl;
                break;
            }
            case 2: {
                cout << "Please enter an Airport to search by (abbreviation): ";
                string airport;
                cin >> airport;
                airport = "\"" + airport + "\"";
                search = binarySearchAirport(data, airport);
                cout << "Displaying delay data for airport: " << airport << endl;
                break;
            }
            case 3: {
                cout << "Please enter a Month to search by: ";
                string month;
                cin >> month;
                int m = monthAbrev[month];
                search = binarySearchMonth(data, m);
                cout << "Displaying delay data for month: " << month << endl;
                break;
            }
            }

            //If data found, creates a data of total search results
            if (search.first != -1) {
                auto begin = data.begin() + search.first;
                auto end = data.begin() + search.second;
                vector<Flight> searchResults(begin, end);

                //Calculates Average of Data and print information
                Flight average = getAverage(searchResults);
                printAverage(average);
                cout << endl;
            }
            else {
                cout << "Does not exist in data given. Sorry!" << endl << endl;
            }

            break;
        }
        case 4: {
            //Times all sorting methods one after another
            //Resets data after each sorting method is ran
            cout << "Choose sorting option:" << endl;
            cout << "1. Sort by Airline" << endl;
            cout << "2. Sort by Airport" << endl;
            cout << "3. Sort by Month" << endl;
            cout << "Input: ";
            int choice;
            cin >> choice;
            cout << endl;
            if (choice == 1 || choice == 2 || choice == 3) {
                data = copy;
                auto start = std::chrono::high_resolution_clock::now();
                insertionSort(data, data.size(), choice);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Insertion sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl;

                data = copy;
                start = std::chrono::high_resolution_clock::now();
                quickSort(data, 0, data.size() - 1, choice);
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Quick sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl;

                data = copy;
                start = std::chrono::high_resolution_clock::now();
                heapSort(data, data.size(), choice);
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Heap sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl;

                data = copy;
                start = std::chrono::high_resolution_clock::now();
                mergeSort(data, 0, data.size() - 1, choice);
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Merge sort completed in " << duration.count() / 1000000.0 << " seconds!" << endl << endl;
            }
            else {
                cout << "Invalid Option" << endl;
            }

            break;
        }
        case 5: {
            exit = true;
            cout << "Thank you for using this program. Bye!" << endl;
            break;
        }
        default:
            cout << "Please enter a valid option!" << endl;
        }
    }
}