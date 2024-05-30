#ifndef HOSPITAL_ALERT_SYSTEM_FACADE_H
#define HOSPITAL_ALERT_SYSTEM_FACADE_H

#include "Patient.h"
#include "PatientAlertListener.h"

class HospitalAlertSystemFacade : public PatientAlertListener
{
public:
    HospitalAlertSystemFacade();
    virtual ~HospitalAlertSystemFacade();

    void sendAlertForPatient(Patient* p);
    void update(Patient* patient) override;
};

#endif
