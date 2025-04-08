#include <iostream>
#include <random>
using namespace std;

// Duck Interface
class Duck {
public:
    virtual ~Duck() = default;
    virtual void quack() = 0;
    virtual void fly() = 0;
};

// MallardDuck - Concrete Duck
class MallardDuck : public Duck {
public:
    void quack() override {
        cout << "Quack" << endl;
    }
    void fly() override {
        cout << "I am flying" << endl;
    }
};

// Turkey Interface
class Turkey {
public:
    virtual ~Turkey() = default;
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

// WildTurkey - Concrete Turkey
class WildTurkey : public Turkey {
public:
    void gobble() override {
        cout << "Gobble, Gobble" << endl;
    }
    void fly() override {
        cout << "I am flying a short distance" << endl;
    }
};

// Adapter: Makes a MallardDuck behave like a Turkey
class MallardDuckAdapter : public Turkey, private MallardDuck {
public:
    MallardDuckAdapter() : randGen(std::random_device{}()), dist(0, 4) {}

    void gobble() override {
        MallardDuck::quack();
    }

    void fly() override {
        if (dist(randGen) == 0) {
            MallardDuck::fly();
        }
    }

private:
    std::mt19937 randGen;
    std::uniform_int_distribution<int> dist;
};

// Adapter: Makes a WildTurkey behave like a Duck
class WildTurkeyAdapter : public Duck, private WildTurkey {
public:
    WildTurkeyAdapter() = default;

    void quack() override {
        WildTurkey::gobble();
    }

    void fly() override {
        for (int i = 0; i < 5; i++) {
            WildTurkey::fly();
        }
    }
};

// Test functions
void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

void testTurkey(Turkey* turkey) {
    turkey->gobble();
    turkey->fly();
}

// Main function
int main() {
    Turkey* turkey = new WildTurkey();
    cout << "The Turkey says:" << endl;
    turkey->gobble();
    turkey->fly();

    cout << "\nTurkeyAdapter is coming:\n";
    Duck* wildTurkeyAdapter = new WildTurkeyAdapter();
    testDuck(wildTurkeyAdapter);

    cout << "\nDuckAdapter is coming:\n";
    Turkey* duck = new MallardDuckAdapter();
    testTurkey(duck);

    // Clean up
    delete turkey;
    delete wildTurkeyAdapter;
    delete duck;

    return 0;
}
