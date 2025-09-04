#ifndef INVENTORY_H
#define INVENTORY_H

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<set>

#include "Product.h"
#include "Supplier.h"
#include "Order.h"
#include "Customer.h"

using namespace std;

class Inventory {
private:
    // Product
    unordered_map<int, Product> products;
    unordered_map<string, set<int>> productNameIds;
    set<int> lowStockProductIds;

    // Supplier
    unordered_map<int, Supplier> suppliers;
    unordered_map<string, set<int>> supplierNameIds;
    
    // Customer
    unordered_map<int, Customer> customers;
    unordered_map<string, set<int>> customerNameIds;




    vector<Order> orders;


    int nextProductId;
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
    vector<Product*> getLowStockProducts();
    
    // Supplier management
    void addSupplier(Supplier supplier);
    bool removeSupplier(int supplierId);
    Supplier* findSupplierById(int supplierId);
    vector<Supplier*> findSupplierByName(string name);
    vector<Supplier> getAllSuppliers() const;
    
    // Customer management
    void addCustomer(Customer customer);
    bool removeCustomer(int customerId);
    Customer* findCustomerById(int customerId);
    vector<Customer*> findCustomerByName(string name);
    vector<Customer> getAllCustomers() const;
    



    
    // Order management
    Order* createOrder(int customerId);
    bool processOrder(int orderId);
    vector<Order> getOrdersByCustomer(int customerId);
    





    // Reporting
    double calculateTotalInventoryValue() const;
    void generateInventoryReport() const;
};

#endif