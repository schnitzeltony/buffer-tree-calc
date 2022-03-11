#ifndef CONVERTFLOATINGTOINTEGER_IMPL_H
#define CONVERTFLOATINGTOINTEGER_IMPL_H

#include "calc-components/calculators/convertfloatingtointeger.h"

template <class F_TYPE, class I_TYPE>
ConvertFloatingToInteger<F_TYPE, I_TYPE>::ConvertFloatingToInteger(CALC_PTR(F_TYPE) input,
                                                                   BUFFER_PTR(I_TYPE) output,
                                                                   AbstractAccessStrategy::Ptr accessStrategy,
                                                                   I_TYPE scalingFactor) :
    CalculatorBaseIn1<F_TYPE, I_TYPE>(input, output, accessStrategy),
    m_scalingFactor(scalingFactor)
{
}

template <class F_TYPE, class I_TYPE>
void ConvertFloatingToInteger<F_TYPE, I_TYPE>::doCalc(int sampleCount)
{
    BUFFER_PTR(I_TYPE) outBuff = CalculatorBase<I_TYPE>::getOutputBuffer();
    for(int i=0, currSample = CalculatorBase<I_TYPE>::getSampleOffset();
            i<sampleCount;
            ++i, ++currSample) {
        outBuff->at(currSample) = (I_TYPE)((double)CalculatorBaseIn1<F_TYPE, I_TYPE>::m_inBuff->at(currSample) * (double)m_scalingFactor);
    }
}

#endif // CONVERTFLOATINGTOINTEGER_IMPL_H
