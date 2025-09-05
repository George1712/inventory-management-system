#ifndef PROJECT_H
#define PROJECT_H

#include<iostream>
#include<string>
using namespace std;

class Product {
private:
    int productID;
    string name;
    string description;
    double price;
    int quantityInStock;
    int supplierId;
    int minStockLevel;

public:
    // Constructors
    Product() : productID(0), price(0.0), quantityInStock(0), supplierId(0), minStockLevel(0) {}
    Product(int id, string name, string desc, double price, 
        int quantity, int supplierId, int minStock = 5);
    
    // Getters
    int getId() const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    int getQuantity() const;
    int getSupplierId() const;
    int getMinStockLevel() const;

    // Setters
    void setPrice(double newPrice);
    void setDescription(string newDesc);
    void setMinStockLevel(int newLevel);

    // Methods
    void updateQuantity(int amount);
    bool isLowStock() const;
    void display() const;
};

#endif