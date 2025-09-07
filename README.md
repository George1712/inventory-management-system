# Inventory Management System

This Inventory Management System is a console-based C++ application designed to manage products,
supplier relationships, customer orders, and inventory tracking efficiently.
It simulates key functionalities of a real-world inventory management system,
allowing businesses to track stock levels, process orders,
manage supplier and customer information, and generate comprehensive business reports.

## Key features
- **Product management:** Add, update, remove, and list products with unique IDs, names, descriptions, price, quantity, supplier association, and minimum stock level.
  
- **Supplier & customer management:** CRUD operations for suppliers and customers.
    
- **Order processing:** Place orders with multiple items, track order status, and adjust inventory quantities on order placement.
    
- **Reports:** Inventory value, low-stock report, sales summaries and simple console reports.
    
- **Interactive Console UI:** Menu-driven interface with input validation helpers for an immediate interactive experience.

## Technical highlights

- **Data structures & performance:**
    
    - `std::unordered_map` — primary storage for products, suppliers, customers and orders keyed by their IDs for expected O(1) lookup.
        
    - Name-based indices are implemented using `std::unordered_map` /`std::set` to enable quick name-based searches.
        
    - Efficient in-memory operations suitable for small-to-medium datasets.
        
- **OOP design:** Clear separation of responsibilities — `Product`, `Supplier`, `Customer`, `Order` classes encapsulate domain data; `Inventory` manages collections and business logic.
    
- **Design choices:** Core logic is implemented as plain C++ classes with minimal dependencies so it can be reused or wrapped by other interfaces later (e.g., GUI or web API).


## Quick Start

```bash
# Clone and navigate to project
git clone https://github.com/your-username/InventoryManagementSystem.git
cd InventoryManagementSystem

# Compile
g++ -Iinclude src/*.cpp -o inventory_system

# Run
./inventory_system
```


## Future improvements

- Add persistence (JSON files or SQLite) and load/save at startup/shutdown.
    
- Add a GUI or simple REST API to make the system accessible beyond the CLI.
    
- Implement role-based users (admins, clerks) and permissions for operations like deletion.
