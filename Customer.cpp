#include "Customer.h"

// Constructor
Customer::Customer(int id, string name, string phone, string email, string address) : 
    customerId(id), name(name), phone(phone),email(email), address(address) {}

// Getters
int Customer::getId() const {
    return customerId;
}
string Customer::getName() const {
    return name;
}
string Customer::getPhone() const {
    return phone;
}
string Customer::getEmail() const {
    return email;
}
string Customer::getAddress() const {
    return address;
}
vector<int> Customer::getOrderHistory() const {
    return orderHistory;
}

// Setters
void Customer::setPhone(string newPhone) {
    this->phone = newPhone;
}
void Customer::setEmail(string newEmail) {
    this->email = newEmail;
}
void Customer::setAddress(string newAddress) {
    this->address = newAddress;
}

void Customer::addOrderToHistory(int orderId) {
    this->orderHistory.push_back(orderId);
}


int Customer::getTotalOrders() const {
    return orderHistory.size();
}

void Customer::display() const {
    cout << "Customer ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Phone: " << getPhone() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Address: " << address << endl;
    cout << "Total Orders: " << getTotalOrders() << endl;
}
