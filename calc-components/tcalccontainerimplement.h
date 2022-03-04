#ifndef TCALCCONTAINERIMPLEMENT_H
#define TCALCCONTAINERIMPLEMENT_H

#include "tcalccontainer.h"

template <class INTYPE, class OUTTYPE>
bool TCalcContainer<INTYPE, OUTTYPE>::doCalc(int sampleCount)
{
    bool allWorkDone = calcInputs(sampleCount);
    if(allWorkDone && !calcDone()) {
        // Not starting final calc means another thread is here already.
        // So we can report allWorkDone to avoid threads looping without
        // calc activity
        bool started = tryStartCalc(sampleCount);
        if(started) {
            setDone();
        }
    }
    return allWorkDone;
}

template <class INTYPE, class OUTTYPE>
void TCalcContainer<INTYPE, OUTTYPE>::init()
{
    for(auto input : m_inputCalculators) {
        input->init();
    }
    doInit();
}

template <class INTYPE, class OUTTYPE>
void TCalcContainer<INTYPE, OUTTYPE>::destroy()
{
    for(auto input : m_inputCalculators) {
        input->destroy();
    }
    doDestroy();
}

template <class INTYPE, class OUTTYPE>
bool TCalcContainer<INTYPE, OUTTYPE>::calcInputs(int sampleCount)
{
    bool allInputsDone = true;
    for(auto input : m_inputCalculators) {
        if(!input->calcDone()) {
            bool started = input->tryStartCalc(sampleCount);
            if(started) {
                input->setDone();
            }
            else {
                allInputsDone = false;
            }
        }
    }
    return allInputsDone;
}

#endif // TCALCCONTAINERIMPLEMENT_H
