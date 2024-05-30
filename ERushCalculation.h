#ifndef ERUSHCALCULATION_H
#define ERUSHCALCULATION_H

class ERush : public IDiseaseCalculationStrategy
{
	virtual AlertLevel calculateAlertLevel(Patient* patient) const override
	{
		//get the patients vitals
		const Vitals* vitals = patient->vitals().back();
		//check if the body temp and brain activity reach the RED threshold
		if (vitals->BT() > 38 && vitals->BA() > 110)
		{
			return AlertLevel::Red;
		}
		//check if the body temp and brain activity reach the YELLOW threshold
		else if (vitals->BT() > 38 && vitals->BA() > 100)
		{
			return AlertLevel::Yellow;
		}
		else
		{
			//Else the patient is fine
			return AlertLevel::Green;
		}
	}
};

#endif