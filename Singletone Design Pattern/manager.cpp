#include <iostream>
using namespace std;

class ConfigManager
{
public:
    static ConfigManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new ConfigManager();
        }
        return instance;
    }

    void setConfig(string key, string value)
    {
        config = key + " = " + value;
    }

    void showConfig()
    {
        cout << "Config: " << config << endl;
    }

private:
    static ConfigManager *instance;
    string config;

    ConfigManager() { cout << "ConfigManager Initialized!" << endl; }
};

// Initialize static member
ConfigManager *ConfigManager::instance = nullptr;

// Usage Example
int main()
{
    ConfigManager *config1 = ConfigManager::getInstance();
    config1->setConfig("Theme", "Dark Mode");

    ConfigManager *config2 = ConfigManager::getInstance();
    config2->showConfig(); // Uses the same instance

    return 0;
}
