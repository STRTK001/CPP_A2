#ifndef DISEASEALERTLEVELCALCULATOR_H
#define DISEASEALERTLEVELCALCULATOR_H

#include <string>
#include <map>
#include <memory>

#include "PatientAlertLevels.h"
#include "Patient.h"
//strategies
#include "IDiseaseCalculationStrategy.h"
#include "AmogusSusCalculation.h"
#include "ERushCalculation.h"
#include "NoCapSyndromeCalculation.h"
#include "TiccToccBrainDamageCalculation.h"
//calculation components
#include "AlertLevelCalculatorComponent.h"
#include "LeafAlertLevelCalculator.h"
#include "CompositeAlertLevelCalculator.h"

class DiseaseAlertLevelCalculator
{
public:
	DiseaseAlertLevelCalculator();
	void calculateAlertLevel(Patient* patient);
	void calculateHighestAlertLevel(Patient* patient);
private:
	std::map<std::string, std::shared_ptr<IDiseaseCalculationStrategy>> _calculationStrategies;
};

#endif