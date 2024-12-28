#include<bits/stdc++.h>
using namespace std;

// Define the Transport class
class Transport {
public:
    string name;
    int dailyRidership;

    // Constructor
    Transport(string n, int ridership) : name(n), dailyRidership(ridership) {}
};

// Merge function to combine two sorted subarrays
void merge(vector<Transport>& transports, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors for left and right halves
    vector<Transport> leftArr, rightArr;

    for (int i = 0; i < n1; i++)
        leftArr.push_back(transports[left + i]);
    for (int i = 0; i < n2; i++)
        rightArr.push_back(transports[mid + 1 + i]);

    // Merge the temporary arrays back into the original vector
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].dailyRidership <= rightArr[j].dailyRidership) {
            transports[k++] = leftArr[i++];
        } else {
            transports[k++] = rightArr[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1)
        transports[k++] = leftArr[i++];
    while (j < n2)
        transports[k++] = rightArr[j++];
}

// Merge Sort function
void mergeSort(vector<Transport>& transports, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(transports, left, mid);
        mergeSort(transports, mid + 1, right);

        merge(transports, left, mid, right);
    }
}

// Function to print the sorted transports
void printTransports(const vector<Transport>& transports) {
    cout << "Sorted Transports by Daily Ridership:" << endl;
    for (const auto& transport : transports) {
        cout << transport.name << " with daily ridership " << transport.dailyRidership << endl;
    }
}

void one() {
    vector<Transport> transports = {
        Transport("Bus A", 300),
        Transport("Van B", 120),
        Transport("Train C", 1500),
        Transport("Bus D", 450)
    };

    // Perform Merge Sort
    mergeSort(transports, 0, transports.size() - 1);

    // Print the sorted transports
    printTransports(transports);

}

// Define the Transport structure
struct Transport1 {
    string name;
    int dailyRidership;
};

