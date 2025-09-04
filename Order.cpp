#include "order.h"

OrderItem::OrderItem(int itemId, string itemName, int quantity, double unitPrice) : 
    itemId(itemId), itemName(itemName), quantity(quantity), unitPrice(unitPrice){}

// Getters
int OrderItem::getItemId() const {
    return itemId;
}
string OrderItem::getItemName() const {
    return itemName;
}
int OrderItem::getQuantity() const {
    return quantity;
}
double OrderItem::getUnitPrice() const {
    return unitPrice;
}

void OrderItem::updateQuantity(int newQuantity) {
    quantity = newQuantity;
}
double OrderItem::getTotalPrice() const {
    return quantity * unitPrice;
}
void OrderItem::display() const {
    cout << "Item ID: " << getItemId() << endl;
    cout << "Item Name: " << getItemName() << endl;
    cout << "Quantity: " << getQuantity() << endl;
    cout << "Unit Price: " << getUnitPrice() << endl;
    cout << "Total Price: " << getTotalPrice() << endl;
}


Order::Order(int id, int customerId, string customerName, string date) :
    orderId(id), customerId(customerId), customerName(customerName), orderDate(date),
    status("PENDING"), totalAmount(0.0) {}


// Getters
int Order::getId() const {
    return orderId;
}
int Order::getCustomerId() const {
    return customerId;
}
string Order::getCustomerName() const {
    return customerName;
}
string Order::getOrderDate() const {
    return orderDate;
}
string Order::getStatus() const {
    return status;
}
double Order::getTotalAmount() const {
    return totalAmount;
}
vector<OrderItem> Order::getItems() const {
    vector<OrderItem> result;
    for (const auto &[id, item] : items) {
        result.push_back(item);
    }
    return result;
}

void Order::setStatus(string newStatus) {
    status = newStatus;
}
void Order::updateTotal(double amountChange) {
    totalAmount += amountChange;
    totalAmount = max(totalAmount, 0.0);
}

void Order::addItem(OrderItem newItem) {
    int id = newItem.getItemId();
    auto it = items.find(id);
    if (it != items.end()) { // already exists
        OrderItem& existingItem = it->second;
        updateTotal(-existingItem.getTotalPrice());
        int newQuantity = existingItem.getQuantity() + newItem.getQuantity();
        existingItem.updateQuantity(newQuantity);
        updateTotal(existingItem.getTotalPrice());
    } else {
        items[id] = newItem;
        updateTotal(newItem.getTotalPrice());
    }
}

bool Order::removeItem(int itemId) {
    auto it = items.find(itemId);
    if (it != items.end()) {
        updateTotal(-it->second.getTotalPrice());
        items.erase(it);
        return true;
    }
    return false;
}

bool Order::updateItemQuantity(int itemId, int newQuantity) {
    auto it = items.find(itemId);
    if (it != items.end() && newQuantity >= 0) {
        updateTotal(-it->second.getTotalPrice()); // Remove old total
        it->second.updateQuantity(newQuantity);   // Update quantity
        updateTotal(it->second.getTotalPrice());  // Add new total
        return true;
    }
    return false;
}

int Order::getItemQuantity(int itemId) const {
    auto it = items.find(itemId);
    return (it != items.end()) ? it->second.getQuantity() : 0;
}

bool Order::isPending() const {
    return status == "PENDING";
}
bool Order::isProcessing() const {
    return status == "PROCESSING";
}
bool Order::isCompleted() const {
    return status == "COMPLETED";
}
bool Order::isCancelled() const {
    return status == "CANCELLED";
}

void Order::display() const {
    cout << "Order ID: " << getId() << endl;
    cout << "Customer ID: " << getCustomerId() << endl;
    cout << "Customer Name: " << getCustomerName() << endl;
    cout << "Order Date: " << getOrderDate() << endl;
    cout << "Status: " << getStatus() << endl;
    cout << "Items:" << endl;
    for (const auto &[id, item] : items) {
        item.display();
        cout << endl;
    }
    cout << "Total Amount: " << getTotalAmount() << endl;
}
