#include "abstractcalculationcomponent.h"

AbstractCalculationComponent::AbstractCalculationComponent(AbstractAccessStrategy::Ptr busyState) :
    m_busyState(busyState)
{
}

void AbstractCalculationComponent::prepareCalc()
{
    m_busyState->reset();
}

bool AbstractCalculationComponent::tryStartCalc(int subBufferNo)
{
    bool calcDoneByMe = m_busyState->tryMakeBusy();
    if(calcDoneByMe) {
        doCalc(subBufferNo);
        m_busyState->setDone(true);
    }
    return calcDoneByMe;
}

bool AbstractCalculationComponent::calcDone()
{
    return m_busyState->isDone();
}

void AbstractCalculationComponent::setDone(bool done)
{
    m_busyState->setDone(done);
}
