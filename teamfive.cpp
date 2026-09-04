#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

class Person {
protected:
    string name;

public:
    Person() {
        name = "";
    }

    Person(string n) {
        name = n;
    }

    virtual ~Person() {}

    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }
};

class Staff : public Person {
private:
    string role;

public:
    Staff() : Person("") {
        role = "";
    }

    Staff(string n, string r) : Person(n) {
        role = r;
    }

    string getRole() {
        return role;
    }

    void setRole(string r) {
        role = r;
    }

    void displayStaff() {
        cout << left
             << setw(20) << name
             << setw(18) << role
             << endl;
    }
};

class Admin {
private:
    string username;
    string email;
    string password;

public:
    Admin() {
        username = "";
        email = "";
        password = "";
    }

    Admin(string u, string e, string p) {
        username = u;
        email = e;
        password = p;
    }

    bool login(string user, string mail, string pass) {
        return username == user &&
               email == mail &&
               password == pass;
    }

    void setCredentials(string u, string e, string p) {
        username = u;
        email = e;
        password = p;
        cout << "\n>> Admin credentials updated successfully!\n";
    }

    void displayAdminInfo() {
        cout << "\n";
        cout << "========================================\n";
        cout << "            Admin Profile               \n";
        cout << "========================================\n";
        cout << "Username : " << username << endl;
        cout << "Email    : " << email << endl;
        cout << "========================================\n";
    }
};

class MenuItem {
private:
    string name;
    double price;
    int stock;

public:
    MenuItem() {
        name = "";
        price = 0.0;
        stock = 0;
    }

    MenuItem(string n, double p, int s) {
        name = n;
        price = p;
        stock = s;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getStock() {
        return stock;
    }

    void setName(string n) { name = n; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }

    bool reduceStock(int quantity) {
        if (quantity > 0 && quantity <= stock) {
            stock -= quantity;
            return true;
        }
        return false;
    }

    void addStock(int quantity) {
        if (quantity > 0) {
            stock += quantity;
        }
    }

    void displayItem(int number) {
        cout << left
             << setw(8) << number
             << setw(20) << name
             << "$" << setw(9)
             << fixed << setprecision(2)
             << price
             << setw(8) << stock
             << endl;
    }
};

class Restaurant {
private:
    MenuItem menu[20]; // ពង្រីកទំហំ Menu ដល់ ២០
    int itemCount;
    static double totalRevenue;

public:
    Restaurant() {
        itemCount = 8;
    }

    void initializeMenu() {
        ifstream file("menu.txt");
        if (file.is_open()) {
            string n;
            double p;
            int s;
            int i = 0;
            while (i < 20 && file >> ws && getline(file, n) && file >> p >> s) {
                menu[i] = MenuItem(n, p, s);
                i++;
            }
            itemCount = i;
            file.close();
        } else {
            menu[0] = MenuItem("Burger", 5.00, 50);
            menu[1] = MenuItem("Pizza", 8.00, 60);
            menu[2] = MenuItem("Water", 1.00, 200);
            menu[3] = MenuItem("Fried Rice", 3.00, 100);
            menu[4] = MenuItem("Cake", 3.00, 100);
            menu[5] = MenuItem("Noodle", 4.00, 120);
            menu[6] = MenuItem("Sting Red", 1.00, 300);
            menu[7] = MenuItem("Sting Blue", 1.00, 300);
            saveMenuToFile();
        }
    }

    void saveMenuToFile() {
        ofstream file("menu.txt");
        if (file.is_open()) {
            for (int i = 0; i < itemCount; i++) {
                file << menu[i].getName() << "\n"
                     << menu[i].getPrice() << " "
                     << menu[i].getStock() << "\n";
            }
            file.close();
        }
    }

    void displayMenu() {
        cout << "\n";
        cout << "========================================================\n";
        cout << "                Restaurant Menu                         \n";
        cout << "========================================================\n";

        cout << left
             << setw(8) << "No."
             << setw(20) << "Item"
             << setw(10) << "Price"
             << setw(8) << "Stock"
             << endl;

        cout << "--------------------------------------------------------\n";

        for (int i = 0; i < itemCount; i++) {
            menu[i].displayItem(i);
        }

        cout << "========================================================\n";
    }

    void insertItem() {
        if (itemCount >= 20) {
            cout << ">> Menu is full (Max 20 items)!\n";
            return;
        }
        string name;
        double price;
        int stock;
        cout << "Enter item name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter item price: ";
        cin >> price;
        cout << "Enter item stock: ";
        cin >> stock;

        menu[itemCount] = MenuItem(name, price, stock);
        itemCount++;
        saveMenuToFile();
        cout << ">> Item inserted successfully!\n";
    }

