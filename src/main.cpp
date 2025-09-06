#include <iostream>
#include <string>
#include <climits>
#include <limits>

#include "Inventory.h"
#include "Product.h"
#include "Supplier.h"
#include "Customer.h"
#include "Order.h"

using namespace std;

// helper functions to validate input
int getValidatedInt(const string& prompt, int min = INT_MIN, int max = INT_MAX);
double getValidatedDouble(const string& prompt, double min = 0.0);
string getValidatedString(const string& prompt, bool allowEmpty = false);
string getValidatedStatus(const string& prompt);
bool getYesNoInput(const string& prompt);

void displayMainMenu();
void handleProductManagement(Inventory& inventory);
void handleSupplierManagement(Inventory& inventory);
void handleCustomerManagement(Inventory& inventory);
void handleOrderManagement(Inventory& inventory);
void handleReports(Inventory& inventory);
void clearInputBuffer();

int main() {
    Inventory inventory;
    int choice;
    
    cout << "=== INVENTORY MANAGEMENT SYSTEM ===" << endl;
    
    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                handleProductManagement(inventory);
                break;
            case 2:
                handleSupplierManagement(inventory);
                break;
            case 3:
                handleCustomerManagement(inventory);
                break;
            case 4:
                handleOrderManagement(inventory);
                break;
            case 5:
                handleReports(inventory);
                break;
            case 0:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << endl;
    } while(choice);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Product Management" << endl;
    cout << "2. Supplier Management" << endl;
    cout << "3. Customer Management" << endl;
    cout << "4. Order Management" << endl;
    cout << "5. Reports" << endl;
    cout << "0. Exit" << endl;
}

void handleProductManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== PRODUCT MANAGEMENT =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Find Product by ID" << endl;
        cout << "4. Find Products by Name" << endl;
        cout << "5. Restock Product" << endl;
        cout << "6. Sell Product" << endl;
        cout << "7. Update Minimum Stock Level" << endl;
        cout << "8. View Low Stock Products" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                string name = getValidatedString("Enter product name: ");
                string description = getValidatedString("Enter product description: ", true);
                double price = getValidatedDouble("Enter price: ", 0.01);
                int quantity = getValidatedInt("Enter quantity: ", 0);
                int supplierId = getValidatedInt("Enter supplier ID: ", 1);
                if (!inventory.findSupplierById(supplierId)) {
                    cout << "Error: Supplier with ID " << supplierId << " does not exist." << endl;
                    break;
                }
                int minStock = getValidatedInt("Enter minimum stock level: ", 0);

                Product newProduct(0, name, description, price, quantity, supplierId, minStock);
                int productId = inventory.addProduct(newProduct);
                
                cout << "Product added successfully with ID: " << productId << endl;
                break;
            }
            case 2: {
                int productId = getValidatedInt("Enter product ID to remove: ", 1);
                if (getYesNoInput("Are you sure you want to remove this product?")) {
                    if(inventory.removeProduct(productId)) {
                        cout << "Product removed successfully." << endl;
                    } else {
                        cout << "Product not found." << endl;
                    }
                } else {
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
            case 3: {
                int productId = getValidatedInt("Enter product ID to find: ", 1);
                
                Product* product = inventory.findProductById(productId);
                if(product) {
                    product->display();
                } else {
                    cout << "Product not found." << endl;
                }
                break;
            }
            case 4: {
                string name = getValidatedString("Enter product name to search: ");
                
                vector<Product*> products = inventory.findProductsByName(name);
                if(products.empty()) {
                    cout << "No products found with that name." << endl;
                } else {
                    for(Product* product : products) {
                        product->display();
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
                int productId = getValidatedInt("Enter product ID to restock: ", 1);
                int quantity = getValidatedInt("Enter quantity to add: ", 1);
                
                if(inventory.restockProduct(productId, quantity)) {
                    cout << "Product restocked successfully." << endl;
                } else {
                    cout << "Failed to restock product." << endl;
                }
                break;
            }
            case 6: {
                int productId = getValidatedInt("Enter product ID to sell: ", 1);
                int quantity = getValidatedInt("Enter quantity to sell: ", 1);
                
                if(inventory.sellProduct(productId, quantity)) {
                    cout << "Product sold successfully." << endl;
                } else {
                    cout << "Failed to sell product. Check if product exists and has sufficient stock." << endl;
                }
                break;
            }
            case 7: {
                int productId = getValidatedInt("Enter product ID: ", 1);
                int newMinStock = getValidatedInt("Enter new minimum stock level: ", 0);
                
                if(inventory.updateProductMinStockLevel(productId, newMinStock)) {
                    cout << "Minimum stock level updated successfully." << endl;
                } else {
                    cout << "Failed to update minimum stock level." << endl;
                }
                break;
            }
            case 8: {
                vector<Product*> lowStockProducts = inventory.getLowStockProducts();
                if(lowStockProducts.empty()) {
                    cout << "No products are low on stock." << endl;
                } else {
                    cout << "Low Stock Products:" << endl;
                    for(Product* product : lowStockProducts) {
                        product->display();
                        cout << endl;
                    }
                }
                break;
            }
            case 0:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice);
}

void handleSupplierManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== SUPPLIER MANAGEMENT =====" << endl;
        cout << "1. Add Supplier" << endl;
        cout << "2. Remove Supplier" << endl;
        cout << "3. Find Supplier by ID" << endl;
        cout << "4. Find Suppliers by Name" << endl;
        cout << "5. View All Suppliers" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                string name = getValidatedString("Enter supplier name: ");
                string phone = getValidatedString("Enter supplier phone: ");
                string email = getValidatedString("Enter supplier email: ");
                string address = getValidatedString("Enter supplier address: ");
                
                Supplier newSupplier(0, name, phone, email, address);
                int supplierId = inventory.addSupplier(newSupplier);
                
                cout << "Supplier added successfully with ID: " << supplierId << endl;
                break;
            }
            case 2: {
                int supplierId = getValidatedInt("Enter supplier ID to remove: ", 1);
                
                if (getYesNoInput("Are you sure you want to remove this supplier?")) {
                    if(inventory.removeSupplier(supplierId)) {
                        cout << "Supplier removed successfully." << endl;
                    } else {
                        cout << "Supplier not found." << endl;
                    }
                } else {
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
            case 3: {
                int supplierId = getValidatedInt("Enter supplier ID to find: ", 1);
                
                Supplier* supplier = inventory.findSupplierById(supplierId);
                if(supplier) {
                    supplier->display();
                } else {
                    cout << "Supplier not found." << endl;
                }
                break;
            }
            case 4: {
                string name = getValidatedString("Enter supplier name: ");
                
                vector<Supplier*> suppliers = inventory.findSupplierByName(name);
                if(suppliers.empty()) {
                    cout << "No suppliers found with that name." << endl;
                } else {
                    for(Supplier* supplier : suppliers) {
                        supplier->display();
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
                vector<Supplier> suppliers = inventory.getAllSuppliers();
                if(suppliers.empty()) {
                    cout << "No suppliers found." << endl;
                } else {
                    for(const Supplier& supplier : suppliers) {
                        supplier.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 0:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice);
}

void handleCustomerManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== CUSTOMER MANAGEMENT =====" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Remove Customer" << endl;
        cout << "3. Find Customer by ID" << endl;
        cout << "4. Find Customers by Name" << endl;
        cout << "5. View All Customers" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                string name = getValidatedString("Enter customer name: ");
                string phone = getValidatedString("Enter customer phone: ");
                string email = getValidatedString("Enter customer email: ");
                string address = getValidatedString("Enter customer address: ");
                
                Customer newCustomer(0, name, phone, email, address);
                int customerId = inventory.addCustomer(newCustomer);
                
                cout << "Customer added successfully with ID: " << customerId << endl;
                break;
            }
            case 2: {
                int customerId = getValidatedInt("Enter customer ID to remove: ", 1);
                
                if (getYesNoInput("Are you sure you want to remove this customer?")) {
                    if(inventory.removeCustomer(customerId)) {
                        cout << "Customer removed successfully." << endl;
                    } else {
                        cout << "Customer not found." << endl;
                    }
                } else {
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
            case 3: {
                int customerId = getValidatedInt("Enter customer ID to find: ", 1);
                
                Customer* customer = inventory.findCustomerById(customerId);
                if(customer) {
                    customer->display();
                } else {
                    cout << "Customer not found." << endl;
                }
                break;
            }
            case 4: {
                string name = getValidatedString("Enter customer name: ");
                
                vector<Customer*> customers = inventory.findCustomerByName(name);
                if(customers.empty()) {
                    cout << "No customers found with that name." << endl;
                } else {
                    for(Customer* customer : customers) {
                        customer->display();
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
                vector<Customer> customers = inventory.getAllCustomers();
                if(customers.empty()) {
                    cout << "No customers found." << endl;
                } else {
                    for(const Customer& customer : customers) {
                        customer.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 0:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice);
}

void handleOrderManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== ORDER MANAGEMENT =====" << endl;
        cout << "1. Create New Order" << endl;
        cout << "2. Add Item to Order" << endl;
        cout << "3. Process Order" << endl;
        cout << "4. Cancel Order" << endl;
        cout << "5. Find Order by ID" << endl;
        cout << "6. View Customer Orders" << endl;
        cout << "7. View Orders by Status" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                int customerId = getValidatedInt("Enter customer ID: ", 1);
                                
                Order* newOrder = inventory.createOrder(customerId);
                if(newOrder) {
                    cout << "Order created successfully with ID: " << newOrder->getId() << endl;
                } else {
                    cout << "Failed to create order. Customer not found." << endl;
                }
                break;
            }
            case 2: {
                int orderId = getValidatedInt("Enter order ID: ", 1);
                if (!inventory.findOrderById(orderId)) {
                    cout << "Error: Order with ID " << orderId << " does not exist." << endl;
                    break;
                }
                int productId = getValidatedInt("Enter product ID: ", 1);
                if (!inventory.findProductById(productId)) {
                    cout << "Error: Product with ID " << productId << " does not exist." << endl;
                    break;
                }
                int quantity = getValidatedInt("Enter quantity: ", 1);

                if(inventory.addItemToOrder(orderId, productId, quantity)) {
                    cout << "Item added to order successfully." << endl;
                } else {
                    cout << "Failed to add item to order." << endl;
                }
                break;
            }
            case 3: {
                int orderId = getValidatedInt("Enter order ID to process: ", 1);                
                if (!inventory.findOrderById(orderId)) {
                    cout << "Error: Order with ID " << orderId << " does not exist." << endl;
                    break;
                }
                if(inventory.processOrder(orderId)) {
                    cout << "Order processed successfully." << endl;
                } else {
                    cout << "Failed to process order." << endl;
                }
                break;
            }
            case 4: {
                int orderId = getValidatedInt("Enter order ID to cancel: ", 1);
                if (!inventory.findOrderById(orderId)) {
                    cout << "Error: Order with ID " << orderId << " does not exist." << endl;
                    break;
                }
                if (getYesNoInput("Are you sure you want to cancel this order?")) {
                    if(inventory.cancelOrder(orderId)) {
                        cout << "Order cancelled successfully." << endl;
                    } else {
                        cout << "Failed to cancel order." << endl;
                    }
                } else {
                    cout << "Operation cancelled." << endl;
                }

                break;
            }
            case 5: {
                int orderId = getValidatedInt("Enter order ID to find: ", 1);                
                Order* order = inventory.findOrderById(orderId);
                if(order) {
                    order->display();
                } else {
                    cout << "Order not found." << endl;
                }
                break;
            }
            case 6: {
                int customerId = getValidatedInt("Enter customer ID: ", 1);

                vector<Order> orders = inventory.getOrdersByCustomer(customerId);
                if(orders.empty()) {
                    cout << "No orders found for this customer." << endl;
                } else {
                    for(const Order& order : orders) {
                        order.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 7: {
                string status = getValidatedStatus("Enter status to filter by (PENDING, COMPLETED, CANCELLED): ");

                vector<Order> orders = inventory.getOrdersByStatus(status);
                if(orders.empty()) {
                    cout << "No orders found with status: " << status << endl;
                } else {
                    for(const Order& order : orders) {
                        order.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 0:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice);
}

void handleReports(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== REPORTS =====" << endl;
        cout << "1. Inventory Report" << endl;
        cout << "2. Sales Report" << endl;
        cout << "3. Low Stock Report" << endl;
        cout << "4. Customer Report" << endl;
        cout << "5. Supplier Report" << endl;
        cout << "6. Order Summary" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                inventory.generateInventoryReport();
                break;
            case 2:
                inventory.generateSalesReport();
                break;
            case 3:
                inventory.generateLowStockReport();
                break;
            case 4: {
                int customerId = getValidatedInt("Enter customer ID: ", 1);
                 if (!inventory.findCustomerById(customerId)) {
                    cout << "Error: Customer with ID " << customerId << " does not exist." << endl;
                    break;
                }
                inventory.generateCustomerReport(customerId);
                break;
            }
            case 5:
                inventory.generateSupplierReport();
                break;
            case 6: {
                int orderId = getValidatedInt("Enter order ID: ", 1);
                if (!inventory.findOrderById(orderId)) {
                    cout << "Error: Order with ID " << orderId << " does not exist." << endl;
                    break;
                }
                cout << inventory.getOrderSummary(orderId) << endl;
                break;
            }
            case 0:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice);
}


void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Validation Functions
int getValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter an integer between "
                 << min << " and " << max << "." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}
double getValidatedDouble(const string& prompt, double min) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a number greater than or equal to " << min << "." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}
string getValidatedString(const string& prompt, bool allowEmpty) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty() || allowEmpty) {
            return value;
        } else {
            cout << "Invalid input. This field cannot be empty." << endl;
        }
    }
}
string getValidatedStatus(const string& prompt) {
    string status;
    while (true) {
        cout << prompt;
        getline(cin, status);
        for (char &c : status) {
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
        }
        if (status == "PENDING" || status == "COMPLETED" || status == "CANCELLED") {
            return status;
        } else {
            cout << "Invalid status. Please enter PENDING, COMPLETED, or CANCELLED." << endl;
        }
    }
}
bool getYesNoInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt << " (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") {
            return true;
        } else if (input == "n" || input == "N") {
            return false;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        }
    }
}