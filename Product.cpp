#include "Product.h"

// Constructor
Product::Product(int id, string name, string desc, double price, 
    int quantity, int supplierId, int minStock) : 
    productID(id), name(name), description(desc), price(price), 
    quantityInStock(quantity), supplierId(supplierId), minStockLevel(minStock) {}


// Getters
int Product::getId() const {
    return productID;
}
string Product::getName() const {
    return name;
}
string Product::getDescription() const {
    return description;
}
double Product::getPrice() const {
    return price;
}
int Product::getQuantity() const {
    return quantityInStock;
}
int Product::getSupplierId() const {
    return supplierId;
}
int Product::getMinStockLevel() const {
    return minStockLevel;
}


// Setters
void Product::setPrice(double newPrice) {
    this->price = newPrice;
}
void Product::setDescription(string desc) {
    this->description = desc;
}
void Product::setMinStockLevel(int newLevel) {
    this->minStockLevel = newLevel;
}    


void Product::updateQuantity(int amount) {
    quantityInStock += amount;
    quantityInStock = max(quantityInStock, 0);
}
bool Product::isLowStock() const {
    return quantityInStock < minStockLevel;
}

void Product::display() const {
    cout << "Product ID: " << productID << endl;
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Price: $" << price << endl;
    cout << "Quantity in Stock: " << quantityInStock << endl;
    cout << "Supplier ID: " << supplierId << endl;
    cout << "Minimum Stock Level: " << minStockLevel << endl;
}
