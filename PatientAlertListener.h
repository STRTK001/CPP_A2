#ifndef PATIENTALERTLISTENER_H
#define PATIENTALERTLISTENER_H

#include "PatientAlertLevels.h"
#include "Patient.h"
class PatientAlertListener
{
public:
	virtual void update(Patient* patient) = 0;
};

#endif