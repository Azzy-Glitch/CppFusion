#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

// Cross-platform time formatting
string format_time(time_t time)
{
    tm local_time;
    tm *temp = localtime(&time);

    if (temp)
        local_time = *temp;
    else
        return "Invalid Time";

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return string(buffer);
}

struct Product
{
    int productID;
    string name;
    string category;
};

struct Order
{
    int orderID;
    int productID;
    int quantity;
    string customerID;
    time_t orderDate;
};

// Function prototypes
void displayMenu();
void addProduct(vector<Product> &products,
                unordered_set<int> &uniqueProductIDs,
                map<int, int> &productStock);
void addCustomer(unordered_map<string, string> &customerData);
void placeOrder(list<Order> &orderHistory,
                multimap<string, Order> &customerOrders,
                map<int, int> &productStock,
                const unordered_map<string, string> &customerData,
                deque<string> &recentCustomers);
void viewRecentCustomers(const deque<string> &recentCustomers);
void viewProductStock(const map<int, int> &productStock);
void viewCustomerOrders(const multimap<string, Order> &customerOrders);
void checkProductExistence(const unordered_set<int> &uniqueProductIDs);
void clearScreen();
bool isValidCustomerID(const string &id);

int main()
{
    vector<Product> products;
    deque<string> recentCustomers;
    list<Order> orderHistory;
    map<int, int> productStock;
    multimap<string, Order> customerOrders;
    unordered_map<string, string> customerData;
    unordered_set<int> uniqueProductIDs;

    int choice;
    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            addProduct(products, uniqueProductIDs, productStock);
            break;
        case 2:
            addCustomer(customerData);
            break;
        case 3:
            placeOrder(orderHistory, customerOrders, productStock,
                       customerData, recentCustomers);
            break;
        case 4:
            viewRecentCustomers(recentCustomers);
            break;
        case 5:
            viewProductStock(productStock);
            break;
        case 6:
            viewCustomerOrders(customerOrders);
            break;
        case 7:
            checkProductExistence(uniqueProductIDs);
            break;
        case 8:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();
    } while (choice != 8);

    return 0;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu()
{
    cout << "\n===== Inventory Management System =====\n";
    cout << "1. Add New Product\n";
    cout << "2. Add New Customer\n";
    cout << "3. Place Order\n";
    cout << "4. View Recent Customers\n";
    cout << "5. View Product Stock Levels\n";
    cout << "6. View Customer Orders\n";
    cout << "7. Check Product Existence\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

bool isValidCustomerID(const string &id)
{
    return id.length() == 4 &&
           id[0] == 'C' &&
           all_of(id.begin() + 1, id.end(), ::isdigit);
}

void addProduct(vector<Product> &products,
                unordered_set<int> &uniqueProductIDs,
                map<int, int> &productStock)
{
    Product newProduct;
    int initialStock;

    cout << "\nEnter Product ID: ";
    while (!(cin >> newProduct.productID) ||
           uniqueProductIDs.count(newProduct.productID))
    {
        cout << "Invalid or duplicate ID! Enter valid Product ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter Product Name: ";
    getline(cin, newProduct.name);

    cout << "Enter Product Category: ";
    getline(cin, newProduct.category);

    cout << "Enter Initial Stock Quantity: ";
    while (!(cin >> initialStock) || initialStock < 0)
    {
        cout << "Invalid quantity! Enter valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    products.push_back(newProduct);
    productStock[newProduct.productID] = initialStock;
    uniqueProductIDs.insert(newProduct.productID);
    cout << "Product added successfully!\n";
}

void addCustomer(unordered_map<string, string> &customerData)
{
    string customerID, name;

    cout << "\nEnter Customer ID (format CXXX): ";
    getline(cin, customerID);

    if (!isValidCustomerID(customerID))
    {
        cout << "Invalid ID format! Use C followed by 3 digits (e.g., C001)\n";
        return;
    }

    if (customerData.count(customerID))
    {
        cout << "Customer ID already exists!\n";
        return;
    }

    cout << "Enter Customer Name: ";
    getline(cin, name);

    customerData[customerID] = name;
    cout << "Customer added successfully!\n";
}

void placeOrder(list<Order> &orderHistory,
                multimap<string, Order> &customerOrders,
                map<int, int> &productStock,
                const unordered_map<string, string> &customerData,
                deque<string> &recentCustomers)
{
    Order newOrder;
    string customerID;
    int productID, quantity;

    cout << "\nEnter Customer ID: ";
    getline(cin, customerID);

    if (!customerData.count(customerID))
    {
        cout << "Customer not found!\n";
        return;
    }

    cout << "Enter Product ID: ";
    while (!(cin >> productID) || !productStock.count(productID))
    {
        cout << "Invalid or unknown Product ID! Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Quantity: ";
    while (!(cin >> quantity) || quantity <= 0)
    {
        cout << "Invalid quantity! Enter valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (productStock[productID] < quantity)
    {
        cout << "Insufficient stock! Available: "
             << productStock[productID] << "\n";
        return;
    }

    // Generate order ID
    newOrder.orderID = orderHistory.empty() ? 1 : orderHistory.back().orderID + 1;
    newOrder.productID = productID;
    newOrder.quantity = quantity;
    newOrder.customerID = customerID;
    newOrder.orderDate = time(nullptr);

    // Update data structures
    orderHistory.push_back(newOrder);
    customerOrders.emplace(customerID, newOrder);
    productStock[productID] -= quantity;

    // Update recent customers (unique entries, max 5)
    auto it = find(recentCustomers.begin(), recentCustomers.end(), customerID);
    if (it != recentCustomers.end())
    {
        recentCustomers.erase(it);
    }
    recentCustomers.push_front(customerID);
    if (recentCustomers.size() > 5)
    {
        recentCustomers.pop_back();
    }

    cout << "Order placed successfully! Order ID: "
         << newOrder.orderID << "\n";
}

void viewRecentCustomers(const deque<string> &recentCustomers)
{
    cout << "\n===== Recent Customers =====\n";
    if (recentCustomers.empty())
    {
        cout << "No recent customers found.\n";
        return;
    }

    for (const auto &customer : recentCustomers)
    {
        cout << "- " << customer << "\n";
    }
}

void viewProductStock(const map<int, int> &productStock)
{
    cout << "\n===== Product Stock Levels =====\n";
    if (productStock.empty())
    {
        cout << "No products in inventory.\n";
        return;
    }

    for (const auto &pair : productStock)
    {
        cout << "Product #" << pair.first << ": " << pair.second << " units\n";
    }
}

void viewCustomerOrders(const multimap<string, Order> &customerOrders)
{
    string customerID;
    cout << "\nEnter Customer ID to view orders: ";
    getline(cin, customerID);

    auto range = customerOrders.equal_range(customerID);
    if (range.first == range.second)
    {
        cout << "No orders found for this customer.\n";
        return;
    }

    cout << "\n===== Orders for Customer " << customerID << " =====\n";
    for (auto it = range.first; it != range.second; ++it)
    {
        const Order &order = it->second;
        cout << "Order #" << order.orderID
             << "\n- Product: " << order.productID
             << "\n- Quantity: " << order.quantity
             << "\n- Date: " << format_time(order.orderDate) << "\n\n";
    }
}

void checkProductExistence(const unordered_set<int> &uniqueProductIDs)
{
    int productID;
    cout << "\nEnter Product ID to check: ";
    while (!(cin >> productID))
    {
        cout << "Invalid input! Enter numeric Product ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Product ID " << productID << " is "
         << (uniqueProductIDs.count(productID) ? "valid" : "invalid") << "\n";
}