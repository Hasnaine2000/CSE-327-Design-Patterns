#include <iostream>
using namespace std;

class Alarm
{
public:
    void alarmOn()
    {
        cout << "Alarm is on and house is secured" << endl;
    }
    void alarmOff()
    {
        cout << "Alarm is off and you can go into the house" << endl;
    }
};

class AirConditioner
{
public:
    void acOn()
    {
        cout << "AC is on" << endl;
    }
    void acOff()
    {
        cout << "AC is off" << endl;
    }
};

class TV
{
public:
    void tvOn()
    {
        cout << "TV is on" << endl;
    }
    void tvOff()
    {
        cout << "TV is off" << endl;
    }
};

class HouseFacade
{
private:
    Alarm alarm;
    AirConditioner ac;
    TV tv;

public:
    HouseFacade() {}
    void goToWork()
    {
        ac.acOff();
        tv.tvOff();
        alarm.alarmOn();
    }
    void comeHome()
    {
        alarm.alarmOff();
        ac.acOn();
        tv.tvOn();
    }
};

int main()
{
    HouseFacade hf;
    
    cout << "Going to work:" << endl;
    hf.goToWork();
    
    cout << "\nJust got home:" << endl;
    hf.comeHome();
    
    return 0;
}
