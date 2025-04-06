#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Enum definitions
enum class Bread { Toast, HotdogBun, BurgerBun };
enum class Protein { BeefPatty, Dog, Bacon };
enum class Side { Lettuce, Tomato, Onions, Cheese };
enum class Sauce { Mayo, Ketchup, YumYum, Mustard };
enum class Wrapper { Paper, Box, Plastic };

// Sandwich class
class Sandwich {
public:
    Sandwich() = default;

    Sandwich(Bread b, Protein p, vector<Side> sides, vector<Sauce> sauces, Wrapper w)
        : b{b}, p{p}, sides{sides}, sauces{sauces}, w{w} {
        cout << "A Sandwich is constructed" << endl;
    }

    Bread b;
    Protein p;
    vector<Side> sides;
    vector<Sauce> sauces;
    Wrapper w;
};

// Abstract builder class
class SandwichBuilder {
public:
    virtual void AddBread() = 0;
    virtual void AddProtein() = 0;
    virtual void AddWrapper() = 0;
    virtual void LoadSides() = 0;
    virtual void DrizzleSauces() = 0;

    void AddSide(Side s) {
        product.sides.push_back(s);
    }

    void AddSauce(Sauce s) {
        product.sauces.push_back(s);
    }

    Sandwich ReturnProduct() {
        return product;
    }

protected:
    Sandwich product;
};

// Concrete builder: BurgerBuilder
class BurgerBuilder : public SandwichBuilder {
public:
    void AddBread() override {
        cout << "Heating up the Seasame Sprinked Bun" << endl;
        product.b = Bread::BurgerBun;
    }

    void AddProtein() override {
        cout << "Grilling the Wagyu" << endl;
        product.p = Protein::BeefPatty;
    }

    void AddWrapper() override {
        cout << "Wrapping with 100% recycled paper" << endl;
        product.w = Wrapper::Paper;
    }

    void LoadSides() override {
        cout << "Loading up the Burger" << endl;
        AddSide(Side::Lettuce);
        AddSide(Side::Tomato);
    }

    void DrizzleSauces() override {
        cout << "Drizzling the sauces" << endl;
        AddSauce(Sauce::YumYum);
    }
};

// Concrete builder: HotdogBuilder
class HotdogBuilder : public SandwichBuilder {
public:
    void AddBread() override {
        cout << "Steaming up the buns" << endl;
        product.b = Bread::HotdogBun;
    }

    void AddProtein() override {
        cout << "Boiling the hotdog in brine" << endl;
        product.p = Protein::Dog;
    }

    void AddWrapper() override {
        cout << "Placing the hotdog into box" << endl;
        product.w = Wrapper::Box;
    }

    void LoadSides() override {
        cout << "Loading up the Hotdog" << endl;
        AddSide(Side::Onions);
    }

    void DrizzleSauces() override {
        cout << "Drizzling the sauces" << endl;
        AddSauce(Sauce::Mustard);
    }
};

// Concrete builder: BLTBuilder
class BLTBuilder : public SandwichBuilder {
public:
    void AddBread() override {
        cout << "Toasting bread in toaster" << endl;
        product.b = Bread::Toast;
    }

    void AddProtein() override {
        cout << "Sizzling bacon in cast iron pan" << endl;
        product.p = Protein::Bacon;
    }

    void AddWrapper() override {
        cout << "Wrapping up in a decompostable plastic wrap" << endl;
        product.w = Wrapper::Plastic;
    }

    void LoadSides() override {
        cout << "Loading up the BLT" << endl;
        AddSide(Side::Lettuce);
        AddSide(Side::Tomato);
    }

    void DrizzleSauces() override {
        cout << "Drizzling with the sauces" << endl;
        AddSauce(Sauce::Mayo);
    }
};

// Director function
Sandwich CreateSandwich(SandwichBuilder* builder) {
    builder->AddBread();
    builder->AddProtein();
    builder->LoadSides();
    builder->DrizzleSauces();
    builder->AddWrapper();
    return builder->ReturnProduct();
}

// Main function
int main() {
    cout << "Creating Burger: ------" << endl;
    CreateSandwich(new BurgerBuilder());

    cout << "Creating Hotdog: ----- " << endl;
    CreateSandwich(new HotdogBuilder());

    cout << "Creating BLT: ---- " << endl;
    CreateSandwich(new BLTBuilder());

    return 0;
}