    void editItem() {
        displayMenu();
        if (itemCount == 0) return;
        int idx;
        cout << "Enter item number to edit (0 to " << itemCount - 1 << "): ";
        cin >> idx;
        if (idx >= 0 && idx < itemCount) {
            string name;
            double price;
            int stock;
            cout << "Enter new name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter new price: ";
            cin >> price;
            cout << "Enter new stock: ";
            cin >> stock;

            menu[idx] = MenuItem(name, price, stock);
            saveMenuToFile();
            cout << ">> Item updated successfully!\n";
        } else {
            cout << ">> Invalid item number!\n";
        }
    }

    void deleteItem() {
        displayMenu();
        if (itemCount == 0) return;
        int idx;
        cout << "Enter item number to delete (0 to " << itemCount - 1 << "): ";
        cin >> idx;
        if (idx >= 0 && idx < itemCount) {
            for (int i = idx; i < itemCount - 1; i++) {
                menu[i] = menu[i + 1];
            }
            itemCount--;
            saveMenuToFile();
            cout << ">> Item deleted successfully!\n";
        } else {
            cout << ">> Invalid item number!\n";
        }
    }

    void searchMenuItem() {
        string query;
        cout << "\nEnter item name to search: ";
        cin >> ws;
        getline(cin, query);

        bool found = false;
        cout << "\n========================================================\n";
        cout << "                 Search Results                         \n";
        cout << "========================================================\n";
        cout << left << setw(8) << "No." << setw(20) << "Item" << setw(10) << "Price" << setw(8) << "Stock" << endl;
        cout << "--------------------------------------------------------\n";

        for (int i = 0; i < itemCount; i++) {
            if (menu[i].getName().find(query) != string::npos) {
                menu[i].displayItem(i);
                found = true;
            }
        }
        cout << "========================================================\n";
        if (!found) {
            cout << ">> No items found matching \"" << query << "\".\n";
        }
    }

    void takeOrder() {
        char again;

        do {
            displayMenu();

            int number;
            int quantity;

            cout << "\nEnter item number (0-" << itemCount - 1 << "): ";

            while (!(cin >> number) || number < 0 || number >= itemCount) {
                cout << ">> Invalid item number!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter number 0-" << itemCount - 1 << ": ";
            }

            cout << "Enter quantity: ";

            while (!(cin >> quantity) || quantity <= 0) {
                cout << ">> Invalid quantity!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter quantity greater than 0: ";
            }

            if (quantity <= menu[number].getStock()) {
                double total = menu[number].getPrice() * quantity;
                menu[number].reduceStock(quantity);
                totalRevenue += total;
                saveMenuToFile();

                cout << "\n";
                cout << "========================================\n";
                cout << "          Order Successfully            \n";
                cout << "========================================\n";
                cout << "Item       : " << menu[number].getName() << endl;
                cout << "Quantity   : " << quantity << endl;
                cout << "Unit Price : $" << fixed << setprecision(2) << menu[number].getPrice() << endl;
                cout << "Total Cost : $" << fixed << setprecision(2) << total << endl;
                cout << "Stock Left : " << menu[number].getStock() << endl;
                cout << "========================================\n";
            } else {
                cout << "\n>> NOT ENOUGH STOCK!\n";
                cout << "Available stock: " << menu[number].getStock() << endl;
            }

            cout << "\nOrder another item? (y/n): ";
            cin >> again;

            while (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                cout << "Please enter y or n: ";
                cin >> again;
            }

        } while (again == 'y' || again == 'Y');
    }

    static void displayRevenue() {
        cout << "\n";
        cout << "========================================\n";
        cout << "            Static Revenue              \n";
        cout << "========================================\n";
        cout << "Total Revenue : $" << fixed << setprecision(2) << totalRevenue << endl;
        cout << "========================================\n";
    }

