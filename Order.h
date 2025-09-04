#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class OrderItem {
private:
    int itemId;
    string itemName;
    int quantity;
    double unitPrice;

public:
    // Constructor
    OrderItem(int itemId, string itemName,
         int quantity, double unitPrice);

    // Getters
    int getItemId() const;
    string getItemName() const;
    int getQuantity() const;
    double getUnitPrice() const;
    
    // Methods
    double getTotalPrice() const;
    void display() const;
};


class Order {
private:
    int orderId;
    int customerId;
    string customerName;
    string orderDate;
    string status; // "PENDING", "PROCESSING", "COMPLETED", "CANCELLED"
    vector<OrderItem> items;
    double totalAmount;

public:
    // Constructor
    Order(int id, int customerId, string customerName, string date);
    
    // Getters
    int getId() const;
    int getCustomerId() const;
    string getCustomerName() const;
    string getOrderDate() const;
    string getStatus() const;
    double getTotalAmount() const;
    vector<OrderItem> getItems() const;
    
    // Order operations
    void addItem(OrderItem item);
    bool removeItem(int productId);
    void calculateTotal();
    void setStatus(string newStatus);
    
    void display() const;
};

#endif