#include "CompositeAlertLevelCalculator.h"


void CompositeAlertLevelCalculator::addChild(std::unique_ptr<AlertLevelCalculatorComponent> component)
{
	_children.push_back(std::move(component));
}

void CompositeAlertLevelCalculator::calculateHighestAlertLevel(Patient* patient,AlertLevel& highestAlertLevel) const
{
	for(const auto& child : _children)
	{
		child->calculateHighestAlertLevel(patient, highestAlertLevel);
	}
}