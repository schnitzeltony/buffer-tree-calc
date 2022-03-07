#ifndef CALCULATORDIFF_IMPL_H
#define CALCULATORDIFF_IMPL_H

#include "calculatordiff.h"

template <class T>
CalculatorDiff<T>::CalculatorDiff(CALC_PTR(T) minuent,
                                  CALC_PTR(T) subtrahent,
                                  BUFFER_PTR(T) output,
                                  AbstractAccessStrategy::Ptr accessStrategy,
                                  bool scalarSubtrahend) :
    CalculatorBase<T>(std::vector<CalcInterface::Ptr> {minuent, subtrahent}, output, accessStrategy),
    m_minuentBuffer(minuent->getOutputBuffer()),
    m_subtrahentBuffer(subtrahent->getOutputBuffer()),
    m_scalarSubtrahend(scalarSubtrahend)
{
}

template <class T>
void CalculatorDiff<T>::doCalc(int sampleCount)
{
    BUFFER_PTR(T) outBuff = CalculatorBase<T>::getOutputBuffer();
    if(!m_scalarSubtrahend) {
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_minuentBuffer->at(currSample) - m_subtrahentBuffer->at(currSample);
        }
    }
    else {
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_minuentBuffer->at(currSample) - m_subtrahentBuffer->at(0);
        }
    }
}

#endif // CALCULATORDIFF_IMPL_H
