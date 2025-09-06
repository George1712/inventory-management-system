#include "Supplier.h"

// Constructor
Supplier::Supplier(int id, string name, string phone,
     string email, string address) : 
    supplierId(id), name(name), phone(phone), email(email), address(address) {}

// Getters
int Supplier::getId() const {
    return supplierId;
}
string Supplier::getName() const {
    return name;
}
string Supplier::getPhone() const {
    return phone;
}
string Supplier::getEmail() const {
    return email;
}
string Supplier::getAddress() const {
    return address;
}

// Setters
void Supplier::setId(int newId) {
    this->supplierId = newId;
}
void Supplier::setPhone(string newPhone) {
    this->phone = newPhone;
}
void Supplier::setEmail(string newEmail) {
    this->email = newEmail;
}
void Supplier::setAddress(string newAddress) {
    this->address = newAddress;
}

void Supplier::display() const {
    cout << "Supplier ID: " << getId() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Phone: " << getPhone() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Address: " << getAddress() << endl;
}
