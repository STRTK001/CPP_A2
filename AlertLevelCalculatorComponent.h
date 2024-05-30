#ifndef ALERTLEVELCALCULATORCOMPONENT_H
#define ALERTLEVELCALCULATORCOMPONENT_H

#include <memory>

#include "PatientAlertLevels.h"
#include "Patient.h"
#include "IDiseaseCalculationStrategy.h"

class AlertLevelCalculatorComponent
{
public:
	virtual void calculateHighestAlertLevel(Patient* patient,AlertLevel& heighestAlertLevel) const = 0;
};

#endif 