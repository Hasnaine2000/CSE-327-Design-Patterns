#include <iostream>
using namespace std;

class ElectricianUnion {
public:
    void submitNetworkRequest() {
        _state = 0;
        cout << "[Electrician] Request submitted. Current state: " << _state << endl;
    }
    
    bool checkOnStatus() {
        _state++;
        cout << "[Electrician] Current state: " << _state << endl;
        if (_state == Complete) {
            cout << "[Electrician] Task completed." << endl;
            return true;
        }
        return false;
    }
    
private:
    enum States {
        Received, RejectTheForm, SizeTheJob, SmokeAndJokeBreak,
        WaitForAuthorization, DoTheWrongJob, BlameTheEngineer, WaitToPunchOut,
        DoHalfAJob, ComplainToEngineer, GetClarification, CompleteTheJob,
        TurnInThePaperwork, Complete
    };
    int _state;
};

class MisDepartment {
public:
    void submitNetworkRequest() {
        _state = 0;
        cout << "[MIS] Request submitted. Current state: " << _state << endl;
    }
    
    bool checkOnStatus() {
        _state++;
        cout << "[MIS] Current state: " << _state << endl;
        if (_state == Complete) {
            cout << "[MIS] Task completed." << endl;
            return true;
        }
        return false;
    }
    
private:
    enum States {
        Received, DenyAllKnowledge, ReferClientToFacilities,
        FacilitiesHasNotSentPaperwork, ElectricianIsNotDone,
        ElectricianDidItWrong, DispatchTechnician, SignedOff, DoesNotWork,
        FixElectriciansWiring, Complete
    };
    int _state;
};

class FacilitiesDepartment {
public:
    void submitNetworkRequest() {
        _state = 0;
        cout << "[Facilities] Request submitted. Current state: " << _state << endl;
    }
    
    bool checkOnStatus() {
        _state++;
        cout << "[Facilities] Current state: " << _state << endl;
        if (_state == Complete) {
            cout << "[Facilities] Task completed." << endl;
            return true;
        }
        return false;
    }
    
private:
    enum States {
        Received, AssignToEngineer, EngineerResearches, RequestIsNotPossible,
        EngineerLeavesCompany, AssignToNewEngineer, NewEngineerResearches,
        ReassignEngineer, EngineerReturns, EngineerResearchesAgain,
        EngineerFillsOutPaperWork, Complete
    };
    int _state;
};

class FacilitiesFacade {
public:
    FacilitiesFacade() : _count(0), _state(Received) {}
    
    void submitNetworkRequest() {
        _state = Received;
        cout << "[Facade] Request received in FacilitiesFacade." << endl;
    }
    
    bool checkOnStatus() {
        _count++;
        cout << "[Facade] Checking status. Call #" << _count << endl;
        
        if (_state == Received) {
            _state = SubmitToEngineer;
            _engineer.submitNetworkRequest();
            cout << "[Facade] Submitted to Facilities. " << _count << " calls so far." << endl;
        } else if (_state == SubmitToEngineer) {
            if (_engineer.checkOnStatus()) {
                _state = SubmitToElectrician;
                _electrician.submitNetworkRequest();
                cout << "[Facade] Submitted to Electrician. " << _count << " calls so far." << endl;
            }
        } else if (_state == SubmitToElectrician) {
            if (_electrician.checkOnStatus()) {
                _state = SubmitToTechnician;
                _technician.submitNetworkRequest();
                cout << "[Facade] Submitted to MIS. " << _count << " calls so far." << endl;
            }
        } else if (_state == SubmitToTechnician) {
            if (_technician.checkOnStatus()) {
                return true;
            }
        }
        return false;
    }
    
    int getNumberOfCalls() {
        return _count;
    }
    
private:
    enum States {
        Received, SubmitToEngineer, SubmitToElectrician, SubmitToTechnician
    };
    
    int _state;
    int _count;
    FacilitiesDepartment _engineer;
    ElectricianUnion _electrician;
    MisDepartment _technician;
};

int main() {
    FacilitiesFacade facilities;
    facilities.submitNetworkRequest();
    while (!facilities.checkOnStatus());
    cout << "Job completed after only " << facilities.getNumberOfCalls() << " phone calls." << endl;
    return 0;
}
