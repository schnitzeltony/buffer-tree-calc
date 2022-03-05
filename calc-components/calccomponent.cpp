#include "calccomponent.h"

CalcComponent::CalcComponent(AbstractAccessStrategy::Ptr accessStrategy) :
    m_accessStrategy(accessStrategy)
{
}

void CalcComponent::prepareCalc()
{
    m_accessStrategy->reset();
}

bool CalcComponent::tryStartCalc(int sampleCount)
{
    bool calcDoneByMe = m_accessStrategy->tryMakeBusy();
    if(calcDoneByMe) {
        doCalc(sampleCount);
        m_accessStrategy->setDone();
    }
    return calcDoneByMe;
}

bool CalcComponent::isDone()
{
    return m_accessStrategy->isDone();
}
