#include <iostream>
#include <string>
#include <limits>

#include "Inventory.h"
#include "Product.h"
#include "Supplier.h"
#include "Customer.h"
#include "Order.h"

using namespace std;

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
    cout << "Initializing system..." << endl;
    
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
        cout << "9. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
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
                
                // Generate a product ID (in a real system, this would be auto-incremented)
                int productId = rand() % 1000 + 100;
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
                int productId, quantity;
                cout << "Enter product ID to restock: ";
                cin >> productId;
                cout << "Enter quantity to add: ";
                cin >> quantity;
                
                if(inventory.restockProduct(productId, quantity)) {
                    cout << "Product restocked successfully." << endl;
                } else {
                    cout << "Failed to restock product." << endl;
                }
                break;
            }
            case 6: {
                int productId, quantity;
                cout << "Enter product ID to sell: ";
                cin >> productId;
                cout << "Enter quantity to sell: ";
                cin >> quantity;
                
                if(inventory.sellProduct(productId, quantity)) {
                    cout << "Product sold successfully." << endl;
                } else {
                    cout << "Failed to sell product. Check if product exists and has sufficient stock." << endl;
                }
                break;
            }
            case 7: {
                int productId, newMinStock;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter new minimum stock level: ";
                cin >> newMinStock;
                
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
            case 9:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 9);
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
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
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
                
                int supplierId = rand() % 1000 + 100;
                Supplier newSupplier(supplierId, name, phone, email, address);
                inventory.addSupplier(newSupplier);
                
                cout << "Supplier added successfully with ID: " << supplierId << endl;
                break;
            }
            case 2: {
                int supplierId;
                cout << "Enter supplier ID to remove: ";
                cin >> supplierId;
                
                if(inventory.removeSupplier(supplierId)) {
                    cout << "Supplier removed successfully." << endl;
                } else {
                    cout << "Supplier not found." << endl;
                }
                break;
            }
            case 3: {
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
            case 4: {
                string name;
                cout << "Enter supplier name to search: ";
                getline(cin, name);
                
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
            case 6:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 6);
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
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
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
                
                int customerId = rand() % 1000 + 100;
                Customer newCustomer(customerId, name, phone, email, address);
                inventory.addCustomer(newCustomer);
                
                cout << "Customer added successfully with ID: " << customerId << endl;
                break;
            }
            case 2: {
                int customerId;
                cout << "Enter customer ID to remove: ";
                cin >> customerId;
                
                if(inventory.removeCustomer(customerId)) {
                    cout << "Customer removed successfully." << endl;
                } else {
                    cout << "Customer not found." << endl;
                }
                break;
            }
            case 3: {
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
            case 4: {
                string name;
                cout << "Enter customer name to search: ";
                getline(cin, name);
                
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
            case 6:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 6);
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
        cout << "8. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch(choice) {
            case 1: {
                int customerId;
                cout << "Enter customer ID: ";
                cin >> customerId;
                
                Order* newOrder = inventory.createOrder(customerId);
                if(newOrder) {
                    cout << "Order created successfully with ID: " << newOrder->getId() << endl;
                } else {
                    cout << "Failed to create order. Customer not found." << endl;
                }
                break;
            }
            case 2: {
                int orderId, productId, quantity;
                cout << "Enter order ID: ";
                cin >> orderId;
                cout << "Enter product ID: ";
                cin >> productId;
                cout << "Enter quantity: ";
                cin >> quantity;
                
                if(inventory.addItemToOrder(orderId, productId, quantity)) {
                    cout << "Item added to order successfully." << endl;
                } else {
                    cout << "Failed to add item to order." << endl;
                }
                break;
            }
            case 3: {
                int orderId;
                cout << "Enter order ID to process: ";
                cin >> orderId;
                
                if(inventory.processOrder(orderId)) {
                    cout << "Order processed successfully." << endl;
                } else {
                    cout << "Failed to process order." << endl;
                }
                break;
            }
            case 4: {
                int orderId;
                cout << "Enter order ID to cancel: ";
                cin >> orderId;
                
                if(inventory.cancelOrder(orderId)) {
                    cout << "Order cancelled successfully." << endl;
                } else {
                    cout << "Failed to cancel order." << endl;
                }
                break;
            }
            case 5: {
                int orderId;
                cout << "Enter order ID to find: ";
                cin >> orderId;
                
                Order* order = inventory.findOrderById(orderId);
                if(order) {
                    order->display();
                } else {
                    cout << "Order not found." << endl;
                }
                break;
            }
            case 6: {
                int customerId;
                cout << "Enter customer ID: ";
                cin >> customerId;
                
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
                string status;
                cout << "Enter status to filter by (PENDING, PROCESSING, COMPLETED, CANCELLED): ";
                getline(cin, status);
                
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
            case 8:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 8);
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
        cout << "7. Back to Main Menu" << endl;
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
                int customerId;
                cout << "Enter customer ID: ";
                cin >> customerId;
                inventory.generateCustomerReport(customerId);
                break;
            }
            case 5:
                inventory.generateSupplierReport();
                break;
            case 6: {
                int orderId;
                cout << "Enter order ID: ";
                cin >> orderId;
                cout << inventory.getOrderSummary(orderId) << endl;
                break;
            }
            case 7:
                cout << "Returning to main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 7);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

