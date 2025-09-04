#include "Inventory.h"


// Constructor
Inventory::Inventory() : nextProductId(1), nextOrderId(1) {}

// Product Management
void Inventory::addProduct(Product product) {
    products.push_back(product);
}
bool Inventory::removeProduct(int productId) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getId() == productId) {
            products.erase(it);
            return true;
        }
    }
    return false;
}
Product* Inventory::findProductById(int productId) {
    for (auto& product : products) {
        if (product.getId() == productId) {
            return &product;
        }
    }
    return nullptr;
}
vector<Product*> Inventory::findProductsByName(string name) {
    vector<Product*> result;
    for (auto& product : products) {
        if (product.getName() == name) {
            result.push_back(&product);
        }
    }
    return result;
}
vector<Product*> Inventory::getLowStockProducts() {
    vector<Product*> result;
    for (auto& product : products) {
        if (product.isLowStock()) {
            result.push_back(&product);
        }
    }
    return result;
}











// Adds a new supplier to the system
void Inventory::addSupplier(Supplier supplier) {
    suppliers.push_back(supplier);
}

// Finds a supplier by ID (returns nullptr if not found)
Supplier* Inventory::findSupplierById(int supplierId) {
    for (auto& supplier : suppliers) {
        if (supplier.getId() == supplierId) {
            return &supplier;
        }
    }
    return nullptr;
}

// Adds a new customer to the system
void Inventory::addCustomer(Customer customer) {
    customers.push_back(customer);
}

// Finds a customer by ID (returns nullptr if not found)
Customer* Inventory::findCustomerById(int customerId) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            return &customer;
        }
    }
    return nullptr;
}

// Creates a new order for a customer
Order* Inventory::createOrder(int customerId) {
    Customer* customer = findCustomerById(customerId);
    if (customer) {
        Order newOrder(nextOrderId++, customerId, customer->getName(), "2023-12-19");
        orders.push_back(newOrder);
        return &orders.back();
    }
    return nullptr;
}

// Processes an order (marks it as completed and updates inventory)
bool Inventory::processOrder(int orderId) {
    for (auto& order : orders) {
        if (order.getId() == orderId && order.getStatus() == "PENDING") {
            // Update inventory quantities
            for (const auto& item : order.getItems()) {
                Product* product = findProductById(item.getItemId());
                if (product) {
                    product->updateQuantity(-item.getQuantity());
                }
            }
            order.setStatus("COMPLETED");
            return true;
        }
    }
    return false;
}

// Returns all orders placed by a specific customer
vector<Order> Inventory::getOrdersByCustomer(int customerId) {
    vector<Order> result;
    for (auto& order : orders) {
        if (order.getCustomerId() == customerId) {
            result.push_back(order);
        }
    }
    return result;
}

// Calculates the total value of all products in inventory
double Inventory::calculateTotalInventoryValue() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product.getPrice() * product.getQuantity();
    }
    return total;
}

// Generates and displays a comprehensive inventory report
void Inventory::generateInventoryReport() const {
    cout << "=== INVENTORY REPORT ===" << endl;
    cout << "Total Products: " << products.size() << endl;
    cout << "Total Inventory Value: $" << calculateTotalInventoryValue() << endl;
    cout << "Low Stock Items: " << endl;
    
    for (const auto& product : products) {
        if (product.isLowStock()) {
            cout << " - " << product.getName() << " (Only " << product.getQuantity() << " left)" << endl;
        }
    }
}