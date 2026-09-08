#include <iostream>
#include <fstream>
#include <iomanip>    
#include <string>
#include <cctype>   
using namespace std;

// ================= FOOD =================
class Food {
    int id, stock;
    string name;
    double price;

public:
    Food() : id(0), stock(0), name(""), price(0) {}
    Food(int i, string n, double p, int s) : id(i), stock(s), name(n), price(p) {}

    int getId() { 
        return id;
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
    void setName(string n) {
         name = n; 
        }
    void setPrice(double p) {
        price = p; 
        }
    void setStock(int s) { 
        stock = s; 
        }
    void reduceStock(int q) {
        stock -= q; 
        }

    void display() {
        cout << left << setw(5) << id << setw(20) << name 
             << "$" << setw(8) << fixed << setprecision(2) << price 
             << setw(6) << stock << endl;
    }
};

// ================= ADMIN =================
class Admin {
    string email = "visal@gmail.com", password = "1111";
    Food food[100];
    int totalFood = 10;

public:
    static string restaurantName;
    static double totalSales;

    Admin() {
        food[0] = Food(1, "Fried Rice", 3.50, 200);
        food[1] = Food(2, "Beef Burger", 5.00, 150);
        food[2] = Food(3, "Chicken Burger", 4.50, 180);
        food[3] = Food(4, "Pizza", 8.00, 10);
        food[4] = Food(5, "Fried Chicken", 6.00, 250);
        food[5] = Food(6, "Noodle", 3.00, 200);
        food[6] = Food(7, "Spaghetti", 5.50, 120);
        food[7] = Food(8, "Coca Cola", 1.50, 300);
        food[8] = Food(9, "Orange Juice", 2.00, 250);
        food[9] = Food(10, "Ice Cream", 2.50, 150);
    }

    static void showRestaurantName() {
        cout << "\n====================================\n"
             << "        " << restaurantName 
             << "\n====================================\n";
    }

    bool login(string e, string p) {
        return e == email && p == password;
        }

    int findFood(int id) {
        for (int i = 0; i < totalFood; i++)
            if (food[i].getId() == id) return i;
        return -1;
    }

    void viewItems() {
        if (totalFood == 0) { cout << "No food available!\n"; return; }
        cout << "\n============== FOOD ITEMS ==============\n"
             << left << setw(5) << "ID" << setw(20) << "Name" << setw(9) << "Price" << setw(6) << "Stock\n"
             << "----------------------------------------\n";
        for (int i = 0; i < totalFood; i++) food[i].display();
        cout << "----------------------------------------\n";
    }

    void searchItem() {
        char ch;
        cout << "\nEnter letter to search: "; cin >> ch;
        ch = tolower((unsigned char)ch);
        bool found = false;

        for (int i = 0; i < totalFood; i++) {
            for (char c : food[i].getName()) {
                if (tolower((unsigned char)c) == ch) {
                    food[i].display();
                    found = true;
                    break;
                }
            }
        }
        if (!found) cout << "No food found!\n";
    }

    void insertItem() {
        if (totalFood >= 100) {
             cout << "Storage full!\n"; 
             return; 
            }
        int id, stock; string name; double price;

        cout << "ID: "; cin >> id;
        if (id <= 0 || findFood(id) != -1) {
            cout << "Invalid ID!\n"; 
            return;
            }
        cin.ignore();
        cout << "Name: "; getline(cin, name);
        cout << "Price: $"; cin >> price;
        cout << "Stock: "; cin >> stock;

        food[totalFood++] = Food(id, name, price, stock);
        saveFood();
        cout << "Food inserted successfully!\n";
    }

    void deleteItem() {
        int id; 
        cout << "Enter ID to delete: "; cin >> id;
        int pos = findFood(id);
        if (pos == -1) {
            cout << "Not found!\n"; 
            return; 
            }

        for (int i = pos; i < totalFood - 1; i++) food[i] = food[i + 1];
        totalFood--;
        saveFood();
        cout << "Deleted successfully!\n";
    }

    void editItem() {
        int id; 
        cout << "Enter ID to edit: "; cin >> id;
        int pos = findFood(id);
        if (pos == -1) {
            cout << "Not found!\n"; 
            return; 
            }

        string name; 
        double price; 
        int stock;
        cin.ignore(); 
        cout << "New Name: "; getline(cin, name);
        cout << "New Price: $"; cin >> price;
        cout << "New Stock: "; cin >> stock;

        food[pos].setName(name);
        food[pos].setPrice(price);
        food[pos].setStock(stock);
        saveFood();
        cout << "Edited successfully!\n";
    }

