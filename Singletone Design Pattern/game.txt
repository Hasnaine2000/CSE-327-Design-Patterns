#include <iostream>
using namespace std;

class GameEngine
{
public:
    static GameEngine *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new GameEngine();
        }
        return instance;
    }

    void run()
    {
        cout << "Game Engine Running!" << endl;
    }

private:
    static GameEngine *instance;
    GameEngine() { cout << "Game Engine Initialized!" << endl; }
};

// Initialize static member
GameEngine *GameEngine::instance = nullptr;

// Usage Example
int main()
{
    GameEngine *engine1 = GameEngine::getInstance();
    engine1->run();

    GameEngine *engine2 = GameEngine::getInstance();
    engine2->run(); // Uses the same instance

    return 0;
}
