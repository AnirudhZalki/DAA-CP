#include <bits/stdc++.h>
using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string timestamp;

public:
    Transaction(const string& t, double a, const string& ts) : type(t), amount(a), timestamp(ts) {}

    string getType() const { return type; }
    double getAmount() const { return amount; }
    string getTimestamp() const { return timestamp; }
};

class FareCollector {
private:
    vector<Transaction> transactions;

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
            swap(fares[0], fares[i]);
            heapify(fares, i, 0);
        }
    }

public:
    void addTransaction(const string& type, double amount, const string& timestamp) {
        transactions.emplace_back(type, amount, timestamp);
    }

    void displayTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions recorded.\n";
            return;
        }

        cout << left << setw(15) << "Type" << setw(10) << "Amount (₹)" << (20) << "Timestamp" << endl;
        cout << string(45, '-') << endl;

        for (const auto& transaction : transactions) {
            cout << left << setw(15) << transaction.getType()
                 << setw(10) << transaction.getAmount()
                 << setw(20) << transaction.getTimestamp() << endl;
        }
    }

    void displaySortedFares() {
        if (transactions.empty()) {
            cout << "No fares to sort.\n";
            return;
        }

        vector<double> fares;
        for (const auto& transaction : transactions) {
            fares.push_back(transaction.getAmount());
        }

        heapSort(fares);

        cout << "\nSorted Fares (\u20B9): ";
        for (double fare : fares) {
            cout << fare << " ";
        }
        cout << endl;
    }
};

int main() {
    FareCollector fareCollector;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Transaction\n";
        cout << "2. Display Transactions\n";
        cout << "3. Display Sorted Fares\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string type, timestamp;
                double amount;

                cout << "Enter transaction type (e.g., Parking, Toll): ";
                cin.ignore(); // Clear input buffer
                getline(cin, type);

                cout << "Enter amount (\u20B9): ";
                cin >> amount;

                cout << "Enter timestamp (YYYY-MM-DD HH:MM): ";
                cin.ignore(); // Clear input buffer
                getline(cin, timestamp);

                fareCollector.addTransaction(type, amount, timestamp);
                break;
            }
            case 2:
                cout << "\nTransaction Details:\n";
                fareCollector.displayTransactions();
                break;

            case 3:
                fareCollector.displaySortedFares();
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
