#include "DiseaseAlertLevelCalculator.h"
#include "Utility.h"

DiseaseAlertLevelCalculator::DiseaseAlertLevelCalculator()
{
	//populate the calculator map with all the calculation strategies
	//amogus sus
	_calculationStrategies[Diagnosis::AMOGUS_SUS] =  std::make_shared<AmogusSusCalculation>();
	//E Rush
	_calculationStrategies[Diagnosis::E_RUSH] = std::make_shared <ERush>();
	//No Cap Syndrome
	_calculationStrategies[Diagnosis::NOCAP_SYNDROME] = std::make_shared <NoCapSyndromeCalculation>();
	//Ticc Tocc Brain Damage
	_calculationStrategies[Diagnosis::TICCTOCC_BRAIN_DAMAGE] = std::make_shared <TiccToccBrainDamageCalculation>();
}

void DiseaseAlertLevelCalculator::calculateAlertLevel(Patient* patient)
{
	//get the patients primary disease
	std::string primaryDisease = patient->primaryDiagnosis();
	//check if we have a strategy for the primary disease
	if (!_calculationStrategies[primaryDisease])
	{
		//maybe print some kind of console msg
		strtk001Utils::logError("cant find primary disease of " + primaryDisease);
		return;
	}
	//calculate the patients alert level using the primary disease
	AlertLevel alertLevel = _calculationStrategies[primaryDisease]->calculateAlertLevel(patient);
	//set the patients primary disease
	patient->setAlertLevel(alertLevel);
}

