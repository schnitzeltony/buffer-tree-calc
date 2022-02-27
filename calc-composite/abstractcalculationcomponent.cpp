#include "abstractcalculationcomponent.h"

AbstractCalculationComponent::AbstractCalculationComponent(AbstractAccessStrategy::Ptr busyState) :
    m_accessStrategy(busyState)
{
}

void AbstractCalculationComponent::prepareCalc()
{
    m_accessStrategy->reset();
}

bool AbstractCalculationComponent::tryStartCalc(int subBufferNo)
{
    bool calcDoneByMe = m_accessStrategy->tryMakeBusy();
    if(calcDoneByMe) {
        doCalc(subBufferNo);
        m_accessStrategy->setDone(true);
    }
    return calcDoneByMe;
}

bool AbstractCalculationComponent::calcDone()
{
    return m_accessStrategy->isDone();
}

void AbstractCalculationComponent::setDone(bool done)
{
    m_accessStrategy->setDone(done);
}
