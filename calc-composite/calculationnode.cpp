#include "calculationnode.h"

bool CalculationNode::doCalc(int subBufferNo)
{
    bool allWorkDone = true;
    for(auto input : m_outCalcStrategy->getInputComponents()) {
        if(!input->calcDone()) {
            bool started = input->startCalc(subBufferNo);
            if(!started) {
                allWorkDone = false;
            }
        }
    }
    if(allWorkDone && !m_outCalcStrategy->calcDone()) {
        bool started = m_outCalcStrategy->startCalc(subBufferNo);
        if(!started) {
            allWorkDone = false;
        }
    }
    if(allWorkDone) {
        m_outCalcStrategy->setDone(true);
    }
    return allWorkDone;
}

void CalculationNode::init()
{
    for(auto input : m_outCalcStrategy->getInputComponents()) {
        input->init();
    }
    m_outCalcStrategy->getOutputBuffer()->init();
}

void CalculationNode::destroy()
{
    for(auto input : m_outCalcStrategy->getInputComponents()) {
        input->destroy();
    }
    m_outCalcStrategy->getOutputBuffer()->destroy();
}
