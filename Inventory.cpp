#include "Inventory.h"

// Constructor
Inventory::Inventory() : 
nextProductId(1), nextOrderId(1),
nextSupplierId(1), nextCustomerId(1) {}


// -------------- Product Management -------------- //

void Inventory::addProduct(Product product) {
    int id = nextProductId++;
    product.setId(id);

    products[id] = product;
    string name = product.getName();
    productNameIds[name].insert(id);

    updateLowStockStatus(id, product.getQuantity(), product.getMinStockLevel());
}
bool Inventory::removeProduct(int productId) {
    auto productIt = products.find(productId); // = [id, Product]
    if (productIt != products.end()) {
        // removing name form id
        string name = (productIt->second).getName();
        auto nameIt = productNameIds.find(name); // = [string, set<id>]
        if (nameIt != productNameIds.end()) {
            nameIt->second.erase(productId);
            if (nameIt->second.empty()) {
                productNameIds.erase(nameIt);
            }
        }
        // remove product id 
        lowStockProductIds.erase(productId);
        products.erase(productIt);
        return true;
    }
    return false;
}
Product* Inventory::findProductById(int productId) const {
    auto it = products.find(productId);
    if (it != products.end()) {
        return const_cast<Product*>(&(it->second));
    }
    return nullptr;
}
vector<Product*> Inventory::findProductsByName(string name) const {
    vector<Product*> result;
    auto it = productNameIds.find(name);
    if (it != productNameIds.end()) {
        for (int id : it->second) {
            result.push_back(const_cast<Product*>(&products.at(id)));
        }
    }
    return result;
}
void Inventory::updateLowStockStatus(int productId, int newQuantity, int minStockLevel) {
    if (newQuantity < minStockLevel) {
        lowStockProductIds.insert(productId);
    } else {
        lowStockProductIds.erase(productId);
    }
}
bool Inventory::restockProduct(int productId, int quantity) {
    if (quantity <= 0) return false;
    Product* product = findProductById(productId);
    if (product) {
        product->updateQuantity(quantity);
        updateLowStockStatus(productId, product->getQuantity(), product->getMinStockLevel());
        return true;
    }
    return false;
}
bool Inventory::sellProduct(int productId, int quantity) {
    if (quantity <= 0) return false;
    Product* product = findProductById(productId);
    if (product && product->getQuantity() >= quantity) {
        product->updateQuantity(-quantity);
        updateLowStockStatus(productId, product->getQuantity(), product->getMinStockLevel());
        return true;
    }
    return false;
}
bool Inventory::updateProductMinStockLevel(int productId, int newMinStockLevel) {
    if (newMinStockLevel < 0) {
        return false;
    }
    auto it = products.find(productId);
    if (it == products.end()) {
        return false;
    }
    it->second.setMinStockLevel(newMinStockLevel);
    updateLowStockStatus(productId, it->second.getQuantity(), newMinStockLevel);
    return true;
}
vector<Product*> Inventory::getLowStockProducts() const {
    vector<Product*> result;
    for (auto id : lowStockProductIds) {
        auto it = products.find(id);
        if (it != products.end()) {
            result.push_back(const_cast<Product*>(&(it->second)));
        }
    }
    return result;
}


// -------------- Supplier Management -------------- //

