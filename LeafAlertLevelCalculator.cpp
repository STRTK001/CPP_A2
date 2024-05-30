#include "LeafAlertLevelCalculator.h"
#include "Utility.h"
LeafAlertLevelCalculator::LeafAlertLevelCalculator(std::shared_ptr<IDiseaseCalculationStrategy> calculationStrategy) :
	_calculationStrategy(calculationStrategy) {}

void LeafAlertLevelCalculator::calculateHighestAlertLevel(Patient* patient, AlertLevel& highestAlertLevel) const
{
	AlertLevel currentAlertLevel =  _calculationStrategy.get()->calculateAlertLevel(patient);

	if (currentAlertLevel > highestAlertLevel)
	{
		highestAlertLevel = currentAlertLevel;
	}
}
