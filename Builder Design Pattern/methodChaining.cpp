#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Enums for ingredients
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

// Abstract Chain Builder
class ChainSandwichBuilder {
public:
    virtual ChainSandwichBuilder& AddBread() = 0;
    virtual ChainSandwichBuilder& AddProtein() = 0;
    virtual ChainSandwichBuilder& AddWrapper() = 0;
    virtual ChainSandwichBuilder& LoadSides() = 0;
    virtual ChainSandwichBuilder& DrizzleSauces() = 0;

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

// Burger Builder
class BurgerBuilder : public ChainSandwichBuilder {
public:
    ChainSandwichBuilder& AddBread() override {
        cout << "Heating up the Seasame Sprinkled Bun" << endl;
        product.b = Bread::BurgerBun;
        return *this;
    }

    ChainSandwichBuilder& AddProtein() override {
        cout << "Grilling the Wagyu" << endl;
        product.p = Protein::BeefPatty;
        return *this;
    }

    ChainSandwichBuilder& AddWrapper() override {
        cout << "Wrapping with 100% recycled paper" << endl;
        product.w = Wrapper::Paper;
        return *this;
    }

    ChainSandwichBuilder& LoadSides() override {
        cout << "Loading up the Burger" << endl;
        AddSide(Side::Lettuce);
        AddSide(Side::Tomato);
        return *this;
    }

    ChainSandwichBuilder& DrizzleSauces() override {
        cout << "Drizzling the sauces" << endl;
        AddSauce(Sauce::YumYum);
        return *this;
    }
};

// Hotdog Builder
class HotdogBuilder : public ChainSandwichBuilder {
public:
    ChainSandwichBuilder& AddBread() override {
        cout << "Steaming up the buns" << endl;
        product.b = Bread::HotdogBun;
        return *this;
    }

    ChainSandwichBuilder& AddProtein() override {
        cout << "Boiling the hotdog in brine" << endl;
        product.p = Protein::Dog;
        return *this;
    }

    ChainSandwichBuilder& AddWrapper() override {
        cout << "Placing the hotdog into box" << endl;
        product.w = Wrapper::Box;
        return *this;
    }

    ChainSandwichBuilder& LoadSides() override {
        cout << "Loading up the Hotdog" << endl;
        AddSide(Side::Onions);
        return *this;
    }

    ChainSandwichBuilder& DrizzleSauces() override {
        cout << "Drizzling the sauces" << endl;
        AddSauce(Sauce::Mustard);
        return *this;
    }
};

// BLT Builder
class BLTBuilder : public ChainSandwichBuilder {
public:
    ChainSandwichBuilder& AddBread() override {
        cout << "Toasting bread in toaster" << endl;
        product.b = Bread::Toast;
        return *this;
    }

    ChainSandwichBuilder& AddProtein() override {
        cout << "Sizzling bacon in cast iron pan" << endl;
        product.p = Protein::Bacon;
        return *this;
    }

    ChainSandwichBuilder& AddWrapper() override {
        cout << "Wrapping up in a decompostable plastic wrap" << endl;
        product.w = Wrapper::Plastic;
        return *this;
    }

    ChainSandwichBuilder& LoadSides() override {
        cout << "Loading up the BLT" << endl;
        AddSide(Side::Lettuce);
        AddSide(Side::Tomato);
        return *this;
    }

    ChainSandwichBuilder& DrizzleSauces() override {
        cout << "Drizzling with the sauces" << endl;
        AddSauce(Sauce::Mayo);
        return *this;
    }
};

// Director function
Sandwich CreateChainSandwich(ChainSandwichBuilder& builder) {
    builder.AddBread()
           .AddProtein()
           .LoadSides()
           .DrizzleSauces()
           .AddWrapper();
    return builder.ReturnProduct();
}

// Main
int main() {
    cout << "Creating Burger: ------" << endl;
    BurgerBuilder burgerBuilder;
    CreateChainSandwich(burgerBuilder);

    cout << "\nCreating Hotdog: -----" << endl;
    HotdogBuilder hotdogBuilder;
    CreateChainSandwich(hotdogBuilder);

    cout << "\nCreating BLT: --------" << endl;
    BLTBuilder bltBuilder;
    CreateChainSandwich(bltBuilder);

    return 0;
}
