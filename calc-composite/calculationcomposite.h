#ifndef CALCULATIONCOMPOSITE_H
#define CALCULATIONCOMPOSITE_H

#include "abstractcalculationcomponent.h"
#include <vector>

class CalculationComposite: public AbstractCalculationComponent
{
public:
    CalculationComposite(AbstractAccessStrategy::Ptr busyState,
                    std::vector<AbstractCalculationComponent::Ptr> inputComponents,
                    AbstractCalculationComponent::Ptr outputComponent);
    virtual bool doCalc(int sampleCount) override;
    virtual void init() override;
    virtual void destroy() override;
private:
    std::vector<AbstractCalculationComponent::Ptr> m_inputComponents;
    AbstractCalculationComponent::Ptr m_outputComponent;
};

#endif // CALCULATIONCOMPOSITE_H
