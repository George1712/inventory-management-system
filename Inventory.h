#ifndef INVENTORY_H
#define INVENTORY_H

#include<iostream>
#include<string>
#include<vector>

#include "Product.h"
#include "Supplier.h"
#include "Order.h"
#include "Customer.h"

using namespace std;

class Inventory {
private:
    vector<Product> products;
    vector<Supplier> suppliers;
    vector<Order> orders;
    vector<Customer> customers;
    int nextProductId;
    int nextOrderId;

public:
    Inventory();

    // Product management
    void addProduct(Product product);
    bool removeProduct(int productId);
    Product* findProductById(int productId);
    vector<Product*> findProductsByName(string name);
    vector<Product*> getLowStockProducts();
    
    // Supplier management
    void addSupplier(Supplier supplier);
    Supplier* findSupplierById(int supplierId);
    
    // Customer management
    void addCustomer(Customer customer);
    Customer* findCustomerById(int customerId);
    
    // Order management
    Order* createOrder(int customerId);
    bool processOrder(int orderId);
    vector<Order> getOrdersByCustomer(int customerId);
    
    // Reporting
    double calculateTotalInventoryValue() const;
    void generateInventoryReport() const;
};

#endif