void Inventory::addSupplier(Supplier supplier) {
    int id = nextSupplierId++;
    supplier.setId(id);

    suppliers[id] = supplier;
    string name = supplier.getName();
    supplierNameIds[name].insert(id);
}
bool Inventory::removeSupplier(int supplierId) {
    auto supplierIt = suppliers.find(supplierId);
    if (supplierIt != suppliers.end()) {
        // remove name from id
        string name = (supplierIt->second).getName();
        auto nameIt = supplierNameIds.find(name);
        if (nameIt != supplierNameIds.end()) {
            nameIt->second.erase(supplierId);
            if (nameIt->second.empty()) {
                supplierNameIds.erase(nameIt);
            }
        }
        // remove supplier id
        suppliers.erase(supplierIt);
        return true;
    }
    return false;
}
Supplier* Inventory::findSupplierById(int supplierId) const {
    auto it = suppliers.find(supplierId);
    if (it != suppliers.end()) {
        return const_cast<Supplier*>(&(it->second));
    }
    return nullptr;
}
vector<Supplier*> Inventory::findSupplierByName(string name) const {
    vector<Supplier*> result;
    auto it = supplierNameIds.find(name);
    if (it != supplierNameIds.end()) {
        for (int id : it->second) {
            result.push_back(const_cast<Supplier*>(&suppliers.at(id)));
        }
    }
    return result;
}
vector<Supplier> Inventory::getAllSuppliers() const {
    vector<Supplier> result;
    for (auto it : suppliers) {
        result.push_back(it.second);
    }
    return result;
}


// -------------- Customer Management -------------- //

void Inventory::addCustomer(Customer customer) {
    int id = nextCustomerId++;
    customer.setId(id);
    
    customers[id] = customer;
    string name = customer.getName();
    customerNameIds[name].insert(id);
}
bool Inventory::removeCustomer(int customerId) {
    auto customerIt = customers.find(customerId);
    if (customerIt != customers.end()) {
        string name = (customerIt->second).getName();
        auto nameIt = customerNameIds.find(name);
        if (nameIt != customerNameIds.end()) {
            nameIt->second.erase(customerId);
            if (nameIt->second.empty()) {
                customerNameIds.erase(nameIt);
            }
        }
        // remove supplier id
        customers.erase(customerIt);
        return true;
    }
    return false;
}

Customer* Inventory::findCustomerById(int customerId) const {
    auto it = customers.find(customerId);
    if (it != customers.end()) {
        return const_cast<Customer*>(&(it->second));
    }
    return nullptr;
}
vector<Customer*> Inventory::findCustomerByName(string name) const {
    vector<Customer*> result;
    auto it = customerNameIds.find(name);
    if (it != customerNameIds.end()) {
        for (int id : it->second) {
            result.push_back(const_cast<Customer*>(&customers.at(id)));
        }
    }
    return result;
}
vector<Customer> Inventory::getAllCustomers() const {
    vector<Customer> result;
    for (auto it : customers) {
        result.push_back(it.second);
    }
    return result;
}


// -------------- Order Management -------------- //

// Utility Method
string Inventory::getCurrentDateTime() const {
    using namespace chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm local_tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&local_tm, "%d-%m-%y %H:%M:%S");
    return oss.str();
}

