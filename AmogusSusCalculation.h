#ifndef AMOGUSSUSCALCULATION_H
#define AMOGUSSUSCALCULATION_H

#include "IDiseaseCalculationStrategy.h"

class AmogusSusCalculation : public IDiseaseCalculationStrategy
{
public:
	virtual AlertLevel calculateAlertLevel(Patient* patient) const override
	{
		//get the patients vitals
		const Vitals* vitals = patient->vitals().back();
		//check if the patients heart rate meets the RED threshold
		if(vitals->HR() > 220)
		{
			return AlertLevel::Red;
		}
		//check if the patients heart rate meets the ORANGE threshold
		else if(vitals->HR() > 210)
		{
			return AlertLevel::Orange;
		}
		//check if the patients heart rate meets the YELLOW threshold
		else if(vitals->HR() > 200)
		{
			return AlertLevel::Yellow;
		}
		//else they're fine
		else
		{
			return AlertLevel::Green;
		}
	}
};

#endif