#include "PatientManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "PatientCSVLoaderAdapter.h"

#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"

#include "DiseaseAlertLevelCalculator.h"
#include "PatientAlertListener.h"


#include "Utility.h"

using namespace std;


PatientManagementSystem::PatientManagementSystem() :
    _patientDatabaseLoader(std::make_unique<PatientCSVLoaderAdapter>("patients.txt"))
    /*_patientDatabaseLoader(std::make_unique<PatientDatabaseLoader>())*/ ,
    _hospitalAlertSystem(std::make_shared<HospitalAlertSystemFacade>()),
    _gpNotificationSystem(std::make_shared<GPNotificationSystemFacade>()),
    _diseaseAlertLevelCalculator(std::make_unique<DiseaseAlertLevelCalculator>())
{
    _patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
    _patientDatabaseLoader->closeConnection();

    // clear patient memory
    for (Patient* p : _patients) {
        delete p;
    }
}

void PatientManagementSystem::init()
{
    _patientDatabaseLoader->loadPatients(_patients);
    for (Patient* p : _patients) {
        _patientLookup[p->uid()] = p;
    }
    
    for (Patient* p : _patients) 
    {
        //subscribe the hospital alert system
        p->addListener(std::weak_ptr<PatientAlertListener>(_hospitalAlertSystem));
        //subscribe the gp notification system
        p->addListener(std::weak_ptr<PatientAlertListener>(_gpNotificationSystem));
    }
}

void PatientManagementSystem::run()
{
    printWelcomeMessage();

    bool running = true;
    while (running) {
        printMainMenu();
        int option = 0;
        cin >> option;

        // handle basic errors
        if (cin.bad()) {
            cin.clear();
            cin.ignore();
            continue;
        }

        // switch based on the selected option
        switch (option) {
        case 1:
            addVitalsRecord();
            break;
        case 2:
            printPatients();
            break;
        case 3:
            running = false;
            break;
        }
    }
}

void PatientManagementSystem::addVitalsRecord()
{
    cout << "Patients" << endl;
    printPatients();
    cout << endl;
    cout << "Enter the patient ID to declare vitals for > ";
    
    string pid { "" };
    cin >> pid;
    if (_patientLookup.count(pid)) {
        int heartRate;
        int oxygenSaturation;
        int bodyTemperature;
        int brainActivity;

        cout << "Enter hear rate: ";
        cin >> heartRate;
        cout << "Enter oxygen saturation: ";
        cin >> oxygenSaturation;
        cout << "Enter body temperature: ";
        cin >> bodyTemperature;
        cout << "Enter brain activity: ";
        cin >> brainActivity;

        Vitals* v = new Vitals(heartRate, oxygenSaturation, bodyTemperature, brainActivity);
        _patientLookup[pid]->addVitals(v);
        //calculate the most recent record's alert level.
        //_diseaseAlertLevelCalculator.get()->calculateAlertLevel(_patientLookup[pid]); <-- i guess fr2 makes this obsolete?
        _diseaseAlertLevelCalculator->calculateHighestAlertLevel(_patientLookup[pid]);
    }
    else {
        cout << "Patient not found" << endl;
    }
}


void PatientManagementSystem::printWelcomeMessage() const
{
    cout << "WELCOME TO DOCTRACK 2000" << endl;
    cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
    cout << endl << "Select an option:" << endl;
    cout << "1. Record new vitals" << endl;
    cout << "2. List patients" << endl;
    cout << "3. Quit" << endl;
    cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
    for (Patient* p : _patients) {
        std::cout << *p << std::endl;
    }
}