Order* Inventory::createOrder(int customerId) {
    Customer* customer = findCustomerById(customerId);
    if (!customer) {
        return nullptr; // Customer doesn't exist
    }
    int orderId = nextOrderId++;
    Order newOrder(orderId, customerId, customer->getName(), getCurrentDateTime());
    orders[orderId] = newOrder;
    customer->addOrderToHistory(orderId);
    customerOrders[customerId].insert(orderId);
    return &orders[orderId];
}
bool Inventory::addItemToOrder(int orderId, int productId, int quantity) {
    Order *order = findOrderById(orderId);
    Product* product = findProductById(productId);
    if (!order || !product || quantity <= 0) {
        return false; // Invalid
    }
    if (!order->isPending()) {
        return false; // completed or cancelled order (can't modify)
    }
    if (product->getQuantity() < quantity) {
        return false;
    }
    OrderItem item(productId, product->getName(), quantity, product->getPrice());
    order->addItem(item);
    return true;
}
bool Inventory::updateOrderItemQuantity(int orderId, int productId, int newQuantity) {
    Order* order = findOrderById(orderId);
    Product* product = findProductById(productId);
    if (!order || !product || newQuantity <= 0 || !order->isPending()) {
        return false;
    }
    if (product -> getQuantity() < newQuantity) {
        return false;
    }
    return order -> updateItemQuantity(productId, newQuantity);
}
bool Inventory::processOrder(int orderId) {
    auto orderIt = orders.find(orderId);
    if (orderIt == orders.end() || !orderIt->second.isPending()) {
        return false;
    }
    Order &order = orderIt->second;
    vector<OrderItem> orderItems = order.getItems();
    for (const auto &item : orderItems) {
        Product* product = findProductById(item.getItemId());
        if (!product || product->getQuantity() < item.getQuantity()) {
            return false;
        }
    }
    for (const auto &item : orderItems) {
        sellProduct(item.getItemId(), item.getQuantity());
    }
    order.setStatus("COMPLETED");
    return true;
}
bool Inventory::cancelOrder(int orderId) {
    auto orderIt = orders.find(orderId);
    if (orderIt == orders.end() || !orderIt->second.isPending()) {
        return false;
    }
    orderIt->second.setStatus("CANCELLED");
    return true;
}
Order* Inventory::findOrderById(int orderId) const {
    auto it = orders.find(orderId);
    if (it != orders.end()) {
        return const_cast<Order*>(&(it->second));
    }
    return nullptr;
}
vector<Order> Inventory::getOrdersByCustomer(int customerId) const {
    vector<Order> result;
    auto it = customerOrders.find(customerId);
    if (it != customerOrders.end()) {
        for (const int &orderId : it->second) {
            auto orderIt = orders.find(orderId);
            if (orderIt != orders.end()) {
                result.push_back(orderIt->second);
            }
        }
    }
    return result;
}
vector<Order> Inventory::getOrdersByStatus(string status) const {
    vector<Order> result;
    for (const auto &[id, order] : orders) {
        if (order.getStatus() == status) {
            result.push_back(order);
        }
    }
    return result;
}
string Inventory::getOrderSummary(int orderId) const {
    auto it = orders.find(orderId);
    if (it == orders.end()) {
        return "Order not found";
    }
    const Order& order = it->second;
    stringstream ss;
    ss << "Order #" << order.getId() << "\n";
    ss << "Customer: " << order.getCustomerName() << "\n";
    ss << "Status: " << order.getStatus() << "\n";
    ss << "Total: $" << order.getTotalAmount() << "\n";
    ss << "Items:\n";
    
    for (const auto& item : order.getItems()) {
        ss << "  - " << item.getItemName() << " (x" << item.getQuantity() 
           << ") @ $" << item.getUnitPrice() << " each\n";
    }
    return ss.str();
}
vector<Order> Inventory::getAllOrders() const {
    vector<Order> result;
    for (const auto &[id, order] : orders) {
        result.push_back(order);
    }
    return result;
}


// -------------- Reports -------------- //


double Inventory::calculateTotalInventoryValue() const {
    double totalValue = 0.0;
    for (const auto& pair : products) {
        const Product& product = pair.second;
        totalValue += product.getPrice() * product.getQuantity();
    }
    return totalValue;
}

double Inventory::calculateTotalRevenue() const {
    double totalRevenue = 0.0;
    for (const auto& pair : orders) {
        const Order& order = pair.second;
        if (order.isCompleted()) {
            totalRevenue += order.getTotalAmount();
        }
    }
    return totalRevenue;
}

void Inventory::generateInventoryReport() const {
    cout << "=== INVENTORY REPORT ===" << endl;
    cout << "Total Products: " << products.size() << endl;
    cout << "Total Inventory Value: $" << calculateTotalInventoryValue() << endl;
    cout << "Low Stock Items: " << getLowStockProducts().size() << endl;
    cout << "----------------------------------------" << endl;
    
    for (const auto& pair : products) {
        const Product& product = pair.second;
        cout << "ID: " << product.getId() 
             << " | Name: " << product.getName()
             << " | Stock: " << product.getQuantity()
             << " | Price: $" << product.getPrice()
             << " | Status: " << (product.isLowStock() ? "LOW STOCK" : "OK") 
             << endl;
    }
}