// Merge function to combine two sorted subarrays
void merge(Transport1 transports[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays for left and right halves
    Transport1 leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = transports[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = transports[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2) {
        if (leftArr[i].dailyRidership <= rightArr[j].dailyRidership) {
            transports[k++] = leftArr[i++];
        } else {
            transports[k++] = rightArr[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1)
        transports[k++] = leftArr[i++];
    while (j < n2)
        transports[k++] = rightArr[j++];
}

// Merge Sort function
void mergeSort(Transport1 transports[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(transports, left, mid);
        mergeSort(transports, mid + 1, right);

        merge(transports, left, mid, right);
    }
}

// Function to print the sorted transports
void printTransports(Transport1 transports[], int n) {
    cout << "Sorted Transports by Daily Ridership:" << endl;
    for (int i = 0; i < n; i++) {
        cout << transports[i].name << " with daily ridership " << transports[i].dailyRidership << endl;
    }
}

// Main function
void two() {
    // Initialize the transport data
    Transport1 transports[] = {
        {"Bus A", 300},
        {"Van B", 120},
        {"Train C", 1500},
        {"Bus D", 450}
    };

    int n = sizeof(transports) / sizeof(transports[0]);

    // Perform Merge Sort
    mergeSort(transports, 0, n - 1);

    // Print the sorted transports
    printTransports(transports, n);

   
}



struct Transaction {
    string type;
    double amount;
    string timestamp;
    Transaction* next;
    Transaction* prev;
};

class FareCollector {
private:
    Transaction* head;
    Transaction* tail;
    double totalParkingFare;
    double totalTollFare;

public:
    FareCollector() : head(nullptr), tail(nullptr), totalParkingFare(0), totalTollFare(0) {}


    void addTransaction(const string& type, double amount, const string& timestamp) {
        Transaction* newTransaction = new Transaction{type, amount, timestamp, nullptr, nullptr};

        if (type == "Parking") {
            totalParkingFare += amount;
        } else if (type == "Toll") {
            totalTollFare += amount;
        }

        if (!head) {
            head = tail = newTransaction;
        } else {
            tail->next = newTransaction;
            newTransaction->prev = tail;
            tail = newTransaction;
        }
    }

    void displayTransactions() const {
        if (!head) {
            cout << "No transactions recorded.\n";
            return;
        }

        cout << left << setw(15) << "Type" << setw(10) << "Amount (₹)" << setw(20) << "Timestamp" << endl;
        cout << string(45, '-') << endl;

        Transaction* current = head;
        while (current) {
            cout << left << setw(15) << current->type
                 << setw(10) << current->amount
                 << setw(20) << current->timestamp << endl;
            current = current->next;
        }
    }

    void displayTotalFare() const {
        cout << "\nTotal Parking Fare: ₹" << totalParkingFare << endl;
        cout << "Total Toll Fare: ₹" << totalTollFare << endl;
        cout << "Grand Total Fare: ₹" << (totalParkingFare + totalTollFare) << endl;
    }

    ~FareCollector() {
        Transaction* current = head;
        while (current) {
            Transaction* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

void three() {
    FareCollector fareCollector;

    fareCollector.addTransaction("Parking", 50.0, "2024-12-25 10:00");
    fareCollector.addTransaction("Toll", 30.0, "2024-12-25 10:15");
    fareCollector.addTransaction("Parking", 20.0, "2024-12-25 11:00");
    fareCollector.addTransaction("Toll", 40.0, "2024-12-25 11:30");

    cout << "Transaction Details:\n";
    fareCollector.displayTransactions();

    fareCollector.displayTotalFare();

}


struct Transaction1 {
    string type;
    double amount;
    string timestamp;
    Transaction1* next;
    Transaction1* prev;
};

class FareCollector1 {
private:
    Transaction1* head;
    Transaction1* tail;

public:

    FareCollector1() : head(nullptr), tail(nullptr) {}

    void addTransaction(const string& type, double amount, const string& timestamp) {
        Transaction1* newTransaction = new Transaction1{type, amount, timestamp, nullptr, nullptr};

        if (!head) {
            head = tail = newTransaction;
        } else {
            tail->next = newTransaction;
            newTransaction->prev = tail;
            tail = newTransaction;
        }
    }

    vector<double> extractFares() const {
        vector<double> fares;
        Transaction1* current = head;
        while (current) {
            fares.push_back(current->amount);
            current = current->next;
        }
        return fares;
    }

    void heapify(vector<double>& fares, int n, int i) {
        int largest = i;  // Initialize the largest as root
        int left = 2 * i + 1;  // Left child
        int right = 2 * i + 2; // Right child

        if (left < n && fares[left] > fares[largest]) {
            largest = left;
        }

        if (right < n && fares[right] > fares[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(fares[i], fares[largest]);

            heapify(fares, n, largest);
        }
    }

    void heapSort(vector<double>& fares) {
        int n = fares.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(fares, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            // Move the current root to the end
            swap(fares[0], fares[i]);

            heapify(fares, i, 0);
        }
    }

    void displaySortedFares() {
        vector<double> fares = extractFares();

        if (fares.empty()) {
            cout << "No fares to sort.\n";
            return;
        }

        heapSort(fares);

        cout << "\nSorted Fares (₹): ";
        for (double fare : fares) {
            cout << fare << " ";
        }
        cout << endl;
    }

      void displayTransactions() const {
        if (!head) {
            cout << "No transactions recorded.\n";
            return;
        }

        cout << left << setw(15) << "Type" << setw(10) << "Amount (₹)" << setw(20) << "Timestamp" << endl;
        cout << string(45, '-') << endl;

        Transaction1* current = head;
        while (current) {
            cout << left << setw(15) << current->type
                 << setw(10) << current->amount
                 << setw(20) << current->timestamp << endl;
            current = current->next;
        }
    }

    ~FareCollector1() {
        Transaction1* current = head;
        while (current) {
            Transaction1* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

void four() {
    FareCollector1 fareCollector;

    // Adding some sample transactions
    fareCollector.addTransaction("Parking", 50.0, "2024-12-25 10:00");
    fareCollector.addTransaction("Toll", 30.0, "2024-12-25 10:15");
    fareCollector.addTransaction("Parking", 20.0, "2024-12-25 11:00");
    fareCollector.addTransaction("Toll", 40.0, "2024-12-25 11:30");

    // Display transactions
    cout << "Transaction Details:\n";
    fareCollector.displayTransactions();

    // Display sorted fares
    fareCollector.displaySortedFares();

    
}


// Structure for a Node in the linked list (representing a section in the transport)
struct TransportSection {
    string ageGroup;        // Age group: Children, Adults, Senior Citizens
    int capacity;           // Number of passengers allowed in this section
    TransportSection* next; // Pointer to the next section in the transport

    TransportSection(string group, int cap) {
        ageGroup = group;
        capacity = cap;
        next = nullptr;
    }
};

// Class representing the Public Transport system
class PublicTransport {
private:
    TransportSection* head; // Head pointer to the linked list of sections

public:
    PublicTransport() {
        head = nullptr;
    }

    // Function to add a section for a particular age group
    void addSection(string group, int capacity) {
        TransportSection* newSection = new TransportSection(group, capacity);
        if (head == nullptr) {
            head = newSection; // If the list is empty, make the new section the head
        } else {
            TransportSection* temp = head;
            // Traverse to the last section in the linked list
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            // Link the new section at the end
            temp->next = newSection;
        }
    }

    // Function to display the sections of the transport and their capacities
    void displaySections() {
        if (head == nullptr) {
            cout << "No sections available." << endl;
            return;
        }
        
        TransportSection* temp = head;
        while (temp != nullptr) {
            cout << "Age Group: " << temp->ageGroup << " | Capacity: " << temp->capacity << endl;
            temp = temp->next;
        }
    }

    // Function to assign passengers to a particular age group
    void assignPassengersToAgeGroup(string group, int passengers) {
        TransportSection* temp = head;
        bool found = false;

        while (temp != nullptr) {
            if (temp->ageGroup == group) {
                found = true;
                if (temp->capacity >= passengers) {
                    temp->capacity -= passengers;
                    cout << passengers << " passengers assigned to the " << group << " section." << endl;
                } else {
                    cout << "Not enough capacity in the " << group << " section. Available capacity: " << temp->capacity << endl;
                }
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "Age group " << group << " not found in the transport system." << endl;
        }
    }

    // Destructor to free memory allocated for the linked list
    ~PublicTransport() {
        TransportSection* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void five() {
    PublicTransport transport;

    // Adding sections for different age groups
    transport.addSection("Children", 20);
    transport.addSection("Adults", 50);
    transport.addSection("Senior Citizens", 15);

    // Display the sections of the transport
    cout << "Current Transport Sections: " << endl;
    transport.displaySections();

    // Assign passengers to different age groups
    transport.assignPassengersToAgeGroup("Children", 5);
    transport.assignPassengersToAgeGroup("Adults", 10);
    transport.assignPassengersToAgeGroup("Senior Citizens", 3);
    transport.assignPassengersToAgeGroup("Children", 25); // This should show a capacity issue
    
}

// Class to represent a transport unit (e.g., Bus, Train)
class TransportUnit {
public:
    string id;
    string type; // Bus, Train, etc.
    string currentLocation;
    string nextStop;
    string scheduledTime;
    string status; // On time, Delayed, etc.

    TransportUnit(string id, string type, string currentLocation, string nextStop, string scheduledTime, string status) {
        this->id = id;
        this->type = type;
        this->currentLocation = currentLocation;
        this->nextStop = nextStop;
        this->scheduledTime = scheduledTime;
        this->status = status;
    }

    // Display transport details
    void displayInfo() {
        cout << "ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Current Location: " << currentLocation << endl;
        cout << "Next Stop: " << nextStop << endl;
        cout << "Scheduled Time: " << scheduledTime << endl;
        cout << "Status: " << status << endl;
    }
};

// Node of a Binary Search Tree to store TransportUnits
class TransportNode {
public:
    TransportUnit* transportUnit;
    TransportNode* left;
    TransportNode* right;

    TransportNode(TransportUnit* transportUnit) {
        this->transportUnit = transportUnit;
        left = right = nullptr;
    }
};

// Binary Search Tree for managing the transport units
class TransportTree {
private:
    TransportNode* root;

    // Helper function for insertion
    TransportNode* insert(TransportNode* node, TransportUnit* transportUnit) {
        if (node == nullptr) {
            return new TransportNode(transportUnit);
        }

        // Compare by transport unit ID
        if (transportUnit->id < node->transportUnit->id) {
            node->left = insert(node->left, transportUnit);
        } else if (transportUnit->id > node->transportUnit->id) {
            node->right = insert(node->right, transportUnit);
        }

        return node;
    }

    // Helper function for in-order traversal
    void inOrder(TransportNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            node->transportUnit->displayInfo();
            inOrder(node->right);
        }
    }

    // Helper function to search for a transport unit by ID
    TransportNode* search(TransportNode* node, string id) {
        if (node == nullptr || node->transportUnit->id == id) {
            return node;
        }

        if (id < node->transportUnit->id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

public:
    TransportTree() {
        root = nullptr;
    }

    // Insert a transport unit
    void insert(TransportUnit* transportUnit) {
        root = insert(root, transportUnit);
    }

    // Display all transport units in sorted order by ID
    void displayAll() {
        inOrder(root);
    }

    // Search for a transport unit by ID
    TransportUnit* search(string id) {
        TransportNode* result = search(root, id);
        if (result != nullptr) {
            return result->transportUnit;
        }
        return nullptr;
    }

    // Update transport status
    void updateStatus(string id, string newStatus) {
        TransportUnit* unit = search(id);
        if (unit != nullptr) {
            unit->status = newStatus;
        } else {
            cout << "Transport unit with ID " << id << " not found!" << endl;
        }
    }
};

void six() {
    TransportTree tree;

    // Add some transport units
    tree.insert(new TransportUnit("B001", "Bus", "Station A", "Station B", "08:30 AM", "On Time"));
    tree.insert(new TransportUnit("T001", "Train", "Station X", "Station Y", "09:00 AM", "Delayed"));
    tree.insert(new TransportUnit("B002", "Bus", "Station B", "Station C", "09:15 AM", "On Time"));
    tree.insert(new TransportUnit("T002", "Train", "Station Z", "Station A", "08:45 AM", "On Time"));

    cout << "Displaying all transport units:\n";
    tree.displayAll();

    // Search for a transport unit by ID
    string searchID = "B001";
    TransportUnit* unit = tree.search(searchID);
    if (unit != nullptr) {
        cout << "\nDetails of Transport Unit " << searchID << ":\n";
        unit->displayInfo();
    } else {
        cout << "\nTransport unit with ID " << searchID << " not found!\n";
    }

    // Update the status of a transport unit
    tree.updateStatus("B002", "Delayed");
    cout << "\nAfter updating status of B002:\n";
    tree.displayAll();
 
}


struct Vehicle {
    string name;
    int pollution;
};

void heapify(vector<Vehicle>& vehicles, int n, int i) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2; 

 
    if (left < n && vehicles[left].pollution > vehicles[largest].pollution)
        largest = left;

    
    if (right < n && vehicles[right].pollution > vehicles[largest].pollution)
        largest = right;

    if (largest != i) {
        swap(vehicles[i], vehicles[largest]);
      
        heapify(vehicles, n, largest);
    }
}


void heapSort(vector<Vehicle>& vehicles) {
    int n = vehicles.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vehicles, n, i);

    for (int i = n - 1; i > 0; i--) {
        
        swap(vehicles[0], vehicles[i]);
      
        heapify(vehicles, i, 0);
    }
}

void seven() {

    vector<Vehicle> vehicles = {
        {"Passenger Cars", 45},
        {"Light-Duty Trucks", 20},
        {"Heavy-Duty Trucks", 15},
        {"Motorcycles", 5},
        {"Buses", 5},
        {"Agricultural Equipment", 3},
        {"Aviation", 5},
        {"Marine Vessels", 2}
    };

  
    heapSort(vehicles);

  
    cout << "Vehicles sorted by pollution contribution (highest to lowest):\n";
    for (const auto& vehicle : vehicles) {
        cout << vehicle.name << " | " << vehicle.pollution << "%\n";
    }

}


struct PaymentNode {
    string type; // Payment type (e.g., credit, debit, UPI, etc.)
    vector<pair<PaymentNode*, int>> connections; // Connections to other payment types and their costs
};

class PaymentGraph {
private:
    unordered_map<string, PaymentNode*> nodes;

public:
    void addPaymentType(const string& type) {
        if (nodes.find(type) == nodes.end()) {
            nodes[type] = new PaymentNode{type, {}};
        }
    }

    void addConnection(const string& from, const string& to, int cost) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            nodes[from]->connections.push_back({nodes[to], cost});
        }
    }

    void findShortestPath(const string& start, const string& end) {
        if (nodes.find(start) == nodes.end() || nodes.find(end) == nodes.end()) {
            cout << "Payment types not found in the graph.\n";
            return;
        }

        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        for (const auto& node : nodes) {
            distances[node.first] = INT_MAX;
        }
        distances[start] = 0;

        auto compare = [](pair<int, PaymentNode*> a, pair<int, PaymentNode*> b) {
            return a.first > b.first;
        };
        priority_queue<pair<int, PaymentNode*>, vector<pair<int, PaymentNode*>>, decltype(compare)> pq(compare);
        pq.push({0, nodes[start]});

        while (!pq.empty()) {
            auto [currentDistance, currentNode] = pq.top();
            pq.pop();

            for (const auto& [neighbor, cost] : currentNode->connections) {
                int newDistance = currentDistance + cost;
                if (newDistance < distances[neighbor->type]) {
                    distances[neighbor->type] = newDistance;
                    previous[neighbor->type] = currentNode->type;
                    pq.push({newDistance, neighbor});
                }
            }
        }

        if (distances[end] == INT_MAX) {
            cout << "No path found from " << start << " to " << end << ".\n";
            return;
        }

        cout << "Shortest path from " << start << " to " << end << ":\n";
        string current = end;
        vector<string> path;
        while (current != start) {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        for (const string& step : path) {
            cout << step << (step == end ? "\n" : " -> ");
        }
        cout << "Total cost: " << distances[end] << "\n";
    }

    ~PaymentGraph() {
        for (auto& node : nodes) {
            delete node.second;
        }
    }
};

void eight() {
    PaymentGraph paymentSystem;

    
    paymentSystem.addPaymentType("Credit");
    paymentSystem.addPaymentType("Debit");
    paymentSystem.addPaymentType("UPI");
    paymentSystem.addPaymentType("NetBanking");
    paymentSystem.addPaymentType("Wallet");

   
    paymentSystem.addConnection("Credit", "Debit", 2);
    paymentSystem.addConnection("Credit", "UPI", 1);
    paymentSystem.addConnection("Debit", "NetBanking", 1);
    paymentSystem.addConnection("UPI", "Wallet", 2);
    paymentSystem.addConnection("NetBanking", "Wallet", 1);

    // Find shortest path for a transaction
    paymentSystem.findShortestPath("Debit", "NetBanking");

}










int main() {
    int n ; cout << "Enter your choice\n" ;
    cin >> n ;
    switch(n) {
        case 1 : {one() ; break ; }
        case 2 : {two() ;  break ; }
        case 3 : {three() ; break ; }
        case 4 : {four() ; break ; }
        case 5 : {five() ; break ; }
        case 6 : {six() ; break ; }
        case 7 : {seven() ; break ; }
        case 8 : {eight() ;break ; }
        default : {
            cout << "Invalid Choice\n" ;
            exit(0) ;
        }
    } 

}