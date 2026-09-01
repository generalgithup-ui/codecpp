#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

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

    void displayStaff() {
        cout << left
             << setw(20) << name
             << setw(18) << role
             << endl;
    }
};

class Admin : public Person {
private:
    string username;
    string email;
    string password;

public:
    Admin() : Person("") {
        username = "";
        email = "";
        password = "";
    }

    Admin(string n, string u, string e, string p)
        : Person(n) {
        username = u;
        email = e;
        password = p;
    }

    bool login(string user, string mail, string pass) {
        return username == user &&
               email == mail &&
               password == pass;
    }

    void displayAdminInfo() {
        cout << "\n";
        cout << "========================================\n";
        cout << "             Admin login\n";
        cout << "========================================\n";
        cout << "Name     : " << name << endl;
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
    MenuItem menu[8];
    int itemCount;

    static double totalRevenue;

public:
    Restaurant() {
        itemCount = 8;
    }

    void initializeMenu() {
        menu[0] = MenuItem("Burger", 5.00, 50);
        menu[1] = MenuItem("Pizza", 8.00, 60);
        menu[2] = MenuItem("Water", 1.00, 200);
        menu[3] = MenuItem("Fried Rice", 3.00, 100);
        menu[4] = MenuItem("Cake", 3.00, 100);
        menu[5] = MenuItem("Noodle", 4.00, 120);
        menu[6] = MenuItem("Sting Red", 1.00, 300);
        menu[7] = MenuItem("Sting Blue", 1.00, 300);
    }

    void displayMenu() {
        cout << "\n";
        cout << "========================================================\n";
        cout << "                Restaurant menu\n";
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

    void takeOrder() {
        char again;

        do {
            displayMenu();

            int number;
            int quantity;

            cout << "\nEnter item number (0-7): ";

            while (!(cin >> number) ||
                    number < 0 ||
                    number >= itemCount) {

                cout << ">> Invalid item number!\n";

                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Please enter number 0-7: ";
            }

            cout << "Enter quantity: ";

            while (!(cin >> quantity) ||
                    quantity <= 0) {

                cout << ">> Invalid quantity!\n";

                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                cout << "Please enter quantity greater than 0: ";
            }

            if (quantity <= menu[number].getStock()) {

                double total =
                    menu[number].getPrice() * quantity;

                menu[number].reduceStock(quantity);

                totalRevenue += total;

                cout << "\n";
                cout << "========================================\n";
                cout << "          Order Successfully\n";
                cout << "========================================\n";

                cout << "Item       : "
                     << menu[number].getName()
                     << endl;

                cout << "Quantity   : "
                     << quantity
                     << endl;

                cout << "Unit Price : $"
                     << fixed
                     << setprecision(2)
                     << menu[number].getPrice()
                     << endl;

                cout << "Total Cost : $"
                     << fixed
                     << setprecision(2)
                     << total
                     << endl;

                cout << "Stock Left : "
                     << menu[number].getStock()
                     << endl;

                cout << "========================================\n";
            }
            else {
                cout << "\n";
                cout << ">> NOT ENOUGH STOCK!\n";

                cout << "Available stock: "
                     << menu[number].getStock()
                     << endl;
            }

            cout << "\nOrder another item? (y/n): ";
            cin >> again;

            while (again != 'y' &&
                   again != 'Y' &&
                   again != 'n' &&
                   again != 'N') {

                cout << "Please enter y or n: ";
                cin >> again;
            }

        } while (again == 'y' ||
                 again == 'Y');
    }

    static void displayRevenue() {
        cout << "\n";
        cout << "========================================\n";
        cout << "          Static Revenue\n";
        cout << "========================================\n";

        cout << "Total Revenue : $"
             << fixed
             << setprecision(2)
             << totalRevenue
             << endl;

        cout << "========================================\n";
    }

    friend void showOrderSummary(Restaurant& restaurant);
};

double Restaurant::totalRevenue = 0.0;

void showOrderSummary(Restaurant& restaurant) {
    cout << "\n";
    cout << "================================================\n";
    cout << "             RESTAURANT SUMMARY\n";
    cout << "================================================\n";

    cout << "Total Menu Items : "
         << restaurant.itemCount
         << endl;

    cout << "Total Revenue    : $"
         << fixed
         << setprecision(2)
         << Restaurant::totalRevenue
         << endl;

    cout << "================================================\n";
}

bool adminLogin(Admin& admin) {
    string username;
    string email;
    string password;

    cout << "\n";
    cout << "========================================\n";
    cout << "              Admin Login\n";
    cout << "========================================\n";

    cout << "Username : ";
    cin >> username;

    cout << "Email    : ";
    cin >> email;

    cout << "Password : ";
    cin >> password;

    return admin.login(
        username,
        email,
        password
    );
}

void displayStaffList(Staff staff[], int size) {
    cout << "\n";
    cout << "========================================\n";
    cout << "             Staff List\n";
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

void displayMainMenu() {
    cout << "\n";
    cout << "=========================================\n";
    cout << "|    Restaurant Management System       |\n";
    cout << "=========================================\n";

    cout << "1. Admin Login\n";
    cout << "2. View Menu\n";
    cout << "3. Place Order\n";
    cout << "4. View Staff List\n";
    cout << "5. View Static Revenue\n";
    cout << "6. Exit\n";

    cout << "=========================================\n";
}

int main() {
    Restaurant restaurant;

    restaurant.initializeMenu();

    Staff staff[3] = {
        Staff("Samrach Visal", "Manager"),
        Staff("Hark", "Chef"),
        Staff("Veaha, Jek", "Waiter")
    };

    Admin admin(
        "VISAL",
        "visal",
        "visal@gmail.com",
        "12345"
    );

    int choice;

    do {
        displayMainMenu();

        cout << "Enter your choice (1-6): ";

        while (!(cin >> choice) ||
               choice < 1 ||
               choice > 6) {

            cout << ">> Invalid choice!\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Please enter 1-6: ";
        }

        switch (choice) {

            case 1:
                if (adminLogin(admin)) {
                    cout << "\n";
                    cout << ">> Login Successful!\n";

                    admin.displayAdminInfo();
                    // បានដក showOrderSummary(restaurant); ចេញពីទីនេះហើយ
                }
                else {
                    cout << "\n";
                    cout << ">> Login Failed!\n";
                    cout << ">> Incorrect Username, "
                         << "Email or Password.\n";
                }
                break;

            case 2:
                restaurant.displayMenu();
                break;

            case 3:
                restaurant.takeOrder();
                break;

            case 4:
                displayStaffList(staff, 3);
                break;

            case 5:
                Restaurant::displayRevenue();
                showOrderSummary(restaurant); // បើអ្នកចង់ឱ្យវាបង្ហាញពេលចុចលេខ 5 អ្នកអាចទុកវានៅទីនេះ
                break;

            case 6:
                cout << "\n";
                cout << "========================================\n";
                cout << "    Thank You For Using Our System\n";
                cout << "    Goodbye! Have a Nice Day\n";
                cout << "========================================\n";
                break;
        }

    } while (choice != 6);

    return 0;
}