#ifndef GP_NOTIFICATION_SYSTEM_FACADE_H
#define GP_NOTIFICATION_SYSTEM_FACADE_H

#include "Patient.h"
#include "PatientAlertListener.h"

class GPNotificationSystemFacade : public PatientAlertListener
{
public:
    GPNotificationSystemFacade();
    virtual ~GPNotificationSystemFacade();

    void sendGPNotificationForPatient(Patient* p);

    void update(Patient* patient) override;
};

#endif
