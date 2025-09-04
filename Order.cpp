#include "order.h"

OrderItem::OrderItem(int itemId, string itemName, int quantity, double unitPrice) : 
    itemId(itemId), itemName(itemName), quantity(quantity), unitPrice(unitPrice){}

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

// ---------------------------------------------------------

Order::Order(int id, int customerId, string customerName, string date) :
    orderId(id), customerId(customerId), customerName(customerName), orderDate(date),
    status("PENDING"), totalAmount(0.0) {}


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
    return items;
}

// ===== OPTIMIZE HERE ===== //

// Adds an item to the order
void Order::addItem(OrderItem item) {
    items.push_back(item);
    calculateTotal(); // Recalculate the total
}

// Removes an item from the order by product ID
bool Order::removeItem(int productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getItemId() == productId) {
            items.erase(it);
            calculateTotal(); // Recalculate the total
            return true;
        }
    }
    return false;
}

// Calculates the total amount of the order
void Order::calculateTotal() {
    totalAmount = 0.0;
    for (const auto& item : items) {
        totalAmount += item.getTotalPrice();
    }
}
// Updates the status of the order
void Order::setStatus(string newStatus) {
    status = newStatus;
}

void Order::display() const {
    cout << "Order ID: " << getId() << endl;
    cout << "Customer ID: " << getCustomerId() << endl;
    cout << "Customer Name: " << getCustomerName() << endl;
    cout << "Order Date: " << getOrderDate() << endl;
    cout << "Status: " << getStatus() << endl;
    cout << "Items:" << endl;
    for (const auto& item : items) {
        item.display();
        cout << endl;
    }
    cout << "Total Amount: " << getTotalAmount() << endl;
}
