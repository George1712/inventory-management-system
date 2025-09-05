#include "Inventory.h"

// Constructor
Inventory::Inventory() : nextProductId(1), nextOrderId(1) {}


// -------------- Product Management -------------- //

void Inventory::addProduct(Product product) {
    int id = product.getId();
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
Product* Inventory::findProductById(int productId) {
    auto it = products.find(productId);
    if (it != products.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Product*> Inventory::findProductsByName(string name) {
    vector<Product*> result;
    auto it = productNameIds.find(name);
    if (it != productNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&products[id]);
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
vector<Product*> Inventory::getLowStockProducts() {
    vector<Product*> result;
    for (auto id : lowStockProductIds) {
        auto it = products.find(id);
        if (it != products.end()) {
            result.push_back(&(it->second));
        }
    }
    return result;
}


// -------------- Supplier Management -------------- //

void Inventory::addSupplier(Supplier supplier) {
    int id = supplier.getId();
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
Supplier* Inventory::findSupplierById(int supplierId) {
    auto it = suppliers.find(supplierId);
    if (it != suppliers.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Supplier*> Inventory::findSupplierByName(string name) {
    vector<Supplier*> result;
    auto it = supplierNameIds.find(name);
    if (it != supplierNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&suppliers[id]);
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
    int id = customer.getId();
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

Customer* Inventory::findCustomerById(int customerId) {
    auto it = customers.find(customerId);
    if (it != customers.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Customer*> Inventory::findCustomerByName(string name) {
    vector<Customer*> result;
    auto it = customerNameIds.find(name);
    if (it != customerNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&customers[id]);
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
Order* Inventory::findOrderById(int orderId) {
    auto it = orders.find(orderId);
    if (it != orders.end()) {
        return &(it->second);
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


