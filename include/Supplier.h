#ifndef SUPPLIER_H
#define SUPPLIER_H

#include<iostream>
#include<string>
using namespace std;

class Supplier {
private:
    int supplierId;
    string name;
    string phone;
    string email;
    string address;

public:
    // Constructors
    Supplier() : supplierId(0) {}
    Supplier(int id, string name, string phone,
         string email, string address);
    
    // Getters
    int getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;
    string getAddress() const;

    // Setters
    void setId(int newId);
    void setPhone(string newPhone);
    void setEmail(string newEmail);
    void setAddress(string newAddress);

    // Methods
    void display() const;
};

#endif