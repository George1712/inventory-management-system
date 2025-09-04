#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;
    string email;
    string address;
    vector<int> orderHistory;

public:
    // Constructor
    Customer(int id, string name, string phone,
         string email, string address);
    
    // Getters
    int getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;
    string getAddress() const;
    vector<int> getOrderHistory() const;

    // Setters
    void setPhone(string newPhone);
    void setEmail(string newEmail);
    void setAddress(string newAddress);

    // Methods
    void addOrderToHistory(int orderId);
    int getTotalOrders() const;
    void display() const;
};

#endif