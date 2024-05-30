#ifndef TICCTOCCBRAINDAMAGECALCULATION_H
#define TICCTOCCBRAINDAMAGECALCULATION_H

#include "IDiseaseCalculationStrategy.h"

class TiccToccBrainDamageCalculation : public IDiseaseCalculationStrategy
{
	virtual AlertLevel calculateAlertLevel(Patient* patient) const override
	{
		//get the patients vitals
		const Vitals* vitals = patient->vitals().back();
		//check if the patient is under 3 and their brain activity meets the RED threshold
		if(patient->age() < 35 && vitals->BA() < 10)
		{
			return AlertLevel::Red;
		}
		//check if the patient is 35 or over and their brain activity meets the RED threshold
		else if(patient->age() >= 35 && vitals->BA() < 20)
		{
			return AlertLevel::Red;
		}
		//else they're fine
		else
		{
			return AlertLevel::Green;
		}
		
	}
};

#endif