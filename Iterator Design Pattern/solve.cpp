#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <memory>
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
// ==================== MENU ITEM ====================
class MenuItem {
public:
    MenuItem(std::string name, std::string desc, bool veg, double price) 
        : name(name), description(desc), vegetarian(veg), price(price) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    bool isVegetarian() const { return vegetarian; }
    double getPrice() const { return price; }

private:
    std::string name, description;
    bool vegetarian;
    double price;
};

// ==================== ITERATOR INTERFACE ====================
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T* next() = 0;
};

// ==================== PANCAKE HOUSE MENU ====================
class PancakeHouseMenu {
public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.59);
    }

    void addItem(std::string name, std::string desc, bool veg, double price) {
        menuItems.emplace_back(name, desc, veg, price);
    }

    std::list<MenuItem>& getMenuItems() { return menuItems; }

    class PancakeHouseMenuIterator : public Iterator<MenuItem> {
    public:
        PancakeHouseMenuIterator(std::list<MenuItem>& items) : items(items), iter(items.begin()) {}
        bool hasNext() const override { return iter != items.end(); }
        MenuItem* next() override { return &*(iter++); }
    private:
        std::list<MenuItem>& items;
        std::list<MenuItem>::iterator iter;
    };

    std::unique_ptr<Iterator<MenuItem>> createIterator() {
        return std::make_unique<PancakeHouseMenuIterator>(menuItems);
    }

private:
    std::list<MenuItem> menuItems;
};

// ==================== DINER MENU ====================
class DinerMenu {
public:
    static const size_t MAX_ITEMS = 6;

    DinerMenu() {
        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.05);
        addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
        addItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89);
    }

    void addItem(std::string name, std::string desc, bool veg, double price) {
        if (numberOfItems >= MAX_ITEMS) {
            std::cerr << "Sorry, menu is full! Can't add item to menu\n";
            return;
        }
        menuItems[numberOfItems++] = MenuItem(name, desc, veg, price);
    }

    const std::array<MenuItem, MAX_ITEMS>& getMenuItems() const { return menuItems; }

    class DinerMenuIterator : public Iterator<MenuItem> {
    public:
        DinerMenuIterator(const std::array<MenuItem, MAX_ITEMS>& items) : items(items), position(0) {}
        bool hasNext() const override { return position < items.size(); }
        MenuItem* next() override { return const_cast<MenuItem*>(&items[position++]); }
    private:
        const std::array<MenuItem, MAX_ITEMS>& items;
        size_t position;
    };

    std::unique_ptr<Iterator<MenuItem>> createIterator() {
        return std::make_unique<DinerMenuIterator>(menuItems);
    }

private:
    std::array<MenuItem, MAX_ITEMS> menuItems;
    size_t numberOfItems = 0;
};

// ==================== WAITRESS CLASS ====================
class Waitress {
public:
    Waitress(PancakeHouseMenu* p, DinerMenu* d) : pancakeMenu(p), dinerMenu(d) {}

    void printMenu() const {
        std::cout << "MENU\n---\nBREAKFAST\n";
        printMenu(pancakeMenu->createIterator());

        std::cout << "\nLUNCH\n";
        printMenu(dinerMenu->createIterator());
    }

private:
    void printMenu(std::unique_ptr<Iterator<MenuItem>> iterator) const {
        while (iterator->hasNext()) {
            MenuItem* item = iterator->next();
            std::cout << item->getName() << ", $" << item->getPrice() << " -- " << item->getDescription() << "\n";
        }
    }

    PancakeHouseMenu* pancakeMenu;
    DinerMenu* dinerMenu;
};

// ==================== MAIN FUNCTION ====================
int main() {
    PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
    DinerMenu* dinerMenu = new DinerMenu();

    Waitress* waitress = new Waitress(pancakeHouseMenu, dinerMenu);
    waitress->printMenu();

    delete pancakeHouseMenu;
    delete dinerMenu;
    delete waitress;

    return 0;
}
