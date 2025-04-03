#include <iostream>
#include <string>

using namespace std;

// Component (Base Class)
class SandwichOrder 
{
public:
    virtual int GetCost() const = 0;
    virtual string GetIngredient() const = 0;
    virtual ~SandwichOrder() = default; // Virtual destructor for proper cleanup
};

// Concrete Component - Basic Sandwich
class BasicSandwich : public SandwichOrder 
{
public:
    int GetCost() const override 
    {
        return 5;
    }
    string GetIngredient() const override 
    {
        return "Basic Bread and Meat";
    }
};

// Concrete Component - Deluxe Sandwich
class DeluxeSandwich : public SandwichOrder 
{
public:
    int GetCost() const override 
    {
        return 8;
    }
    string GetIngredient() const override 
    {
        return "Organic Bread, Organic Meat, Cheese, Veggie";
    }
};

// Decorator - Base Class for Additional Features
class Decorator : public SandwichOrder 
{
protected:
    SandwichOrder* order_;
public:
    Decorator(SandwichOrder* order) : order_(order) {}
    
    int GetCost() const override 
    {
        return order_->GetCost();
    }
    
    string GetIngredient() const override 
    {
        return order_->GetIngredient();
    }
    
    virtual ~Decorator() 
    {
        delete order_; // Properly delete the wrapped object
    }
};

// Concrete Decorator - Adding Condiments
class CondimentDecorator : public Decorator 
{
private:
    string condiment_;
    int cost_ = 1;

public:
    CondimentDecorator(string condiment, SandwichOrder* order) 
        : condiment_(condiment), Decorator(order) {}

    int GetCost() const override 
    {
        return cost_ + Decorator::GetCost();
    }

    string GetIngredient() const override 
    {
        return condiment_ + ", " + order_->GetIngredient();
    }
};

// Concrete Decorator - Adding Side Items
class SideDecorator : public Decorator 
{
private:
    string side_;
    int cost_ = 2;

public:
    SideDecorator(string side, SandwichOrder* order) 
        : side_(side), Decorator(order) {}

    int GetCost() const override 
    {
        return cost_ + Decorator::GetCost();
    }

    string GetIngredient() const override 
    {
        return side_ + ", " + order_->GetIngredient();
    }
};

// Function to Display Order Details
void ServeOrder(SandwichOrder* order) 
{
    cout << "Total Cost: $" << order->GetCost() << endl;
    cout << "Ingredients: " << order->GetIngredient() << endl;
}

int main() 
{
    // Create a Deluxe Sandwich
    SandwichOrder* sandwich1 = new DeluxeSandwich();

    // Add Condiments and Sides using Decorators
    SandwichOrder* decorated1 = new CondimentDecorator("Mayo", sandwich1);
    SandwichOrder* decorated2 = new SideDecorator("Pickle", decorated1);
    SandwichOrder* decorated3 = new CondimentDecorator("Mustard", decorated2);
    SandwichOrder* final_order = new SideDecorator("Onion", decorated3);

    // Serve the final order
    ServeOrder(final_order);

    // Clean up memory
    delete final_order;

    return 0;
}