    static void showTotalSales() {
        cout << "\n===== Total Accumulated Sales =====\n"
             << "Total Sales Amount: $" << fixed << setprecision(2) << totalSales
             << "\n===================================\n";
    }

    void order() {
        int id, qty, totalItems = 0;
        char again;
        double grandTotal = 0;

        do {
            cout << "Enter Food ID: "; cin >> id;
            int pos = findFood(id);

            if (pos == -1){
                cout << "Not found!\n";
            }
            else if (food[pos].getStock() <= 0){
                cout << "Out of stock!\n";
            }
            else {
                cout << food[pos].getName() << " | $" << food[pos].getPrice() << endl;
                cout << "Quantity: "; cin >> qty;

                if (qty <= 0 || qty > food[pos].getStock()){
                    cout << "Invalid quantity!\n";
                }
                else {
                    double sub = food[pos].getPrice() * qty;
                    food[pos].reduceStock(qty);
                    grandTotal += sub;
                    totalItems += qty;
                    totalSales += sub;
                    cout << "Subtotal: $" << fixed << setprecision(2) << sub << endl;
                    saveFood();
                }
            }
            cout << "Order more? (y/n): "; cin >> again;
        } while (again == 'y' || again == 'Y');

        cout << "\n================ Summary ================\n"
             << "Total Items : " << totalItems << "\n"
             << "GRAND TOTAL : $" << fixed << setprecision(2) << grandTotal << "\n"
             << "=========================================\n";
    }

    void saveFood() {
        ofstream file("food.txt");
        if (!file)
        return;
        file << totalFood << endl;
        for (int i = 0; i < totalFood; i++) {
            file << food[i].getId() << endl << food[i].getName() << endl
                 << food[i].getPrice() << endl << food[i].getStock() << endl;
        }
    }

    void loadFood() {
        ifstream file("food.txt");
        if (!file) 
        return;
        int count; 
        file >> count;
        if (file.fail() || count < 1 || count > 100) return;

        totalFood = 0;
        for (int i = 0; i < count; i++) {
            int id, stock; string name; double price;
            file >> id; file.ignore(); getline(file, name);
            file >> price >> stock;
            if (!file.fail()) food[totalFood++] = Food(id, name, price, stock);
        }
    }

    void changeAccount() {
        cout << "New Email: "; cin >> email;
        cout << "New Password: "; cin >> password;
        saveAdmin();
        cout << "Account updated!\n";
    }

    void saveAdmin() {
        ofstream file("admin.txt");
        if (file) file << email << endl << password << endl;
    }

    void loadAdmin() {
        ifstream file("admin.txt");
        if (file) { getline(file, email); getline(file, password); }
    }
};

// Static initializations
string Admin::restaurantName = "ABC RESTAURANT";
double Admin::totalSales = 0.0;

// ================= MENUS =================
void adminMenu(Admin &a) {
    int choice;
    do {
        Admin::showRestaurantName();
        cout << "1. View | 2. Insert | 3. Delete | 4. Edit | 5. Search | 6. Change account | 0. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: a.viewItems(); break;
            case 2: a.insertItem(); break;
            case 3: a.deleteItem(); break;
            case 4: a.editItem(); break;
            case 5: a.searchItem(); break;
            case 6: a.changeAccount(); break;
        }
    } while (choice != 0);
}

void customerMenu(Admin &a) {
    int choice;
    do {
        Admin::showRestaurantName();
        cout << "1. View Items | 2. Search | 3. Order | 4. Total Sales (Static) | 0. Back\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: a.viewItems(); break;
            case 2: a.searchItem(); break;
            case 3: a.order(); break;
            case 4: Admin::showTotalSales(); break;
        }
    } while (choice != 0);
}

// ================= MAIN =================
int main() {
    Admin admin;
    admin.loadFood();
    admin.loadAdmin();

    int choice;
    do {
        Admin::showRestaurantName();
        cout << "1. Admin Login\n2. Customer\n0. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            string e, p;
            cout << "Email: "; cin >> e;
            cout << "Password: "; cin >> p;
            if (admin.login(e, p)){
                adminMenu(admin);
            }
            else{
                cout << "Wrong email/password!\n";
            }
            } else if (choice == 2){
             customerMenu(admin);
            }
    } while (choice != 0);

    admin.saveFood();
    admin.saveAdmin();
    return 0;
}