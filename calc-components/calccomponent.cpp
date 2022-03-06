#include "calccomponent.h"

CalcComponent::CalcComponent(std::function<void (int)> doCalcHandler, AbstractAccessStrategy::Ptr accessStrategy) :
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

bool CalcComponent::isDone() const
{
    return m_accessStrategy->isDone();
}

void CalcComponent::doCalc(int sampleCount)
{
    m_doCalcHandler(sampleCount);
}
