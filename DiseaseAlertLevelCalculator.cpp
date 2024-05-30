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


void DiseaseAlertLevelCalculator::calculateHighestAlertLevel(Patient* patient)
{
	//create a new composite calculator
	CompositeAlertLevelCalculator* calculatorComposite = new CompositeAlertLevelCalculator();
	//for each disease that this patient has
	for (const std::string& disease : patient->diagnoses())
	{
		//find the coresponding strategy in our calculaton strategies map 
		std::shared_ptr<IDiseaseCalculationStrategy> strategy = _calculationStrategies[disease];
		if (strategy.get() != nullptr)
		{
			//populate the composite calculator with the coresponding strategy
			calculatorComposite->addChild(std::make_unique<LeafAlertLevelCalculator>(strategy));
		}
	}
	//init our highest alert level to green as a default
	AlertLevel highestAlertLevel = AlertLevel::Green;
	//use the composite to calculate our patient's highestAlertLevel
	calculatorComposite->calculateHighestAlertLevel(patient, highestAlertLevel);
	//set the patient's alert level to the alertLevel we have calculated
	patient->setAlertLevel(highestAlertLevel);
}