    friend void showOrderSummary(Restaurant& restaurant);
};

double Restaurant::totalRevenue = 0.0;

void showOrderSummary(Restaurant& restaurant) {
    cout << "\n";
    cout << "================================================\n";
    cout << "              RESTAURANT SUMMARY                \n";
    cout << "================================================\n";
    cout << "Total Menu Items : " << restaurant.itemCount << endl;
    cout << "Total Revenue    : $" << fixed << setprecision(2) << Restaurant::totalRevenue << endl;
    cout << "================================================\n";
}

bool adminLogin(Admin& admin) {
    string username, email, password;

    cout << "\n";
    cout << "========================================\n";
    cout << "              Admin Login               \n";
    cout << "========================================\n";
    cout << "Username : ";
    cin >> username;
    cout << "Email    : ";
    cin >> email;
    cout << "Password : ";
    cin >> password;

    return admin.login(username, email, password);
}

void loadStaffFromFile(Staff staff[], int& size) {
    ifstream file("staff.txt");
    if (file.is_open()) {
        string n, r;
        int i = 0;
        while (i < 10 && file >> ws && getline(file, n) && getline(file, r)) {
            staff[i] = Staff(n, r);
            i++;
        }
        size = i;
        file.close();
    }
}

void displayStaffList(Staff staff[], int size) {
    cout << "\n";
    cout << "========================================\n";
    cout << "               Staff List               \n";
    cout << "========================================\n";

    cout << left
         << setw(20) << "Name"
         << setw(18) << "Role"
         << endl;

    cout << "----------------------------------------\n";

    for (int i = 0; i < size; i++) {
        staff[i].displayStaff();
    }

    cout << "========================================\n";
}

void adminMenu(Admin& admin, Restaurant& restaurant, Staff staff[], int staffSize) {
    int choice;
    do {
        cout << "\n=========================================\n";
        cout << "|             Admin Control Panel       |\n";
        cout << "=========================================\n";
        cout << "1. View Admin Info\n";
        cout << "2. Change Admin Credentials (Username/Email/Password)\n";
        cout << "3. Insert Item\n";
        cout << "4. Edit Item\n";
        cout << "5. Delete Item\n";
        cout << "6. View All Items\n";
        cout << "7. View Staff List\n";
        cout << "8. Logout\n";
        cout << "Enter choice (1-8): ";

        while (!(cin >> choice) || choice < 1 || choice > 8) {
            cout << ">> Invalid choice!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter 1-8: ";
        }

        switch (choice) {
            case 1:
                admin.displayAdminInfo();
                break;

            case 2: {
                string user, email, pass;
                cout << "Enter new Username: ";
                cin >> user;
                cout << "Enter new Email: ";
                cin >> email;
                cout << "Enter new Password: ";
                cin >> pass;
                admin.setCredentials(user, email, pass);
                break;
            }

            case 3:
                restaurant.insertItem();
                break;

            case 4:
                restaurant.editItem();
                break;

            case 5:
                restaurant.deleteItem();
                break;

            case 6:
                restaurant.displayMenu();
                break;

            case 7:
                displayStaffList(staff, staffSize);
                break;

            case 8:
                cout << "\n>> Logging out from Admin panel...\n";
                break;
        }

    } while (choice != 8);
}

void displayMainMenu() {
    cout << "\n";
    cout << "=========================================\n";
    cout << "|     Restaurant Management System      |\n";
    cout << "=========================================\n";
    cout << "1. Admin Login\n";
    cout << "2. View Menu\n";
    cout << "3. Search Menu Item\n";
    cout << "4. Place Order\n";
    cout << "5. View Static Revenue\n";
    cout << "6. Exit\n";
    cout << "=========================================\n";
}

int main() {
    Restaurant restaurant;
    restaurant.initializeMenu();

    Staff staff[10] = {
        Staff("Samrach Visal", "Manager"),
        Staff("Hark", "Chef"),
        Staff("Veaha Jek", "Waiter")
    };
    int staffSize = 3;
    loadStaffFromFile(staff, staffSize);

    // Initial Admin credentials
    Admin admin("visal", "visal@gmail.com", "12345");

    int choice;

    do {
        displayMainMenu();
        cout << "Enter your choice (1-6): ";

        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << ">> Invalid choice!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter 1-6: ";
        }

        switch (choice) {
            case 1:
                if (adminLogin(admin)) {
                    cout << "\n>> Login Successful!\n";
                    adminMenu(admin, restaurant, staff, staffSize);
                } else {
                    cout << "\n>> Login Failed!\n";
                    cout << ">> Incorrect Username, Email or Password.\n";
                }
                break;

            case 2:
                restaurant.displayMenu();
                break;

            case 3:
                restaurant.searchMenuItem();
                break;

            case 4:
                restaurant.takeOrder();
                break;

            case 5:
                Restaurant::displayRevenue();
                showOrderSummary(restaurant);
                break;

            case 6:
                cout << "\n";
                cout << "========================================\n";
                cout << "    Thank You For Using Our System      \n";
                cout << "    Goodbye! Have a Nice Day            \n";
                cout << "========================================\n";
                break;
        }

    } while (choice != 6);

    return 0;
}