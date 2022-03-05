#include "calccomponent.h"

CalcComponent::CalcComponent(std::function<bool (int)> doCalcHandler, AbstractAccessStrategy::Ptr accessStrategy) :
    m_accessStrategy(accessStrategy),
    m_doCalcHandler(doCalcHandler)
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

bool CalcComponent::doCalc(int sampleCount)
{
    return m_doCalcHandler(sampleCount);
}
