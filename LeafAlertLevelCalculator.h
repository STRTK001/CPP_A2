#ifndef LEAFALERTLEVELCALCULATOR_H
#define LEAFALERTLEVELCALCULATOR_H

#include "AlertLevelCalculatorComponent.h"

class LeafAlertLevelCalculator : public AlertLevelCalculatorComponent
{
public:
	LeafAlertLevelCalculator(std::shared_ptr<IDiseaseCalculationStrategy> calculationStrategy);
	virtual void calculateHighestAlertLevel(Patient* patient,AlertLevel highestAlertLevel) const override;

private:
	std::shared_ptr<IDiseaseCalculationStrategy> _calculationStrategy;
};

#endif 