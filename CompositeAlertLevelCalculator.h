#ifndef COMPOSITEALERTLEVELCALCULATOR_H
#define COMPOSITEALERTLEVELCALCULATOR_H

#include "AlertLevelCalculatorComponent.h"
#include <vector>
#include <memory>

class CompositeAlertLevelCalculator : public AlertLevelCalculatorComponent
{
public:
    void addChild(std::unique_ptr<AlertLevelCalculatorComponent> component);
    void calculateHighestAlertLevel(Patient* patient, AlertLevel highestAlertLevel) const override;
private:
    std::vector<std::unique_ptr<AlertLevelCalculatorComponent>> _children;
};

#endif
