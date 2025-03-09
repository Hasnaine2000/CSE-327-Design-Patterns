#include <iostream>
using namespace std;

class FileManager
{
public:
    static FileManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new FileManager();
        }
        return instance;
    }

    void readFile(string filename)
    {
        cout << "Reading file: " << filename << endl;
    }

private:
    static FileManager *instance;
    FileManager() { cout << "FileManager Initialized!" << endl; }
};

// Initialize static member
FileManager *FileManager::instance = nullptr;

// Usage Example
int main()
{
    FileManager *fm1 = FileManager::getInstance();
    fm1->readFile("document.txt");

    FileManager *fm2 = FileManager::getInstance();
    fm2->readFile("data.txt");

    return 0;
}
