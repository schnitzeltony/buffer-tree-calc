#ifndef CALCULATORADD_IMPL_H
#define CALCULATORADD_IMPL_H

#include "calc-components/calculators/calculatoradd.h"

template <class T1_OUT, class T2>
CalculatorAdd2<T1_OUT, T2>::CalculatorAdd2(CALC_PTR(T1_OUT) buff1,
                                           CALC_PTR(T2) buff2,
                                           BUFFER_PTR(T1_OUT) output,
                                           AbstractAccessStrategy::Ptr accessStrategy,
                                           bool scalarBuff2) :
    CalculatorBase<T1_OUT>(std::vector<CalcInterface::Ptr> {buff1, buff2}, output, accessStrategy),
    m_buff1(buff1->getOutputBuffer()),
    m_buff2(buff2->getOutputBuffer()),
    m_scalarBuff2(scalarBuff2)
{
}

template <class T1_OUT, class T2>
void CalculatorAdd2<T1_OUT, T2>::doCalc(int sampleCount)
{
    BUFFER_PTR(T1_OUT) outBuff = CalculatorBase<T1_OUT>::getOutputBuffer();
    if(!m_scalarBuff2) {
        doCalcBuff(sampleCount, outBuff);
    }
    else {
        doCalcScalar(sampleCount, outBuff);
    }
}

template <class T1_OUT, class T2>
template <typename ACCESS_STRATEGY>
std::shared_ptr<CalculatorAdd2<T1_OUT, T2>> CalculatorAdd2<T1_OUT, T2>::createWithOutBuffer(CALC_PTR(T1_OUT) buff1,
                                                                                            CALC_PTR(T2) buff2,
                                                                                            int bufferSize,
                                                                                            bool scalarBuff2)
{
    return std::make_shared<CalculatorAdd2<T1_OUT, T2>>(buff1,
                                                       buff2,
                                                       std::make_shared<BufferTemplate<T1_OUT>>(bufferSize),
                                                       createAccessStrategy<ACCESS_STRATEGY>(),
                                                       scalarBuff2);
}

template <class T1_OUT, class T2>
void CalculatorAdd2<T1_OUT, T2>::doCalcBuff(int sampleCount, BUFFER_PTR(T1_OUT) outBuff)
{
    for(int i=0, currSample = CalculatorBase<T1_OUT>::getSampleOffset();
        i<sampleCount;
        ++i, ++currSample) {
        outBuff->at(currSample) = m_buff1->at(currSample) + m_buff2->at(currSample);
    }
}

template <class T1_OUT, class T2>
void CalculatorAdd2<T1_OUT, T2>::doCalcScalar(int sampleCount, BUFFER_PTR(T1_OUT) outBuff)
{
    T2 scalarVal = m_buff2->at(0);
    for(int i=0, currSample = CalculatorBase<T1_OUT>::getSampleOffset();
        i<sampleCount;
        ++i, ++currSample) {
        outBuff->at(currSample) = m_buff1->at(currSample) + scalarVal;
    }
}

#endif // CALCULATORADD_IMPL_H
