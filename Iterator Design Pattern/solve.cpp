#include <iostream>
#include <string>
#include <list>
#include <array>
using namespace std;

// MenuItem class
class MenuItem {
public:
    MenuItem() = default;
    MenuItem(string_view n, string_view d, bool v, double p)
        : name(n), description(d), vegetarian(v), price(p) {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    bool isVegetarian() const { return vegetarian; }
    double getPrice() const { return price; }

private:
    string name;
    string description;
    bool vegetarian = false;
    double price = 0.0;
};

// PancakeHouseMenu class
class PancakeHouseMenu {
    public:
        PancakeHouseMenu() {
            addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
            addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
            addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
            addItem("Waffles", "Waffles with your choice of blueberries or strawberries", true, 3.59);
        }
    
        void addItem(string_view name, string_view description, bool vegetarian, double price) {
            menuItems.emplace_back(name, description, vegetarian, price);
        }
    
        Iterator<MenuItem>* createIterator() {
            return new PancakeHouseMenuIterator(menuItems);
        }
    
        string getMenuDescription() const {
            return "ObjectVille Pancake House Menu";
        }
    
    private:
        list<MenuItem> menuItems;
    };
    
    // DinerMenu class
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
    
        void addItem(string_view name, string_view description, bool vegetarian, double price) {
            if (numberOfItems < MAX_ITEMS) {
                menuItems[numberOfItems++] = MenuItem(name, description, vegetarian, price);
            } else {
                cerr << "Sorry, menu is full! Can't add item to menu\n";
            }
        }
    
        Iterator<MenuItem>* createIterator() {
            return new DinerMenuIterator(menuItems);
        }
    
        string getMenuDescription() const {
            return "ObjectVille Diner Menu";
        }
    
    private:
        array<MenuItem, MAX_ITEMS> menuItems;
        size_t numberOfItems = 0;
    };




// Iterator Interface
template<typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual T* next() = 0;
    virtual bool hasNext() const = 0;
};

// PancakeHouseMenu Iterator (uses std::list)
class PancakeHouseMenuIterator : public Iterator<MenuItem> {
public:
    PancakeHouseMenuIterator(list<MenuItem>& i) : items(i), iter(items.begin()) {}
    
    MenuItem* next() override {
        return &*iter++;
    }

    bool hasNext() const override {
        return iter != items.end();
    }

private:
    list<MenuItem>& items;
    list<MenuItem>::iterator iter;
};

// DinnerMenu Iterator (uses std::array)
class DinerMenuIterator : public Iterator<MenuItem> {
public:
    static const size_t MAX_ITEMS = 6;
    DinerMenuIterator(array<MenuItem, MAX_ITEMS>& i) : items(i) {}

    MenuItem* next() override {
        return &items[position++];
    }

    bool hasNext() const override {
        return position < items.size() && !items[position].getName().empty();
    }

private:
    array<MenuItem, MAX_ITEMS>& items;
    size_t position = 0;
};




// Waitress class
class Waitress {
public:
    Waitress(PancakeHouseMenu* p, DinerMenu* d) : pancake(p), diner(d) {}

    void printMenu() const {
        Iterator<MenuItem>* pancakeIterator = pancake->createIterator();
        Iterator<MenuItem>* dinerIterator = diner->createIterator();

        cout << "Menu\n---\nBREAKFAST\n";
        printItems(pancakeIterator);
        cout << "\nLUNCH\n";
        printItems(dinerIterator);

        delete pancakeIterator;
        delete dinerIterator;
    }

private:
    void printItems(Iterator<MenuItem>* iterator) const {
        while (iterator->hasNext()) {
            MenuItem* item = iterator->next();
            cout << item->getName() << ", " << item->getPrice() << "$ -- "
                 << item->getDescription() << "\n";
        }
    }

    PancakeHouseMenu* pancake;
    DinerMenu* diner;
};

// Main Function
int main() {
    PancakeHouseMenu pancakeMenu;
    DinerMenu dinerMenu;
    Waitress waitress(&pancakeMenu, &dinerMenu);
    waitress.printMenu();
    return 0;
}
