#include "calculationnode.h"

CalculationNode::CalculationNode(AbstractAccessStrategy::Ptr busyState, ICalcNodeComponents::Ptr calcComponents) :
    AbstractCalculationComponent(busyState),
    m_calcComponents(calcComponents)
{
}

bool CalculationNode::doCalc(int subBufferNo)
{
    bool allWorkDone = true;
    for(auto input : m_calcComponents->getInputComponents()) {
        if(!input->calcDone()) {
            bool started = input->tryStartCalc(subBufferNo);
            if(!started) {
                allWorkDone = false;
            }
        }
    }
    if(allWorkDone && !m_calcComponents->getOutputComponent()->calcDone()) {
        bool started = m_calcComponents->getOutputComponent()->tryStartCalc(subBufferNo);
        if(!started) {
            allWorkDone = false;
        }
    }
    if(allWorkDone) {
        m_calcComponents->getOutputComponent()->setDone(true);
    }
    return allWorkDone;
}

void CalculationNode::init()
{
    for(auto input : m_calcComponents->getInputComponents()) {
        input->init();
    }
    m_calcComponents->getOutputComponent()->init();
}

void CalculationNode::destroy()
{
    for(auto input : m_calcComponents->getInputComponents()) {
        input->destroy();
    }
    m_calcComponents->getOutputComponent()->destroy();
}
