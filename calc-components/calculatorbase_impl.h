#ifndef CALCULATORBASEIMPL_H
#define CALCULATORBASEIMPL_H

#include "calc-components/calculatorbase.h"

template <class T>
CalculatorBase<T>::CalculatorBase(std::vector<CalcInterface::Ptr> inputCalculators,
               BUFFER_PTR(T) outputBuffer,
               AbstractAccessStrategy::Ptr accessStrategy) :
    m_AccessComponent([&](int sampleCount){doCalcCallback(sampleCount);}, accessStrategy),
    m_inputsComposite(inputCalculators),
    m_outputBuffer(outputBuffer)
{
}

template <class T>
void CalculatorBase<T>::prepareCalc()
{
    m_sampleOffset = 0;
    m_inputsComposite.prepareCalc();
    m_AccessComponent.prepareCalc();
}

template <class T>
bool CalculatorBase<T>::isDone() const
{
    return m_inputsComposite.isDone() && m_AccessComponent.isDone();
}

template <class T>
bool CalculatorBase<T>::tryStartCalc(int sampleCount)
{
    bool allDone = true;
    if(!m_inputsComposite.isDone()) {
        allDone = m_inputsComposite.tryStartCalc(sampleCount);
    }
    if(allDone && !m_AccessComponent.isDone()) {
        allDone = m_AccessComponent.tryStartCalc(sampleCount);
    }
    return allDone;
}

template <class T>
void CalculatorBase<T>::doCalcCallback(int sampleCount)
{
    doCalc(sampleCount);
    m_sampleOffset += sampleCount;
}

#endif // CALCULATORBASEIMPL_H
