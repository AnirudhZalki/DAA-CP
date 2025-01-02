#include<bits/stdc++.h>

using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string timestamp;
    Transaction* left;
    Transaction* right;

public:
    Transaction(const string& t, double a, const string& ts)
        : type(t), amount(a), timestamp(ts), left(nullptr), right(nullptr) {}

    friend class FareCollector;
};

class FareCollector {
private:
    Transaction* root;
    double totalParkingFare;
    double totalTollFare;

    void addTransactionHelper(Transaction*& node, const string& type, double amount, const string& timestamp) {
        if (!node) {
            node = new Transaction(type, amount, timestamp);
            if (type == "Parking") totalParkingFare += amount;
            else if (type == "Toll") totalTollFare += amount;
            return;
        }

        if (amount < node->amount) {
            addTransactionHelper(node->left, type, amount, timestamp);
        } else {
            addTransactionHelper(node->right, type, amount, timestamp);
        }
    }

    void displayTransactionsHelper(Transaction* node) const {
        if (!node) return;

        displayTransactionsHelper(node->left);
        cout << left << setw(15) << node->type
             << setw(10) << node->amount
             << setw(20) << node->timestamp << endl;
        displayTransactionsHelper(node->right);
    }

    void cleanup(Transaction* node) {
        if (!node) return;

        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }

public:
    FareCollector() : root(nullptr), totalParkingFare(0), totalTollFare(0) {}

    void addTransaction(const string& type, double amount, const string& timestamp) {
        addTransactionHelper(root, type, amount, timestamp);
    }

    void displayTransactions() const {
        if (!root) {
            cout << "No transactions recorded.\n";
            return;
        }

        cout << left << setw(15) << "Type" << setw(10) << "Amount (₹)" << setw(20) << "Timestamp" << endl;
        cout << string(45, '-') << endl;

        displayTransactionsHelper(root);
    }

    void displayTotalFare() const {
        cout << "\nTotal Parking Fare: ₹" << totalParkingFare << endl;
        cout << "Total Toll Fare: ₹" << totalTollFare << endl;
        cout << "Grand Total Fare: ₹" << (totalParkingFare + totalTollFare) << endl;
    }

    ~FareCollector() {
        cleanup(root);
    }
};

int main() {
    FareCollector fareCollector;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Transaction\n";
        cout << "2. Display Transactions\n";
        cout << "3. Display Total Fares\n";
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

                cout << "Enter amount (₹): ";
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
                fareCollector.displayTotalFare();
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
