#include <iostream>
using namespace std;

class Database
{
public:
    static Database *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Database();
        }
        return instance;
    }

    void connect()
    {
        cout << "Connected to Database." << endl;
    }

private:
    static Database *instance;
    Database() { cout << "Database Instance Created!" << endl; }
};

// Initialize static member
Database *Database::instance = nullptr;

// Usage Example
int main()
{
    Database *db1 = Database::getInstance();
    db1->connect();

    Database *db2 = Database::getInstance();
    db2->connect(); // Uses the same instance

    return 0;
}
