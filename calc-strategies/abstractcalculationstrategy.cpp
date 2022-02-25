#include "abstractcalculationstrategy.h"

AbstractCalculationStrategy::AbstractCalculationStrategy(AbstractAccessStrategy::Ptr accessStrategy,
                                                         std::vector<AbstractCalculationComponent *> inputComponents,
                                                         AbstractCalculationComponent *outComponent) :
    AbstractCalculationComponent(accessStrategy),
    m_inputComponents(inputComponents),
    m_outComponent(outComponent)
{
}

std::vector<AbstractCalculationComponent *> AbstractCalculationStrategy::getInputComponents()
{
    return m_inputComponents;
}

AbstractCalculationComponent *AbstractCalculationStrategy::getOutputBuffer()
{
    return m_outComponent;
}
