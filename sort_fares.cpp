#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

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

public:

    FareCollector() : head(nullptr), tail(nullptr) {}

    void addTransaction(const string& type, double amount, const string& timestamp) {
        Transaction* newTransaction = new Transaction{type, amount, timestamp, nullptr, nullptr};

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
        Transaction* current = head;
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

        Transaction* current = head;
        while (current) {
            cout << left << setw(15) << current->type
                 << setw(10) << current->amount
                 << setw(20) << current->timestamp << endl;
            current = current->next;
        }
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

    return 0;
}
