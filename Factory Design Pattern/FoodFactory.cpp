#include <iostream>
using namespace std;

// Abstract base class
class Battleship {
public:
    Battleship() {
        cout << "Battleship Created" << endl;
    }

    virtual void Fire() = 0;
    virtual void Steer() = 0;

    virtual ~Battleship() {
        cout << "Battleship destroyed" << endl;
    }
};

// Concrete class: Destroyer
class Destroyer : public Battleship {
public:
    Destroyer() {
        cout << "Destroyer Created" << endl;
    }

    void Fire() override {
        cout << "Destroyer Fire" << endl;
    }

    void Steer() override {
        cout << "Destroyer Steer" << endl;
    }
};

// Concrete class: Carrier
class Carrier : public Battleship {
public:
    Carrier() {
        cout << "Carrier Created" << endl;
    }

    void Fire() override {
        cout << "Carrier Fire" << endl;
    }

    void Steer() override {
        cout << "Carrier Steer" << endl;
    }
};

// Creator class (Factory Method)
class ShipCreator {
public:
    virtual Battleship *FactoryMethod() = 0;
    virtual ~ShipCreator() {}

    Battleship *CreateShip() {
        return this->FactoryMethod();
    }
};

// Concrete Creator for Carrier
class CarrierCreator : public ShipCreator {
public:
    Battleship *FactoryMethod() override {
        return new Carrier();
    }
};

// Concrete Creator for Destroyer
class DestroyerCreator : public ShipCreator {
public:
    Battleship *FactoryMethod() override {
        return new Destroyer();
    }
};

int main() {
    // Creating a Carrier using the Factory Method
    ShipCreator *creator = new CarrierCreator();
    Battleship *battleship1 = creator->CreateShip();
    battleship1->Fire();
    battleship1->Steer();

    cout << "\nSecond Battleship:\n";

    // Creating a Destroyer using the Factory Method
    delete creator;  // Delete previous creator to avoid memory leak
    creator = new DestroyerCreator();
    Battleship *battleship2 = creator->CreateShip();
    battleship2->Fire();
    battleship2->Steer();

    // Cleaning up memory
    delete battleship1;
    delete battleship2;
    delete creator;

    return 0;
}