void Inventory::generateSalesReport() const {
    cout << "=== SALES REPORT ===" << endl;
    cout << "Total Orders: " << orders.size() << endl;
    cout << "Total Revenue: $" << calculateTotalRevenue() << endl;
    
    vector<Order> completedOrders;
    // Count orders by status
    int pending = 0, completed = 0, cancelled = 0;
    for (const auto& [id, order] : orders) {
        if (order.isPending()) { 
            pending++;
        } else if (order.isCompleted()) {
            completed++;
            completedOrders.push_back(order);
        } else if (order.isCancelled()) {
            cancelled++;
        } 
    }
    
    cout << "Pending Orders: " << pending << endl;
    cout << "Completed Orders: " << completed << endl;
    cout << "Cancelled Orders: " << cancelled << endl;
    cout << "----------------------------------------" << endl;
    
    // Show recent completed orders
    cout << "Recent Completed Orders:" << endl;
    for (const auto& order : completedOrders) {
        cout << "Order #" << order.getId() 
             << " | Customer: " << order.getCustomerName()
             << " | Total: $" << order.getTotalAmount()
             << " | Date: " << order.getOrderDate() 
             << endl;
    }
}

void Inventory::generateLowStockReport() const {
    cout << "=== LOW STOCK REPORT ===" << endl;
    vector<Product*> lowStock = getLowStockProducts();
    
    if (lowStock.empty()) {
        cout << "No products are low on stock." << endl;
        return;
    }
    
    cout << "Low Stock Products (" << lowStock.size() << "):" << endl;
    for (const Product* product : lowStock) {
        cout << "ID: " << product->getId() 
             << " | Name: " << product->getName()
             << " | Current Stock: " << product->getQuantity()
             << " | Minimum Required: " << product->getMinStockLevel()
             << " | Deficit: " << (product->getMinStockLevel() - product->getQuantity())
             << endl;
    }
}

void Inventory::generateCustomerReport(int customerId) const {
    Customer* customer = findCustomerById(customerId);
    if (!customer) {
        cout << "Customer not found." << endl;
        return;
    }
    
    cout << "=== CUSTOMER REPORT ===" << endl;
    cout << "Customer ID: " << customer->getId() << endl;
    cout << "Name: " << customer->getName() << endl;
    cout << "Total Orders: " << customer->getOrderHistory().size() << endl;
    cout << "----------------------------------------" << endl;
    
    vector<Order> customerOrders = getOrdersByCustomer(customerId);
    double totalSpent = 0.0;
    
    cout << "Order History:" << endl;
    for (const Order& order : customerOrders) {
        cout << "Order #" << order.getId() 
             << " | Date: " << order.getOrderDate()
             << " | Status: " << order.getStatus()
             << " | Total: $" << order.getTotalAmount()
             << endl;
        totalSpent += order.getTotalAmount();
    }
    
    cout << "Total Amount Spent: $" << totalSpent << endl;
}

void Inventory::generateSupplierReport() const {
    cout << "=== SUPPLIER REPORT ===" << endl;
    cout << "Total Suppliers: " << suppliers.size() << endl;
    cout << "----------------------------------------" << endl;
    
    for (const auto& pair : suppliers) {
        const Supplier& supplier = pair.second;
        cout << "ID: " << supplier.getId() 
             << " | Name: " << supplier.getName()
             << " | Contact: " << supplier.getEmail() << " / " << supplier.getPhone()
             << endl;
        
        // Count products from this supplier
        int productCount = 0;
        for (const auto& productPair : products) {
            if (productPair.second.getSupplierId() == supplier.getId()) {
                productCount++;
            }
        }
        
        cout << "   Products Supplied: " << productCount << endl;
    }
}