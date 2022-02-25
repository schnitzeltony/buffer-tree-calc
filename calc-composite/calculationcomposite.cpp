#include "calculationcomposite.h"

CalculationComposite::CalculationComposite(AbstractAccessStrategy::Ptr busyState,
                                           std::vector<Ptr> inputComponents,
                                           Ptr outputComponent) :
    AbstractCalculationComponent(busyState),
    m_inputComponents(inputComponents),
    m_outputComponent(outputComponent)
{
}

bool CalculationComposite::doCalc(int subBufferNo)
{
    bool allWorkDone = true;
    for(auto input : m_inputComponents) {
        if(!input->calcDone()) {
            bool started = input->tryStartCalc(subBufferNo);
            if(started) {
                input->setDone(true);
            }
            else {
                allWorkDone = false;
            }
        }
    }
    if(allWorkDone && !m_outputComponent->calcDone()) {
        // Not starting final calc means another thread is here already.
        // So we can report allWorkDone to avoid threads looping without
        // calc activity
        bool started = m_outputComponent->tryStartCalc(subBufferNo);
        if(started) {
            m_outputComponent->setDone(true);
        }
    }
    return allWorkDone;
}

void CalculationComposite::init()
{
    for(auto input : m_inputComponents) {
        input->init();
    }
    m_outputComponent->init();
}

void CalculationComposite::destroy()
{
    for(auto input : m_inputComponents) {
        input->destroy();
    }
    m_outputComponent->destroy();
}
