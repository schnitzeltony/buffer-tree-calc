#ifndef CALCULATORBASEIMPL_H
#define CALCULATORBASEIMPL_H

#include "calc-components/calculatorbase.h"

template <class T>
CalculatorBase<T>::CalculatorBase(std::vector<CalcInterface::Ptr> inputCalculators,
                                  BUFFER_PTR(T) outputBuffer,
                                  std::function<void(int)> doCalcHandler,
                                  AbstractAccessStrategy::Ptr accessStrategy) :
    m_AccessComponent([&](int sampleCount){doCalcCallback(sampleCount);}, accessStrategy),
    m_inputsComposite(inputCalculators),
    m_outputBuffer(outputBuffer),
    m_doCalcHandler(doCalcHandler)
{
}

template <class T>
void CalculatorBase<T>::prepareNextCalc()
{
    if(!m_keepSampleOffsetOnNextTryStart) {
        m_sampleOffset = 0;
    }
    m_inputsComposite.prepareNextCalc();
    m_AccessComponent.prepareNextCalc();
}

template <class T>
bool CalculatorBase<T>::isDone() const
{
    return m_inputsComposite.isDone() && m_AccessComponent.isDone();
}

template <class T>
bool CalculatorBase<T>::tryStartCalc(int sampleCount)
{
    bool atLeastOneStarted = false;
    if(!m_inputsComposite.isDone()) {
        atLeastOneStarted = m_inputsComposite.tryStartCalc(sampleCount);
    }
    if(!m_AccessComponent.isDone()) {
        atLeastOneStarted |= m_AccessComponent.tryStartCalc(sampleCount);
    }
    return atLeastOneStarted;
}

template <class T>
void CalculatorBase<T>::doCalcCallback(int sampleCount)
{
    m_doCalcHandler(sampleCount);
    m_sampleOffset += sampleCount;
}

#endif // CALCULATORBASEIMPL_H
