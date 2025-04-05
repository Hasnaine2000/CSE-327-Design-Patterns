#include <iostream>
#include <string>
#include <list>
#include <array>
#include <memory>

// ==================== MENU ITEM CLASS ====================
class MenuItem {
public:
    MenuItem() = default;
    MenuItem(std::string name, std::string description, bool vegetarian, double price)
        : name(std::move(name)), description(std::move(description)), vegetarian(vegetarian), price(price) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    bool isVegetarian() const { return vegetarian; }
    double getPrice() const { return price; }

private:
    std::string name;
    std::string description;
    bool vegetarian;
    double price = 0.0;
};

inline std::ostream& operator<<(std::ostream& os, const MenuItem& item) {
    os << item.getName() << ", $" << item.getPrice() << "\n" << item.getDescription();
    return os;
}

// ==================== ITERATOR INTERFACE ====================
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() = default;
};

// ==================== PANCAKE HOUSE MENU ====================
class PancakeHouseMenu {
public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs and sausage", false, 2.99);
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles with blueberries or strawberries", true, 3.59);
    }

    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price) {
        menuItems.emplace_back(name, description, vegetarian, price);
    }

    const std::list<MenuItem>& getMenuItems() const {
        return menuItems;
    }

    std::string getMenuDescription() const {
        return "ObjectVille Pancake House Menu";
    }

private:
    std::list<MenuItem> menuItems;
};

// ==================== DINER MENU ====================
class DinerMenu {
private:
    static const size_t MAX_ITEMS = 6;
    size_t numberOfItems = 0;
    std::array<MenuItem, MAX_ITEMS> menuItems;

public:
    DinerMenu() {
        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog with sauerkraut, relish, onions, and cheese", false, 3.05);
        addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
        addItem("Pasta", "Spaghetti with Marinara Sauce and sourdough bread", true, 3.89);
    }

    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price) {
        if (numberOfItems >= MAX_ITEMS) {
            std::cerr << "Sorry, menu is full! Can't add item to menu\n";
            return;
        }
        menuItems[numberOfItems++] = MenuItem(name, description, vegetarian, price);
    }

    const std::array<MenuItem, MAX_ITEMS>& getMenuItems() const {
        return menuItems;
    }

    std::string getMenuDescription() const {
        return "ObjectVille Diner Menu";
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    // Create PancakeHouseMenu
    PancakeHouseMenu pancakeHouse;
    const auto& breakfastItems = pancakeHouse.getMenuItems();

    // Create DinerMenu
    DinerMenu dinerMenu;
    const auto& lunchItems = dinerMenu.getMenuItems();

    // Print Breakfast Menu
    std::cout << "Breakfast Menu Items:\n";
    for (const auto& item : breakfastItems) {
        std::cout << item.getName() << " - $" << item.getPrice() << " - " << item.getDescription() << "\n";
    }

    // Print Lunch Menu
    std::cout << "\nLunch Menu Items:\n";
    for (size_t i = 0; i < lunchItems.size(); i++) {
        std::cout << lunchItems[i].getName() << " - $" << lunchItems[i].getPrice() << " - " << lunchItems[i].getDescription() << "\n";
    }

    return 0;
}
