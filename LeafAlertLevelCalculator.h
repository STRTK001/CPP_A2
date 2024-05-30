#ifndef LEAFALERTLEVELCALCULATOR_H
#define LEAFALERTLEVELCALCULATOR_H

#include <memory>

#include "AlertLevelCalculatorComponent.h"
#include "IDiseaseCalculationStrategy.h"

class LeafAlertLevelCalculator : public AlertLevelCalculatorComponent
{
public:
	LeafAlertLevelCalculator();
	virtual AlertLevel calculateAlertLevel(Patient* patient) const override;

private:
	std::shared_ptr<IDiseaseCalculationStrategy> _calculationStrategy;
};

#endif 