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

// Turkey Interface
class Turkey {
public:
    virtual ~Turkey() = default;
    virtual void gooble() = 0;
    virtual void fly() = 0;
};

// MallardDuck - A concrete Duck
class MallardDuck : public Duck {
public:
    void quack() override {
        cout << "Quack" << endl;
    }
    void fly() override {
        cout << "I am flying" << endl;
    }
};

// WildTurkey - A concrete Turkey
class WildTurkey : public Turkey {
public:
    void gooble() override {
        cout << "Googble, gooble" << endl;
    }
    void fly() override {
        cout << "I am flying a short distance" << endl;
    }
};

// TurkeyAdapter - Makes a Turkey act like a Duck
class TurkeyAdapter : public Duck {
public:
    TurkeyAdapter(Turkey* tur) : turkey(tur) {}

    void quack() override {
        turkey->gooble();
    }

    void fly() override {
        for (int i = 0; i < 5; i++) {
            turkey->fly();
        }
    }

private:
    Turkey* turkey;
};

// DuckAdapter - Makes a Duck act like a Turkey
class DuckAdapter : public Turkey {
public:
    DuckAdapter(Duck* du) : duck(du), randGen(std::random_device{}()), dist(0, 4) {}

    void gooble() override {
        duck->quack();
    }

    void fly() override {
        if (dist(randGen) == 0) {
            duck->fly();
        }
    }

private:
    Duck* duck;
    std::mt19937 randGen;
    std::uniform_int_distribution<int> dist;
};

// Testing functions
void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

void testTurkey(Turkey* turkey) {
    turkey->gooble();
    turkey->fly();
}

// Main
int main() {
    Duck* duck = new MallardDuck();
    Turkey* turkey = new WildTurkey();

    cout << "The Duck says..." << endl;
    testDuck(duck);

    cout << "The Turkey says..." << endl;
    testTurkey(turkey);

    cout << "\nTurkey Adapter Performing\n";
    Duck* turkeyAdapter = new TurkeyAdapter(turkey);
    testDuck(turkeyAdapter);

    cout << "\nDuck Adapter Performing\n";
    Turkey* duckAdapter = new DuckAdapter(duck);
    testTurkey(duckAdapter);

    // Clean up
    delete duck;
    delete turkey;
    delete turkeyAdapter;
    delete duckAdapter;

    return 0;
}
