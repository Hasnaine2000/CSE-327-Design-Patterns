#include <iostream>
using namespace std;

// Interface (Abstract Class)
class Image {
public:
    virtual void display() = 0;
};

// Real Image Class (Loads & Displays Image)
class RealImage : public Image {
private:
    string fileName;

public:
    RealImage(string filename) : fileName(filename) {
        cout << "Loading image: " << fileName << endl;
    }

    void display() override {
        cout << "Displaying image: " << fileName << endl;
    }
};

// Proxy Image Class (Loads RealImage Only When Needed)
class ProxyImage : public Image {
private:
    string fileName;
    RealImage* realImage;

public:
    ProxyImage(string filename) : fileName(filename), realImage(nullptr) {}

    ~ProxyImage() {
        delete realImage;
    }

    void display() override {
        if (!realImage) { // Load only if needed
            realImage = new RealImage(fileName);
        }
        realImage->display();
    }
};

// Main Function
int main() {
    ProxyImage proxy("dogs.png");
    proxy.display();  // First time: Loads & Displays
    proxy.display();  // Second time: Just Displays

    return 0;
}
