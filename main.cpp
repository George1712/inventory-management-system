// g++ -std=c++17 *.cpp -o program
// \.program.exe

#include <iostream>
#include <string>
#include "Inventory.h"
#include "Product.h"
#include "Supplier.h"
#include "Customer.h"
#include "Order.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void handleProductManagement(Inventory& inventory);
void handleSupplierManagement(Inventory& inventory);
void handleCustomerManagement(Inventory& inventory);
void handleOrderManagement(Inventory& inventory);
void handleReports(Inventory& inventory);

int main() {
    Inventory inventory;
    int choice;
    
    cout << "=== INVENTORY MANAGEMENT SYSTEM ===" << endl;
    
    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer
        
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
            case 6:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << endl;
    } while(choice != 6);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Product Management" << endl;
    cout << "2. Supplier Management" << endl;
    cout << "3. Customer Management" << endl;
    cout << "4. Order Management" << endl;
    cout << "5. Reports" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

void handleProductManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== PRODUCT MANAGEMENT =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Find Product by ID" << endl;
        cout << "4. Find Products by Name" << endl;
        cout << "5. View All Products" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                string name, description;
                double price;
                int quantity, supplierId, minStock;
                
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter product description: ";
                getline(cin, description);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter supplier ID: ";
                cin >> supplierId;
                cout << "Enter minimum stock level: ";
                cin >> minStock;
                
                // In a real system, you'd generate unique IDs
                int productId = rand() % 1000 + 1;
                Product newProduct(productId, name, description, price, quantity, supplierId, minStock);
                inventory.addProduct(newProduct);
                
                cout << "Product added successfully with ID: " << productId << endl;
                break;
            }
            case 2: {
                int productId;
                cout << "Enter product ID to remove: ";
                cin >> productId;
                
                if(inventory.removeProduct(productId)) {
                    cout << "Product removed successfully." << endl;
                } else {
                    cout << "Product not found." << endl;
                }
                break;
            }
            case 3: {
                int productId;
                cout << "Enter product ID to find: ";
                cin >> productId;
                
                Product* product = inventory.findProductById(productId);
                if(product) {
                    product->display();
                } else {
                    cout << "Product not found." << endl;
                }
                break;
            }
            case 4: {
                string name;
                cout << "Enter product name to search: ";
                getline(cin, name);
                
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
                // This would need a method to get all products
                cout << "View all products feature would be implemented here." << endl;
                break;
            }
            case 6:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 6);
}

void handleSupplierManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== SUPPLIER MANAGEMENT =====" << endl;
        cout << "1. Add Supplier" << endl;
        cout << "2. Find Supplier by ID" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                string name, phone, email, address;
                
                cout << "Enter supplier name: ";
                getline(cin, name);
                cout << "Enter supplier phone: ";
                getline(cin, phone);
                cout << "Enter supplier email: ";
                getline(cin, email);
                cout << "Enter supplier address: ";
                getline(cin, address);
                
                int supplierId = rand() % 1000 + 1;
                Supplier newSupplier(supplierId, name, phone, email, address);
                inventory.addSupplier(newSupplier);
                
                cout << "Supplier added successfully with ID: " << supplierId << endl;
                break;
            }
            case 2: {
                int supplierId;
                cout << "Enter supplier ID to find: ";
                cin >> supplierId;
                
                Supplier* supplier = inventory.findSupplierById(supplierId);
                if(supplier) {
                    supplier->display();
                } else {
                    cout << "Supplier not found." << endl;
                }
                break;
            }
            case 3:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 3);
}

void handleCustomerManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== CUSTOMER MANAGEMENT =====" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Find Customer by ID" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                string name, phone, email, address;
                
                cout << "Enter customer name: ";
                getline(cin, name);
                cout << "Enter customer phone: ";
                getline(cin, phone);
                cout << "Enter customer email: ";
                getline(cin, email);
                cout << "Enter customer address: ";
                getline(cin, address);
                
                int customerId = rand() % 1000 + 1;
                Customer newCustomer(customerId, name, phone, email, address);
                inventory.addCustomer(newCustomer);
                
                cout << "Customer added successfully with ID: " << customerId << endl;
                break;
            }
            case 2: {
                int customerId;
                cout << "Enter customer ID to find: ";
                cin >> customerId;
                
                Customer* customer = inventory.findCustomerById(customerId);
                if(customer) {
                    customer->display();
                } else {
                    cout << "Customer not found." << endl;
                }
                break;
            }
            case 3:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 3);
}

void handleOrderManagement(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== ORDER MANAGEMENT =====" << endl;
        cout << "1. Create New Order" << endl;
        cout << "2. Process Order" << endl;
        cout << "3. View Customer Orders" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                int customerId;
                cout << "Enter customer ID: ";
                cin >> customerId;
                
                Customer* customer = inventory.findCustomerById(customerId);
                if(!customer) {
                    cout << "Customer not found." << endl;
                    break;
                }
                
                Order* newOrder = inventory.createOrder(customerId);
                if(!newOrder) {
                    cout << "Failed to create order." << endl;
                    break;
                }
                
                cout << "Order created with ID: " << newOrder->getId() << endl;
                
                // Add items to order
                char addMore;
                do {
                    int productId, quantity;
                    cout << "Enter product ID to add to order: ";
                    cin >> productId;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    
                    Product* product = inventory.findProductById(productId);
                    if(product) {
                        if(product->getQuantity() >= quantity) {
                            OrderItem item(productId, product->getName(), quantity, product->getPrice());
                            newOrder->addItem(item);
                            cout << "Product added to order." << endl;
                        } else {
                            cout << "Insufficient stock. Only " << product->getQuantity() << " available." << endl;
                        }
                    } else {
                        cout << "Product not found." << endl;
                    }
                    
                    cout << "Add another product? (y/n): ";
                    cin >> addMore;
                } while(addMore == 'y' || addMore == 'Y');
                
                newOrder->calculateTotal();
                cout << "Order total: $" << newOrder->getTotalAmount() << endl;
                break;
            }
            case 2: {
                int orderId;
                cout << "Enter order ID to process: ";
                cin >> orderId;
                
                if(inventory.processOrder(orderId)) {
                    cout << "Order processed successfully." << endl;
                } else {
                    cout << "Failed to process order. It may not exist or is already processed." << endl;
                }
                break;
            }
            case 3: {
                int customerId;
                cout << "Enter customer ID: ";
                cin >> customerId;
                
                vector<Order> orders = inventory.getOrdersByCustomer(customerId);
                if(orders.empty()) {
                    cout << "No orders found for this customer." << endl;
                } else {
                    for(Order order : orders) {
                        order.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 4:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 4);
}

void handleReports(Inventory& inventory) {
    int choice;
    do {
        cout << "\n===== REPORTS =====" << endl;
        cout << "1. Inventory Value Report" << endl;
        cout << "2. Low Stock Report" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                double totalValue = inventory.calculateTotalInventoryValue();
                cout << "Total Inventory Value: $" << totalValue << endl;
                break;
            }
            case 2: {
                vector<Product*> lowStockProducts = inventory.getLowStockProducts();
                if(lowStockProducts.empty()) {
                    cout << "No products are low on stock." << endl;
                } else {
                    cout << "Low Stock Products:" << endl;
                    for(Product* product : lowStockProducts) {
                        cout << " - " << product->getName() << " (Only " 
                             << product->getQuantity() << " left, minimum: " 
                             << product->getMinStockLevel() << ")" << endl;
                    }
                }
                break;
            }
            case 3:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 3);
}