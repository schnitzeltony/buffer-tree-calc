#ifndef CALCULATORMULT_IMPL_H
#define CALCULATORMULT_IMPL_H

#include "calculatormult.h"

template <class T>
CalculatorMult<T>::CalculatorMult(CALC_PTR(T) buff1,
                                 CALC_PTR(T) buff2,
                                 BUFFER_PTR(T) output,
                                 AbstractAccessStrategy::Ptr accessStrategy,
                                 bool scalarBuff2) :
    CalculatorBase<T>(std::vector<CalcInterface::Ptr> {buff1, buff2}, output, accessStrategy),
    m_buff1(buff1->getOutputBuffer()),
    m_buff2(buff2->getOutputBuffer()),
    m_scalarBuff2(scalarBuff2)
{
}

template <class T>
void CalculatorMult<T>::doCalc(int sampleCount)
{
    BUFFER_PTR(T) outBuff = CalculatorBase<T>::getOutputBuffer();
    if(!m_scalarBuff2) {
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_buff1->at(currSample) * m_buff2->at(currSample);
        }
    }
    else {
        for(int i=0, currSample = CalculatorBase<T>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
            outBuff->at(currSample) =
                    m_buff1->at(currSample) * m_buff2->at(0);
        }
    }
}

#endif // CALCULATORMULT_IMPL_H
