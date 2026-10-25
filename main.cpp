#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

 
// Data Structure
 
struct LibraryItem {
    int idNumber;
    string bookTitle;
    string writerName;
    int yearPublished;
    int stockCount;
};

// Global container
vector<LibraryItem> catalog;

 
// Helper Utilities
 

int locateItem(int idValue) {
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i].idNumber == idValue)
            return i;
    }
    return -1;
}

void resetInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

 
// Add Item (Overloaded)
 

void insertItem(int idValue, string name, string creator, int year, int quantity) {

    if (locateItem(idValue) != -1) {
        cout << "Duplicate ID detected. Cannot insert.\n";
        return;
    }

    LibraryItem entry;
    entry.idNumber = idValue;
    entry.bookTitle = name;
    entry.writerName = creator;
    entry.yearPublished = year;
    entry.stockCount = quantity;

    catalog.push_back(entry);

    cout << "Item successfully inserted.\n";
}

void insertItem(const LibraryItem &entry) {

    if (locateItem(entry.idNumber) != -1) {
        cout << "Duplicate ID detected. Cannot insert.\n";
        return;
    }

    catalog.push_back(entry);
    cout << "Item successfully inserted using struct.\n";
}

 
// Show Items (Overloaded)
 

void printItems() {

    if (catalog.empty()) {
        cout << "No items currently stored.\n";
        return;
    }

    for (const auto &entry : catalog) {
        cout << "\nItem ID: " << entry.idNumber
             << "\nTitle: " << entry.bookTitle
             << "\nAuthor: " << entry.writerName
             << "\nYear: " << entry.yearPublished
             << "\nAvailable Copies: " << entry.stockCount << "\n";
    }
}

void printItems(int idValue) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "No matching item found.\n";
        return;
    }

    auto &entry = catalog[pos];

    cout << "\nItem ID: " << entry.idNumber
         << "\nTitle: " << entry.bookTitle
         << "\nAuthor: " << entry.writerName
         << "\nYear: " << entry.yearPublished
         << "\nAvailable Copies: " << entry.stockCount << "\n";
}

void printItems(const string &creator) {

    bool matchFound = false;

    for (const auto &entry : catalog) {
        if (entry.writerName == creator) {
            cout << "\nItem ID: " << entry.idNumber
                 << "\nTitle: " << entry.bookTitle
                 << "\nAuthor: " << entry.writerName
                 << "\nYear: " << entry.yearPublished
                 << "\nAvailable Copies: " << entry.stockCount << "\n";
            matchFound = true;
        }
    }

    if (!matchFound)
        cout << "No books written by that author were found.\n";
}

 
// Modify Item
 

void reviseItem(int idValue, string newTitle, string newAuthor, int newYear) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "Item not found. Update failed.\n";
        return;
    }

    catalog[pos].bookTitle = newTitle;
    catalog[pos].writerName = newAuthor;
    catalog[pos].yearPublished = newYear;

    cout << "Item updated successfully.\n";
}

 
// Find Item
 

LibraryItem retrieveItem(int idValue) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "Search failed. Item does not exist.\n";
        return {-1, "", "", 0, 0};
    }

    return catalog[pos];
}

 
// Remove Item
 

void removeItem(int idValue) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "Deletion failed. Item not found.\n";
        return;
    }

    catalog.erase(catalog.begin() + pos);
    cout << "Item removed successfully.\n";
}

 
// Checkout / Checkin
 

void checkoutItem(int idValue, int amount = 1) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "Checkout failed. Item not found.\n";
        return;
    }

    if (catalog[pos].stockCount < amount) {
        cout << "Not enough stock available.\n";
        return;
    }

    catalog[pos].stockCount -= amount;
    cout << "Checkout complete.\n";
}

void checkinItem(int idValue, int amount = 1) {

    int pos = locateItem(idValue);

    if (pos == -1) {
        cout << "Return failed. Item not found.\n";
        return;
    }

    catalog[pos].stockCount += amount;
    cout << "Return complete.\n";
}

 
// Interface Menu
 

void showOptions() {

    cout << "\n========= Library Control Panel =========\n";
    cout << "1. Insert Book\n";
    cout << "2. Display All\n";
    cout << "3. Display By ID\n";
    cout << "4. Display By Author\n";
    cout << "5. Update Book\n";
    cout << "6. Search Book\n";
    cout << "7. Remove Book\n";
    cout << "8. Borrow Book\n";
    cout << "9. Return Book\n";
    cout << "0. Quit\n";
    cout << "Select option: ";
}

int main() {

    int selection;

    do {
        showOptions();
        cin >> selection;
        resetInputStream();

        switch (selection) {

            case 1: {
                int id, year, quantity;
                string title, author;

                cout << "ID: ";
                cin >> id;
                resetInputStream();

                cout << "Title: ";
                getline(cin, title);

                cout << "Author: ";
                getline(cin, author);

                cout << "Year: ";
                cin >> year;

                cout << "Copies: ";
                cin >> quantity;

                insertItem(id, title, author, year, quantity);
                break;
            }

            case 2:
                printItems();
                break;

            case 3: {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                printItems(id);
                break;
            }

            case 4: {
                string author;
                cout << "Enter Author: ";
                getline(cin, author);
                printItems(author);
                break;
            }

            case 5: {
                int id, year;
                string title, author;

                cout << "ID to update: ";
                cin >> id;
                resetInputStream();

                cout << "New Title: ";
                getline(cin, title);

                cout << "New Author: ";
                getline(cin, author);

                cout << "New Year: ";
                cin >> year;

                reviseItem(id, title, author, year);
                break;
            }

            case 6: {
                int id;
                cout << "Search ID: ";
                cin >> id;
                LibraryItem found = retrieveItem(id);
                if (found.idNumber != -1)
                    cout << "Item located: " << found.bookTitle << "\n";
                break;
            }

            case 7: {
                int id;
                cout << "ID to remove: ";
                cin >> id;
                removeItem(id);
                break;
            }

            case 8: {
                int id, amount;
                cout << "Borrow ID: ";
                cin >> id;
                cout << "Amount: ";
                cin >> amount;
                checkoutItem(id, amount);
                break;
            }

            case 9: {
                int id, amount;
                cout << "Return ID: ";
                cin >> id;
                cout << "Amount: ";
                cin >> amount;
                checkinItem(id, amount);
                break;
            }

            case 0:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid selection.\n";
        }

    } while (selection != 0);

    return 0;
}