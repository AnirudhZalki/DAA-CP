#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


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

int main() {
    FareCollector fareCollector;

    fareCollector.addTransaction("Parking", 50.0, "2024-12-25 10:00");
    fareCollector.addTransaction("Toll", 30.0, "2024-12-25 10:15");
    fareCollector.addTransaction("Parking", 20.0, "2024-12-25 11:00");
    fareCollector.addTransaction("Toll", 40.0, "2024-12-25 11:30");

    cout << "Transaction Details:\n";
    fareCollector.displayTransactions();

    fareCollector.displayTotalFare();

    return 0;
}
