#ifndef ALERTLEVELCALCULATORCOMPONENT_H
#define ALERTLEVELCALCULATORCOMPONENT_H

#include "PatientAlertLevel.h"
#include "Patient.h"

class AlertLevelCalculatorComponent
{
public:
	virtual AlertLevel calculateAlertLevel(Patient* patient) const = 0;
};

#endif 