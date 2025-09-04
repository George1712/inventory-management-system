#include "Inventory.h"

// Constructor
Inventory::Inventory() : nextProductId(1), nextOrderId(1) {}


// -------------- Product Management -------------- //

void Inventory::addProduct(Product product) {
    int id = product.getId();
    products[id] = product;
    string name = product.getName();
    productNameIds[name].insert(id);
    
    updateLowStockStatus(id, product.getQuantity(), product.getMinStockLevel());
}
bool Inventory::removeProduct(int productId) {
    auto productIt = products.find(productId); // = [id, Product]
    if (productIt != products.end()) {
        // removing name form id
        string name = (productIt->second).getName();
        auto nameIt = productNameIds.find(name); // = [string, set<id>]
        if (nameIt != productNameIds.end()) {
            nameIt->second.erase(productId);
            if (nameIt->second.empty()) {
                productNameIds.erase(nameIt);
            }
        }
        // remove product id 
        lowStockProductIds.erase(productId);
        products.erase(productIt);
        return true;
    }
    return false;
}
Product* Inventory::findProductById(int productId) {
    auto it = products.find(productId);
    if (it != products.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Product*> Inventory::findProductsByName(string name) {
    vector<Product*> result;
    auto it = productNameIds.find(name);
    if (it != productNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&products[id]);
        }
    }
    return result;
}
void Inventory::updateLowStockStatus(int productId, int newQuantity, int minStockLevel) {
    if (newQuantity < minStockLevel) {
        lowStockProductIds.insert(productId);
    } else {
        lowStockProductIds.erase(productId);
    }
}
bool Inventory::restockProduct(int productId, int quantity) {
    if (quantity <= 0) return false;
    Product* product = findProductById(productId);
    if (product) {
        product->updateQuantity(quantity);
        updateLowStockStatus(productId, product->getQuantity(), product->getMinStockLevel());
        return true;
    }
    return false;
}
bool Inventory::sellProduct(int productId, int quantity) {
    if (quantity <= 0) return false;
    Product* product = findProductById(productId);
    if (product && product->getQuantity() >= quantity) {
        product->updateQuantity(-quantity);
        updateLowStockStatus(productId, product->getQuantity(), product->getMinStockLevel());
        return true;
    }
    return false;
}
bool Inventory::updateProductMinStockLevel(int productId, int newMinStockLevel) {
    if (newMinStockLevel < 0) {
        return false;
    }
    auto it = products.find(productId);
    if (it == products.end()) {
        return false;
    }
    it->second.setMinStockLevel(newMinStockLevel);
    updateLowStockStatus(productId, it->second.getQuantity(), newMinStockLevel);
    return true;
}
vector<Product*> Inventory::getLowStockProducts() {
    vector<Product*> result;
    for (auto id : lowStockProductIds) {
        auto it = products.find(id);
        if (it != products.end()) {
            result.push_back(&(it->second));
        }
    }
    return result;
}


// -------------- Supplier Management -------------- //

void Inventory::addSupplier(Supplier supplier) {
    int id = supplier.getId();
    suppliers[id] = supplier;
    string name = supplier.getName();
    supplierNameIds[name].insert(id);
}
bool Inventory::removeSupplier(int supplierId) {
    auto supplierIt = suppliers.find(supplierId);
    if (supplierIt != suppliers.end()) {
        // remove name from id
        string name = (supplierIt->second).getName();
        auto nameIt = supplierNameIds.find(name);
        if (nameIt != supplierNameIds.end()) {
            nameIt->second.erase(supplierId);
            if (nameIt->second.empty()) {
                supplierNameIds.erase(nameIt);
            }
        }
        // remove supplier id
        suppliers.erase(supplierIt);
        return true;
    }
    return false;
}
Supplier* Inventory::findSupplierById(int supplierId) {
    auto it = suppliers.find(supplierId);
    if (it != suppliers.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Supplier*> Inventory::findSupplierByName(string name) {
    vector<Supplier*> result;
    auto it = supplierNameIds.find(name);
    if (it != supplierNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&suppliers[id]);
        }
    }
    return result;
}
vector<Supplier> Inventory::getAllSuppliers() const {
    vector<Supplier> result;
    for (auto it : suppliers) {
        result.push_back(it.second);
    }
    return result;
}


// -------------- Customer Management -------------- //

void Inventory::addCustomer(Customer customer) {
    int id = customer.getId();
    customers[id] = customer;
    string name = customer.getName();
    customerNameIds[name].insert(id);
}
bool Inventory::removeCustomer(int customerId) {
    auto customerIt = customers.find(customerId);
    if (customerIt != customers.end()) {
        string name = (customerIt->second).getName();
        auto nameIt = customerNameIds.find(name);
        if (nameIt != customerNameIds.end()) {
            nameIt->second.erase(customerId);
            if (nameIt->second.empty()) {
                customerNameIds.erase(nameIt);
            }
        }
        // remove supplier id
        customers.erase(customerIt);
        return true;
    }
    return false;
}

Customer* Inventory::findCustomerById(int customerId) {
    auto it = customers.find(customerId);
    if (it != customers.end()) {
        return &(it->second);
    }
    return nullptr;
}
vector<Customer*> Inventory::findCustomerByName(string name) {
    vector<Customer*> result;
    auto it = customerNameIds.find(name);
    if (it != customerNameIds.end()) {
        for (int id : it->second) {
            result.push_back(&customers[id]);
        }
    }
    return result;
}
vector<Customer> Inventory::getAllCustomers() const {
    vector<Customer> result;
    for (auto it : customers) {
        result.push_back(it.second);
    }
    return result;
}


// -------------- Order Management -------------- //













// -------------- Reports -------------- //


