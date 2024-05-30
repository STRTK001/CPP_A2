#ifndef NOCAPSYNDROMECALCULATION_H
#define NOCAPSYNDROMECALCULATION_H

#include "IDiseaseCalculationStrategy.h"

class NoCapSyndromeCalculation : public IDiseaseCalculationStrategy
{
	virtual AlertLevel calculateAlertLevel(Patient* patient) const override
	{
		//get the patients vitals
		const Vitals* vitals = patient->vitals().back();
		//check if the O2 saturation meets the RED threshold
		if (vitals->SPO2() < 90)
		{
			return AlertLevel::Red;
		}
		//check if the O2 saturation meets the ORANGE threshold
		else if(vitals->SPO2() < 92)
		{
			return AlertLevel::Orange;
		}
		//check if the O2 saturation meets the YELLOW threshold
		else if(vitals->SPO2() < 94)
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