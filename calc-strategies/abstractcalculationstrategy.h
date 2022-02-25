#ifndef ABSTRACTCALCULATIONSTRATEGY_H
#define ABSTRACTCALCULATIONSTRATEGY_H

#include "calc-composite/abstractcalculationcomponent.h"
#include <vector>

class AbstractCalculationStrategy : public AbstractCalculationComponent
{
public:
    AbstractCalculationStrategy(AbstractAccessStrategy::Ptr accessStrategy,
                                std::vector<AbstractCalculationComponent*> inputComponents,
                                AbstractCalculationComponent* outComponent);

    virtual std::vector<AbstractCalculationComponent *> getInputComponents();
    virtual AbstractCalculationComponent *getOutputBuffer();

private:
    std::vector<AbstractCalculationComponent*> m_inputComponents;
    AbstractCalculationComponent *m_outComponent;
};

typedef std::shared_ptr<AbstractCalculationStrategy> AbstractCalculationStrategyPtr;

#endif // ABSTRACTCALCULATIONSTRATEGY_H
