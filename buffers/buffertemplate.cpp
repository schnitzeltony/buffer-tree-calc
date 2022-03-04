#include "buffertemplate.h"


template <class INTYPE, class OUTTYPE>
bool TCalculator<INTYPE, OUTTYPE>::doCalc(int sampleCount)
{
    bool allWorkDone = true;
    for(auto input : m_inputCalculators) {
        if(!input->calcDone()) {
            bool started = input->tryStartCalc(sampleCount);
            if(started) {
                input->setDone();
            }
            else {
                allWorkDone = false;
            }
        }
    }
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
void TCalculator<INTYPE, OUTTYPE>::init()
{
    for(auto input : m_inputCalculators) {
        input->init();
    }
    doInit();
}

template <class INTYPE, class OUTTYPE>
void TCalculator<INTYPE, OUTTYPE>::destroy()
{
    for(auto input : m_inputCalculators) {
        input->destroy();
    }
    doDestroy();
}

template class TCalculator<int16_t, int16_t>;
template class TCalculator<int16_t, float>;
template class TCalculator<float, int16_t>;
template class TCalculator<float, float>;
