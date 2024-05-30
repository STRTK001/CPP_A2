#ifndef DISEASEALERTLEVELCALCULATOR_H
#define DISEASEALERTLEVELCALCULATOR_H

#include <string>
#include <map>
#include <memory>

#include "PatientAlertLevels.h"
#include "Patient.h"

#include "IDiseaseCalculationStrategy.h"
#include "AmogusSusCalculation.h"
#include "ERushCalculation.h"
#include "NoCapSyndromeCalculation.h"
#include "TiccToccBrainDamageCalculation.h"

class DiseaseAlertLevelCalculator
{
public:
	DiseaseAlertLevelCalculator();
	void calculateAlertLevel(Patient* patient);
private:
	std::map<std::string, std::shared_ptr<IDiseaseCalculationStrategy>> _calculationStrategies;


};

#endif