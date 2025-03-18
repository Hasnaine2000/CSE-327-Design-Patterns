#include <iostream>
#include <mutex>

using namespace std;

class Logger
{
public:
    static Logger *getLogger()
    {
        if (loggerInstance == nullptr) // First check (not locked)
        {
            lock_guard<mutex> lock(mtx); // Lock before creating instance
            if (loggerInstance == nullptr) // Second check (thread safety)
            {
                loggerInstance = new Logger();
            }
        }
        return loggerInstance;
    }

    void Log(const string &msg)
    {
        counter++;
        cout << "Log " << counter << ": " << msg << endl;
    }

private:
    static Logger *loggerInstance;
    static int counter;
    static mutex mtx; // Mutex for thread safety

    // Private constructor to prevent external instantiation
    Logger()
    {
        cout << "Logger Initialized!" << endl;
    }

    // Deleting copy constructor and assignment operator
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

// Initialize static members
Logger *Logger::loggerInstance = nullptr;
int Logger::counter = 0;
mutex Logger::mtx;

// Usage Example
int main()
{
    Logger *logger1 = Logger::getLogger();
    logger1->Log("This is a log message.");

    Logger *logger2 = Logger::getLogger();
    logger2->Log("This is another log message.");

    return 0;
}
