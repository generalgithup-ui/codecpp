#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ==========================================
// 1. Base Class (Class មេសម្រាប់មនុស្ស)
// ==========================================
class Person {
protected:
    string name;

public:
    Person() : name("") {}
    Person(string n) : name(n) {}
    
    virtual ~Person() {} // Virtual Destructor
    
    string getName() const { return name; }
    void setName(string n) { name = n; }
};

// ==========================================
// 2. Derived Class: Staff (Class កូនបន្តពី Person)
// ==========================================
class Staff : public Person {
private:
    string role; 

public:
    Staff() : Person(""), role("") {}
    Staff(string n, string r) : Person(n), role(r) {}

    void displayStaff() const {
        cout << left << setw(18) << name
             << setw(16) << role << endl;
    }
};

// ==========================================
// 3. Derived Class: Admin (Class កូនបន្តពី Person)
// ==========================================
class Admin : public Person {
private:
    string email;
    string password;

public:
    Admin() : Person(""), email(""), password("") {}
    Admin(string n, string em, string pw) : Person(n), email(em), password(pw) {}

    bool login(string inputEmail, string inputPw) {
        return (email == inputEmail && password == inputPw);
    }

    void displayAdminInfo() const {
        cout << "\n--- Admin Profile ---" << endl;
        cout << "Name : " << name << endl;
        cout << "Email: " << email << endl;
    }
};

// ==========================================
// 4. MenuItem Class (សម្រាប់មុខម្ហូប)
// ==========================================
class MenuItem {
private:
    string name;
    double price;
    int stock;

public:
    MenuItem() : name(""), price(0.0), stock(0) {} 
    MenuItem(string n, double p, int s) : name(n), price(p), stock(s) {} 
    
    inline string getName() const { return name; }    
    inline double getPrice() const { return price; }  
    inline int getStock() const { return stock; }     
    
    void reduceStock(int qty) {
         if (stock >= qty) 
             stock -= qty; 
    }

    void displayItem() const {
        cout << left << setw(18) << name
             << setw(10) << price
             << setw(8)  << stock << endl;
    }
};

// ==========================================
// 5. Restaurant Class (គ្រប់គ្រងម៉ឺនុយ និងប្រាក់ចំណូល)
// ==========================================
class Restaurant {
private:
    MenuItem *menu;
    int itemCount;
    static double totalRevenue; 

public:
    Restaurant(int count) : itemCount(count) {    
        menu = new MenuItem[count];    
    }

    ~Restaurant() {        
        delete[] menu;
    }

    void initializeMenu() {
        menu[0] = MenuItem("0) Burger", 5.00, 50);
        menu[1] = MenuItem("1) Pizza", 8.00, 60);
        menu[2] = MenuItem("2) Water", 1.00, 200);
        menu[3] = MenuItem("3) Fry rice", 3.00, 100);
        menu[4] = MenuItem("4) Cake", 3.00, 100);
        menu[5] = MenuItem("5) Noodle", 4.00, 120);
        menu[6] = MenuItem("6) Sting Red", 1.00, 300);
        menu[7] = MenuItem("7) Sting Blue", 1.00, 300);
    }

    void displayMenu() const {
        cout << "\n======== Welcome to Our Restaurant Menu ========" << endl;
        cout << left << setw(18) << "Item" 
             << setw(10) << "Price" << setw(8) << "Stock" << endl;
        cout << "------------------------------------------------" << endl;
        for (int i = 0; i < itemCount; i++) {
            menu[i].displayItem();
        }
    }

    void takeOrder() {
        char continueOrder;
        do {
            displayMenu();
            int index, qty;
            cout << "\nEnter item number (0-7): ";
            cin >> index;

            if (index >= 0 && index < itemCount) {
                cout << "Enter quantity: ";
                cin >> qty;

                if (menu[index].getStock() >= qty) {
                    menu[index].reduceStock(qty);
                    double total = menu[index].getPrice() * qty;
                    totalRevenue += total;

                    cout << "\n==================================" << endl;
                    cout << " Status    : Order Successful!" << endl;
                    cout << "- Ordered  : " << menu[index].getName() << endl;
                    cout << "- Quantity : " << qty << endl;
                    cout << "- Total Cost: $" << fixed << setprecision(2) << total << endl;
                    cout << "==================================" << endl;
                } else {
                    cout << ">> Not enough stock! Only " << menu[index].getStock() << " left." << endl;
                }
            } else {
                cout << ">> Invalid item number. Please try again." << endl;
            }

            cout << "\nDo you want to order another item? (y/n): ";
            cin >> continueOrder;

        } while (continueOrder == 'y' || continueOrder == 'Y');
    }

    static void displayRevenue() {
        cout << "\n>>> Total Restaurant Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    }

    friend void showOrderSummary(const Restaurant &res);    
};

double Restaurant::totalRevenue = 0.0;  

// Friend Function
void showOrderSummary(const Restaurant &res) {
    cout << "\n=================================================" << endl;
    cout << "      Restaurant Summary (Static & Friend)       " << endl;
    cout << "=================================================" << endl;
    cout << "Total Item Types    : " << res.itemCount << endl;    
    cout << "Total Sales Revenue : $" << fixed << setprecision(2) << Restaurant::totalRevenue << endl;
    cout << "=================================================" << endl;
}

// ==========================================
// Main Program
// ==========================================
int main() {
    cout << "=========================================" << endl;
    cout << "|      Restaurant Management System     |" << endl;
    cout << "=========================================" << endl;
    
    Restaurant *restaurant = new Restaurant(8); 
    restaurant->initializeMenu();

    // បង្កើត Staff ប្រើប្រាស់ Inheritance
    Staff st[3] = {
        Staff("Samrach Visal", "Manager"), 
        Staff("Hark", "Chef"), 
        Staff("Dav, jek", "Waiter")
    };
      
    // បង្កើត Admin សម្រាប់ប្រព័ន្ធការពារ
    Admin admin("Kim Sour", "admin@gmail.com", "12345");

    int choice;
    do {
        cout << "\n============= MAIN MENU =============" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Place Order (Continuous Ordering)" << endl;
        cout << "3. View Staff List" << endl;
        cout << "4. View Revenue & Summary (Admin Area)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        // Validation ត្រង់នេះធ្វើឱ្យងាយយល់ជាងមុន
        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Please enter 1 to 5: ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                restaurant->displayMenu(); 
                break;

            case 2:
                restaurant->takeOrder(); // ហៅមុខងារកុម្ម៉ង់ជាប់គ្នាបាន
                break;

            case 3:
                cout << "\n======== Staff List ========" << endl;
                cout << left << setw(18) << "Name" << setw(16) << "Role" << endl;
                cout << "----------------------------------" << endl;
                for (int i = 0; i < 3; i++) {
                    st[i].displayStaff();
                }
                break;

            case 4: {
                // ការពារផ្នែក Admin មុននឹងមើលចំណូល
                string inputEmail, inputPw;
                cout << "\n--- Admin Login Required ---" << endl;
                cout << "Enter Email: ";
                cin >> inputEmail;
                cout << "Enter Password: ";
                cin >> inputPw;

                if (admin.login(inputEmail, inputPw)) {
                    cout << "\nLogin Successful!" << endl;
                    admin.displayAdminInfo();
                    Restaurant::displayRevenue();
                    showOrderSummary(*restaurant);
                } else {x
                    cout << "\n>> Incorrect Email or Password! Access Denied." << endl;
                }
                break;
            }

            case 5:
                cout << "Thank you for using our system. Goodbye!" << endl;
                break;
        }
    } while (choice != 5);

    delete restaurant;    
    return 0;
}