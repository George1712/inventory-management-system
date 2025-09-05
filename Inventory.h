#ifndef INVENTORY_H
#define INVENTORY_H

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<set>
#include<chrono>
#include<ctime>
#include<sstream>
#include<iomanip>
using namespace std;

#include "Product.h"
#include "Supplier.h"
#include "Order.h"
#include "Customer.h"

class Inventory {
private:
    // Product
    unordered_map<int, Product> products;
    unordered_map<string, set<int>> productNameIds;
    set<int> lowStockProductIds;
    int nextProductId;

    // Supplier
    unordered_map<int, Supplier> suppliers;
    unordered_map<string, set<int>> supplierNameIds;
    
    // Customer
    unordered_map<int, Customer> customers;
    unordered_map<string, set<int>> customerNameIds;

    // Order
    unordered_map<int, Order> orders;
    unordered_map<int, set<int>> customerOrders; // [custID, orders]
    int nextOrderId;

public:
    Inventory();

    // Product management
    void addProduct(Product product);
    bool removeProduct(int productId);
    Product* findProductById(int productId);
    vector<Product*> findProductsByName(string name);
    bool restockProduct(int productId, int quantity);
    bool sellProduct(int productId, int quantity);
    void updateLowStockStatus(int productId, int newQuantity, int minStockLevel);
    bool updateProductMinStockLevel(int productId, int newMinStocklevel);
    vector<Product*> getLowStockProducts() const;
    
    // Supplier management
    void addSupplier(Supplier supplier);
    bool removeSupplier(int supplierId);
    Supplier* findSupplierById(int supplierId);
    vector<Supplier*> findSupplierByName(string name);
    vector<Supplier> getAllSuppliers() const;
    
    // Customer management
    void addCustomer(Customer customer);
    bool removeCustomer(int customerId);
    Customer* findCustomerById(int customerId) const;
    vector<Customer*> findCustomerByName(string name);
    vector<Customer> getAllCustomers() const;
    
    // Order management
    string getCurrentDateTime() const;
    Order* createOrder(int customerId);
    bool addItemToOrder(int orderId, int productId, int quantity);
    bool updateOrderItemQuantity(int orderId, int productId, int newQuantity);
    bool processOrder(int orderId);
    bool cancelOrder(int orderId);
    Order* findOrderById(int orderId);
    vector<Order> getOrdersByCustomer(int customerId) const;
    vector<Order> getOrdersByStatus(string status) const;
    string getOrderSummary(int orderId) const;
    vector<Order> getAllOrders() const;

    // Reporting
    double calculateTotalInventoryValue() const;
    double calculateTotalRevenue() const;
    void generateInventoryReport() const;
    void generateSalesReport() const;
    void generateLowStockReport() const;
    void generateCustomerReport(int customerId) const;
    void generateSupplierReport() const;
};

#endif