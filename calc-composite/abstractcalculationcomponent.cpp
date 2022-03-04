#include "abstractcalculationcomponent.h"

AbstractCalculationComponent::AbstractCalculationComponent(AbstractAccessStrategy::Ptr busyState) :
    m_accessStrategy(busyState)
{
}

void AbstractCalculationComponent::prepareCalc()
{
    m_accessStrategy->reset();
}

bool AbstractCalculationComponent::tryStartCalc(int sampleCount)
{
    bool calcDoneByMe = m_accessStrategy->tryMakeBusy();
    if(calcDoneByMe) {
        doCalc(sampleCount);
        m_accessStrategy->setDone();
    }
    return calcDoneByMe;
}

bool AbstractCalculationComponent::calcDone()
{
    return m_accessStrategy->isDone();
}

void AbstractCalculationComponent::setDone()
{
    m_accessStrategy->setDone();
}
