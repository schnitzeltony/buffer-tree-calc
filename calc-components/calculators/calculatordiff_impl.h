#ifndef CALCULATORDIFF_IMPL_H
#define CALCULATORDIFF_IMPL_H

#include "calculatordiff.h"

template <class T>
CalculatorDiff<T>::CalculatorDiff(CALC_PTR(T) minuent,
                                  CALC_PTR(T) subtrahent,
                                  BUFFER_PTR(T) output,
                                  AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorBase<T>(std::vector<CalcInterface::Ptr> {minuent, subtrahent}, output, accessStrategy),
    m_minuentBuffer(minuent->getOutputBuffer()),
    m_subtrahentBuffer(subtrahent->getOutputBuffer())
{
}

template <class T>
void CalculatorDiff<T>::doCalc(int sampleCount)
{
    BUFFER_PTR(T) outBuff = CalculatorBase<T>::getOutputBuffer();
    for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
        i<sampleCount;
        ++i, ++currSample) {
        outBuff->at(currSample) =
                m_minuentBuffer->at(currSample) - m_subtrahentBuffer->at(currSample);
    }
}

#endif // CALCULATORDIFF_IMPL_H
