#ifndef CALCULATORDIFF_IMPL_H
#define CALCULATORDIFF_IMPL_H

#include "calculatordiff.h"

template <class T1_OUT, class T2>
CalculatorDiff2<T1_OUT, T2>::CalculatorDiff2(CALC_PTR(T1_OUT) minuent,
                                             CALC_PTR(T2) subtrahent,
                                             BUFFER_PTR(T1_OUT) output,
                                             AbstractAccessStrategy::Ptr accessStrategy,
                                             bool scalarSubtrahend) :
    CalculatorBase<T1_OUT>(std::vector<CalcInterface::Ptr> {minuent, subtrahent}, output, accessStrategy),
    m_minuentBuffer(minuent->getOutputBuffer()),
    m_subtrahentBuffer(subtrahent->getOutputBuffer()),
    m_scalarSubtrahend(scalarSubtrahend)
{
}

template <class T1_OUT, class T2>
void CalculatorDiff2<T1_OUT, T2>::doCalc(int sampleCount)
{
    BUFFER_PTR(T1_OUT) outBuff = CalculatorBase<T1_OUT>::getOutputBuffer();
    if(!m_scalarSubtrahend) {
        for(int i=0, currSample = CalculatorBase<T1_OUT>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_minuentBuffer->at(currSample) - m_subtrahentBuffer->at(currSample);
        }
    }
    else {
        T2 scalarSubtrahent = m_subtrahentBuffer->at(0);
        for(int i=0, currSample = CalculatorBase<T1_OUT>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_minuentBuffer->at(currSample) - scalarSubtrahent;
        }
    }
}

template <class T1_OUT, class T2>
template <typename ACCESS_STRATEGY>
std::shared_ptr<CalculatorDiff2<T1_OUT, T2>> CalculatorDiff2<T1_OUT, T2>::createWithOutBuffer(
        CALC_PTR(T1_OUT) minuent,
        CALC_PTR(T2) subtrahent,
        int bufferSize,
        bool scalarSubtrahend)
{
    return std::make_shared<CalculatorDiff2<T1_OUT, T2>>(minuent,
                                                         subtrahent,
                                                         std::make_shared<BufferTemplate<T1_OUT>>(bufferSize),
                                                         createAccessStrategy<ACCESS_STRATEGY>(),
                                                         scalarSubtrahend);
}

#endif // CALCULATORDIFF_IMPL_H
