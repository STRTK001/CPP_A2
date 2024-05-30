#ifndef IDISEASECALCULATIONSTRATEGY_H
#define IDISEASECALCULATIONSTRATEGY_H

#include "Patient.h"
#include "Vitals.h"

class IDiseaseCalculationStrategy
{
public:
	virtual AlertLevel calculateAlertLevel(Patient* patient) const = 0;
};

#endif