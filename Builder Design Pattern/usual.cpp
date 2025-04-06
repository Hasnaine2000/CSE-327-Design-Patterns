#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Bread {
    Toast,
    HotdogBun,
    BurgerBun
};

enum class Protein {
    BeefPatty,
    Dog,
    Bacon
};

enum class Side {
    Lettuce,
    Tomato,
    Onions,
    Cheese
};

enum class Sauce {
    Mayo,
    Ketchup,
    YumYum,
    Mustard
};

enum class Wrapper {
    Paper,
    Box,
    Plastic
};

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

int main() {
    Sandwich burger(
        Bread::BurgerBun, Protein::BeefPatty,
        vector<Side>{Side::Lettuce, Side::Cheese, Side::Tomato},
        vector<Sauce>{Sauce::YumYum},
        Wrapper::Paper
    );

    Sandwich hotdog(
        Bread::HotdogBun, Protein::Dog,
        vector<Side>{Side::Onions},
        vector<Sauce>{Sauce::Ketchup, Sauce::Mustard},
        Wrapper::Box
    );

    Sandwich BLT(
        Bread::Toast, Protein::Bacon,
        vector<Side>{Side::Tomato, Side::Lettuce},
        vector<Sauce>{Sauce::Mayo},
        Wrapper::Plastic
    );

    return 0;
}
