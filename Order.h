#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class OrderItem {
private:
    int itemId;
    string itemName;
    int quantity;
    double unitPrice;

public:
    // Constructors
    OrderItem() : itemId(0), quantity(0), unitPrice(0.0) {}
    OrderItem(int itemId, string itemName, int quantity, double unitPrice);

    // Getters
    int getItemId() const;
    string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    
    // Methods
    void updateQuantity(int newQuantity);
    double getTotalPrice() const;
    void display() const;
};


class Order {
private:
    int orderId;
    int customerId;
    string customerName;
    string orderDate;
    string status; // "PENDING", "COMPLETED", "CANCELLED"
    unordered_map<int, OrderItem> items;
    double totalAmount;

public:
    // Constructors
    Order() : orderId(0), customerId(0), totalAmount(0.0) {}
    Order(int id, int customerId, string customerName, string date);
    
    // Getters
    int getId() const;
    int getCustomerId() const;
    string getCustomerName() const;
    string getOrderDate() const;
    string getStatus() const;
    double getTotalAmount() const;
    vector<OrderItem> getItems() const;
    int getItemQuantity(int itemId) const;
    
    // Setters
    void setStatus(string newStatus);
    void updateTotal(double amountChange);

    // Actions
    void addItem(OrderItem item);
    bool removeItem(int itemId);
    bool updateItemQuantity(int itemId, int newQuantity);
    
    // Status
    bool isPending() const;
    bool isProcessing() const;
    bool isCompleted() const;
    bool isCancelled() const;

    void display() const;
};

#endif